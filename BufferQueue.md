# BufferQueue

**Path:**  
`native/libs/gui/` — `BufferQueue.cpp`, `BufferQueueCore.*`, `BufferQueueProducer.*`, `BufferQueueConsumer.*`

**Namespace/Class:**  
`android::BufferQueue`, `BufferQueueCore`, `BufferQueueProducer`, `BufferQueueConsumer`

**Related Documentation:**  
`native/libs/gui/include/gui/BufferSlot.h` (state machine comments)

**Related Classes:**

- [[Surface]] — wraps `IGraphicBufferProducer` for apps
- [[BLASTBufferQueue]] — modern app → SurfaceFlinger path
- [[GraphicBuffer]] — gralloc-backed pixel memory
- [[IGraphicBufferProducer]] / [[IGraphicBufferConsumer]] — Binder IPC interfaces

---

# Purpose

**One sentence**

> BufferQueue is a fixed-size pool of GPU/display buffers shared between a **producer** (writes pixels) and a **consumer** (reads/displays pixels), synchronized with fences and a slot-based state machine.

**Role in Android Graphics**

Every visible surface (View, SurfaceView, camera preview, video decoder output) ultimately dequeues a buffer, draws into it, queues it, and SurfaceFlinger (or GLConsumer) acquires and releases it. BufferQueue is the kernel of that producer–consumer pipeline. It avoids sending `GraphicBuffer` handles over Binder on every frame by mirroring slot state on both sides.

---

# High-Level Flow

```text
Producer (app / camera / codec)          Consumer (SF / GLConsumer / ImageReader)
─────────────────────────────────        ────────────────────────────────────────
dequeueBuffer(slot, fence)               acquireBuffer(item)
    → slot FREE → DEQUEUED                   → front of FIFO → ACQUIRED
requestBuffer(slot) → GraphicBuffer*       (wait on acquire fence)
    [allocate if BUFFER_NEEDS_REALLOCATION]
draw / encode into buffer
queueBuffer(slot, fence, metadata)       composite / sample / display
    → DEQUEUED → QUEUED                       
    → push BufferItem to mQueue          releaseBuffer(slot, fence)
                                             → ACQUIRED → FREE
cancelBuffer(slot, fence)                    → slot back on mFreeBuffers
    → DEQUEUED → FREE
```

Typical happy path per frame:

1. **Dequeue** — producer gets an empty slot + release fence (consumer finished reading).
2. **Request** — producer gets the `GraphicBuffer` pointer for that slot (may trigger gralloc alloc).
3. **Queue** — producer submits filled buffer + acquire fence; item enters FIFO; consumer notified.
4. **Acquire** — consumer takes oldest (or only) queued item; slot → ACQUIRED.
5. **Release** — consumer done; slot returns to FREE with release fence for producer.

---

# Public API

| Function | Side | Purpose | Notes |
|---|---|---|---|
| `createBufferQueue` | factory | Creates shared `BufferQueueCore` + producer + consumer | Entry point |
| `connect` / `disconnect` | producer | Attach EGL/CPU/camera/media API | Sets `mConnectedApi` |
| `dequeueBuffer` | producer | Get slot to write into | May return `BUFFER_NEEDS_REALLOCATION` |
| `requestBuffer` | producer | Get `GraphicBuffer` for dequeued slot | Must call after realloc flag |
| `queueBuffer` | producer | Submit frame to consumer | Builds `BufferItem`, pushes FIFO |
| `cancelBuffer` | producer | Return dequeued slot unused | DEQUEUED → FREE |
| `acquireBuffer` | consumer | Take next frame from queue | May drop stale frames |
| `releaseBuffer` | consumer | Return buffer to pool | Sets release fence |
| `setMaxDequeuedBufferCount` | producer | Limit in-flight producer buffers | Default 1 |
| `setMaxAcquiredBufferCount` | consumer | Limit in-flight consumer buffers | |
| `attachBuffer` / `detachBuffer` | both | Import/export buffers across processes | Advanced |

---

# Core Data Structures

## BufferQueueCore (shared state)

Both producer and consumer hold a `sp<BufferQueueCore>` and mirror `mSlots`.

| Variable | Meaning |
|---|---|
| `mMutex` | Protects all core state |
| `mSlots[64]` | Per-slot `GraphicBuffer`, fence, state, frame number |
| `mQueue` | FIFO of `BufferItem` (queued frames) |
| `mFreeSlots` | FREE slots with **no** buffer allocated |
| `mFreeBuffers` | FREE slots **with** a buffer (reuse candidates) |
| `mActiveBuffers` | Slots not in FREE state |
| `mMaxDequeuedBufferCount` | Max buffers producer holds dequeued |
| `mMaxAcquiredBufferCount` | Max buffers consumer holds acquired |
| `mAsyncMode` | Single-buffer queue; drop/replace instead of block |
| `mFrameCounter` | Monotonic frame number |
| `mConsumerListener` | Notified on `onFrameAvailable` / `onFrameReplaced` |
| `mDequeueCondition` | Producer waits here when no free slots |

## BufferSlot

| Field | Meaning |
|---|---|
| `mGraphicBuffer` | gralloc allocation (or null) |
| `mBufferState` | FREE / DEQUEUED / QUEUED / ACQUIRED / SHARED |
| `mFence` | Sync: producer must wait before writing; consumer before reading |
| `mFrameNumber` | Frame this slot last participated in (LRU ordering) |
| `mRequestBufferCalled` | Producer called `requestBuffer` after dequeue |

## BufferItem

Snapshot of a queued frame: slot, crop, transform, timestamp, fence, HDR metadata, etc. Copied into `mQueue` on `queueBuffer`, copied out on `acquireBuffer`.

---

# State Machine

From `BufferSlot.h` — tracked by `mDequeueCount`, `mQueueCount`, `mAcquireCount`, `mShared`:

```text
FREE       (0,0,0)  ──dequeueBuffer──►  DEQUEUED  (1,0,0)
                                           │
              ┌────────────────────────────┼────────────────────────────┐
              │ cancelBuffer             │ queueBuffer                  │
              ▼                          ▼                              │
           FREE ◄──────────────────  QUEUED  (0,1,0)                    │
              ▲                          │                              │
              │ releaseBuffer            │ acquireBuffer                │
              │                          ▼                              │
              └────────────────────  ACQUIRED (0,0,1) ──────────────────┘
                                         (detachBuffer → FREE slot, no buffer)
```

**SHARED mode:** one buffer reused in place; counts can overlap; used for static content / auto-refresh.

---

# Main Algorithm

## Slot selection (`waitForFreeSlotThenRelock`)

Loop until a slot is found or timeout/block:

1. Count dequeued/acquired buffers; reject if over `mMaxDequeuedBufferCount`.
2. Prefer **shared buffer slot** if in shared mode.
3. Else for dequeue: take from `mFreeBuffers` (reuse), else `mFreeSlots` (new alloc) if allowed.
4. If queue too deep or no slot → wait on `mDequeueCondition` (or `WOULD_BLOCK` in async).

## Frame lifecycle pseudocode

```text
// Producer
slot, fence = dequeue()
if flags & NEEDS_REALLOCATION:
    buf = allocate(w, h, format, usage)
else:
    buf = requestBuffer(slot)
render(buf, fence)
queueBuffer(slot, render_done_fence, crop, transform, timestamp)

// Consumer
item = acquire()          // pops mQueue front
wait(item.fence)
display(item)
releaseBuffer(item.slot, display_done_fence)
```

---

# Function Walkthrough

Distilled code — logging, validation, ATRACE, and feature-flag branches removed.

---

## `BufferQueue::createBufferQueue`

### Purpose
Factory: one `BufferQueueCore`, two faces (producer IPC + consumer IPC).

```cpp
void BufferQueue::createBufferQueue(sp<IGraphicBufferProducer>* outProducer,
                                    sp<IGraphicBufferConsumer>* outConsumer,
                                    bool consumerIsSurfaceFlinger) {
    sp<BufferQueueCore> core(new BufferQueueCore());
    sp<IGraphicBufferProducer> producer(new BufferQueueProducer(core, consumerIsSurfaceFlinger));
    sp<IGraphicBufferConsumer> consumer(new BufferQueueConsumer(core));
    *outProducer = producer;
    *outConsumer = consumer;
}
```

---

## `waitForFreeSlotThenRelock`

### Purpose
Find a slot for dequeue or attach; block until consumer releases one.

```cpp
status_t waitForFreeSlotThenRelock(FreeSlotCaller caller, lock, int* found) {
    while (true) {
        *found = INVALID_BUFFER_SLOT;

        if (mCore->mSharedBufferMode && mCore->mSharedBufferSlot != INVALID) {
            *found = mCore->mSharedBufferSlot;
        } else if (caller == Dequeue) {
            *found = getFreeBufferLocked();      // reuse existing allocation
            if (*found == INVALID && mCore->mAllowAllocation)
                *found = getFreeSlotLocked();    // empty slot → will alloc
        } else {
            *found = getFreeSlotLocked() ?: getFreeBufferLocked();
        }

        if (*found != INVALID && mCore->mQueue.size() <= maxBufferCount)
            return OK;

        mCore->mDequeueCondition.wait(lock);   // consumer released a buffer
    }
}

int getFreeBufferLocked() {
    if (mCore->mFreeBuffers.empty()) return INVALID;
    int slot = mCore->mFreeBuffers.front();
    mCore->mFreeBuffers.pop_front();
    return slot;
}
```

---

## `dequeueBuffer`

### Purpose
Producer obtains a slot to render into. Returns release fence (consumer finished previous use). May flag `BUFFER_NEEDS_REALLOCATION`.

### High-Level Steps
1. Resolve width/height/format/usage (defaults + consumer usage bits).
2. `waitForFreeSlotThenRelock` → `found` slot.
3. If existing buffer wrong size/format → clear slot, set realloc flag.
4. `mBufferState.dequeue()` — FREE → DEQUEUED.
5. Hand out `mFence` to producer; clear slot fence.
6. If realloc needed: allocate `GraphicBuffer` via gralloc, store in slot.

```cpp
status_t dequeueBuffer(int* outSlot, sp<Fence>* outFence,
                       uint32_t w, uint32_t h, PixelFormat format, uint64_t usage, ...) {
    lock(mCore->mMutex);

    usage |= mCore->mConsumerUsageBits;
    if (!w && !h) { w = mCore->mDefaultWidth; h = mCore->mDefaultHeight; }

    int found;
    while (found == INVALID)
        waitForFreeSlotThenRelock(Dequeue, lock, &found);

    const sp<GraphicBuffer>& buffer = mSlots[found].mGraphicBuffer;
    bool needsRealloc = !buffer || buffer->needsReallocation(w, h, format, 1, usage);

    mCore->mActiveBuffers.insert(found);
    *outSlot = found;
    mSlots[found].mBufferState.dequeue();

    status_t flags = OK;
    if (needsRealloc) {
        mSlots[found].mGraphicBuffer = nullptr;
        mCore->mIsAllocating = true;
        flags |= BUFFER_NEEDS_REALLOCATION;
    } else {
        mCore->mBufferAge = mCore->mFrameCounter + 1 - mSlots[found].mFrameNumber;
    }

    *outFence = mSlots[found].mFence;
    mSlots[found].mFence = Fence::NO_FENCE;
    unlock;

    if (flags & BUFFER_NEEDS_REALLOCATION) {
        sp<GraphicBuffer> gb = new GraphicBuffer(w, h, format, 1, usage, ...);
        lock;
        mSlots[*outSlot].mGraphicBuffer = gb;
        mCore->mIsAllocating = false;
        unlock;
    }
    return flags;
}
```

---

## `requestBuffer`

### Purpose
After dequeue (and after alloc if needed), producer fetches the `GraphicBuffer` pointer for the slot. Mirrors consumer-side slot table — no Binder transfer of the buffer handle each frame.

```cpp
status_t requestBuffer(int slot, sp<GraphicBuffer>* buf) {
    lock(mCore->mMutex);
    mSlots[slot].mRequestBufferCalled = true;
    *buf = mSlots[slot].mGraphicBuffer;
    return OK;
}
```

---

## `queueBuffer`

### Purpose
Producer submits a completed frame. Slot DEQUEUED → QUEUED. Item pushed to FIFO. Consumer gets `onFrameAvailable` (or `onFrameReplaced` in async drop mode).

### High-Level Steps
1. Validate slot is DEQUEUED and `requestBuffer` was called.
2. Store acquire fence on slot; `mBufferState.queue()`.
3. Build `BufferItem` from slot + input (crop, transform, timestamp, HDR, …).
4. Push to `mQueue`, or **replace** tail if async/droppable.
5. Notify consumer; wake blocked dequeuers.

```cpp
status_t queueBuffer(int slot, const QueueBufferInput& input, QueueBufferOutput* output) {
    input.deflate(..., &acquireFence, ...);

    lock(mCore->mMutex);

    mSlots[slot].mFence = acquireFence;
    mSlots[slot].mBufferState.queue();   // DEQUEUED → QUEUED

    ++mCore->mFrameCounter;
    BufferItem item;
    item.mGraphicBuffer = mSlots[slot].mGraphicBuffer;
    item.mCrop = crop;
    item.mTransform = transform;
    item.mTimestamp = requestedPresentTimestamp;
    item.mFrameNumber = mCore->mFrameCounter;
    item.mSlot = slot;
    item.mFence = acquireFence;
    item.mIsDroppable = mCore->mAsyncMode || mCore->mQueueBufferCanDrop;

    if (mCore->mQueue.empty()) {
        mCore->mQueue.push_back(item);
        listener = mCore->mConsumerListener;   // onFrameAvailable
    } else if (mCore->mQueue.back().mIsDroppable) {
        mSlots[last.mSlot].mBufferState.freeQueued();
        mCore->mFreeBuffers.push_back(last.mSlot);
        mCore->mQueue.back() = item;
        listener = mCore->mConsumerListener;   // onFrameReplaced
    } else {
        mCore->mQueue.push_back(item);
        listener = mCore->mConsumerListener;
    }

    mCore->mBufferHasBeenQueued = true;
    mCore->mDequeueCondition.notify_all();
    unlock;

    listener->onFrameAvailable(item);   // or onFrameReplaced
    return OK;
}
```

---

## `cancelBuffer`

### Purpose
Producer aborts a dequeued buffer without submitting a frame. DEQUEUED → FREE.

```cpp
status_t cancelBuffer(int slot, const sp<Fence>& fence) {
    lock(mCore->mMutex);

    mSlots[slot].mBufferState.cancel();
    mCore->mActiveBuffers.erase(slot);
    mCore->mFreeBuffers.push_back(slot);
    mSlots[slot].mFence = fence;   // producer's work fence, if any
    mCore->mDequeueCondition.notify_all();
    unlock;
    return OK;
}
```

---

## `acquireBuffer`

### Purpose
Consumer takes the next frame from `mQueue`. Slot QUEUED → ACQUIRED. May drop older queued frames if timestamps say they're late.

### High-Level Steps
1. Fail if queue empty (unless shared-buffer auto-refresh).
2. Optionally drop `mQueue[0]` while `mQueue[1]` is still on time (frame dropping).
3. Pop front `BufferItem`; `mBufferState.acquire()`.
4. Clear `GraphicBuffer` from item if already acquired once (avoid re-import).
5. Wake producer waiting for free slots.

```cpp
status_t acquireBuffer(BufferItem* outBuffer, nsecs_t expectedPresent, ...) {
    lock(mCore->mMutex);

    if (mCore->mQueue.empty()) return NO_BUFFER_AVAILABLE;

    // Drop stale frames when multiple queued and timestamps allow
    while (mCore->mQueue.size() > 1 && shouldDrop(mCore->mQueue[1], expectedPresent)) {
        mSlots[mCore->mQueue[0].mSlot].mBufferState.freeQueued();
        mCore->mFreeBuffers.push_back(mCore->mQueue[0].mSlot);
        mCore->mQueue.erase(mCore->mQueue.begin());
    }

    BufferItem& front = mCore->mQueue[0];
    *outBuffer = front;

    mSlots[front.mSlot].mBufferState.acquire();   // QUEUED → ACQUIRED
    mSlots[front.mSlot].mFence = Fence::NO_FENCE;

    if (outBuffer->mAcquireCalled)
        outBuffer->mGraphicBuffer = nullptr;   // already mapped on consumer side

    mCore->mQueue.erase(mCore->mQueue.begin());
    mCore->mDequeueCondition.notify_all();
    unlock;
    return OK;
}
```

---

## `releaseBuffer`

### Purpose
Consumer finished with buffer. ACQUIRED → FREE. Slot returns to `mFreeBuffers` with release fence for producer's next dequeue.

```cpp
status_t releaseBuffer(int slot, uint64_t frameNumber, const sp<Fence>& releaseFence, ...) {
    lock(mCore->mMutex);

    mSlots[slot].mFence = releaseFence;
    mSlots[slot].mBufferState.release();   // ACQUIRED → FREE

    mCore->mActiveBuffers.erase(slot);
    mCore->mFreeBuffers.push_back(slot);
    mCore->mDequeueCondition.notify_all();
    unlock;

    mConnectedProducerListener->onBufferReleased();   // optional
    return OK;
}
```

---

# Call Flow

**Who calls producer side:**
- `Surface::dequeueBuffer` / `ANativeWindow` → `IGraphicBufferProducer`
- Camera / MediaCodec → `IGraphicBufferProducer` directly

**Who calls consumer side:**
- `SurfaceFlinger` (via `BLASTBufferQueue` / `BufferQueueConsumer`)
- `GLConsumer` (TextureView / ExternalTexture)
- `ImageReader` / `CpuConsumer`

**Typical stack:**

```text
App (View / SurfaceView / Camera)
    ↓
Surface / ANativeWindow
    ↓
IGraphicBufferProducer  ←── BufferQueueProducer
    ↓
BufferQueueCore (mSlots, mQueue, fences)
    ↓
BufferQueueConsumer  ←── IGraphicBufferConsumer
    ↓
SurfaceFlinger / GLConsumer / ImageReader
    ↓
HWComposer / GPU / CPU
```

**Gralloc touchpoint:** `dequeueBuffer` → `new GraphicBuffer(...)` → `GraphicBufferAllocator` → IAllocator/IMapper HAL.

---

# Locking / Concurrency

| Lock | Protects |
|---|---|
| `BufferQueueCore::mMutex` | All slot state, queue, free lists, counters |
| `BufferQueueProducer::mCallbackMutex` | Ordered `onFrameAvailable` callbacks |
| Fences | Cross-process/GPU sync without holding mutex during GPU work |

**Producer** may block in `dequeueBuffer` on `mDequeueCondition` when all slots are dequeued/queued/acquired up to `maxBufferCount`.

**Consumer** runs on SF render thread / GL thread; `acquireBuffer` is non-blocking unless queue empty.

**Async mode:** producer rarely blocks; `queueBuffer` drops/replaces previous frame instead of growing queue.

---

# Memory Ownership

| Object | Owner |
|---|---|
| `BufferQueueCore` | `sp<>` shared by producer + consumer halves |
| `GraphicBuffer` | Ref-counted; lives in `mSlots[slot]` while slot active |
| Slot index | Producer and consumer mirror the same slot array |
| `BufferItem` in queue | Copy of metadata; may null out `mGraphicBuffer` after first acquire |

Producer **creates** buffers (via gralloc on realloc). Consumer **never frees** gralloc memory directly — `releaseBuffer` returns slot to pool. `clearBufferSlotLocked` frees when slot torn down.

---

# Error Handling

Important failure cases (validation omitted in distilled code above):

- `NO_INIT` — queue abandoned or producer not connected
- `WOULD_BLOCK` / `TIMED_OUT` — no free slot, non-blocking dequeue
- `BUFFER_NEEDS_REALLOCATION` — not an error; producer must `requestBuffer` after alloc
- `NO_BUFFER_AVAILABLE` — consumer acquire with empty queue
- `PRESENT_LATER` — timestamp not yet due
- `STALE_BUFFER_SLOT` — release after buffer reallocated on same slot
- `INVALID_OPERATION` — too many dequeued or acquired buffers

---

# Performance Notes

| Topic | Behavior |
|---|---|
| **Allocations** | Lazy — only on first use or size/format change (`needsReallocation`) |
| **Copies** | No pixel copy in BufferQueue; only metadata + fence handoff |
| **Sync** | Fences avoid CPU stalls; EGL may throttle to 2 buffers in flight |
| **Caching** | `mFreeBuffers` reuses same gralloc allocation across frames |
| **Fast path** | Reuse free buffer, same dimensions, sync queue depth 1 |
| **Slow path** | gralloc alloc, blocking dequeue, frame drop loop in acquire |
| **Async** | Replace last queued buffer — lower latency, possible frame drop |
| **Buffer age** | Returned in dequeue for partial repaint hints |

---

# Questions

- [ ] How does `BLASTBufferQueue` differ from classic `Surface` → BQ path?
- [ ] When does `mGraphicBuffer = nullptr` on acquire break cross-process buffer passing?
- [ ] Exact `maxBufferCount` formula from `mMaxDequeued + mMaxAcquired + 1`?
- [ ] Shared buffer mode — who uses it in production (static wallpaper)?

---

# Related Concepts

- [[GraphicBuffer]] / gralloc allocator + mapper
- [[Fence]] — sync file between GPU and compositor
- [[SurfaceFlinger]] — primary consumer
- [[ANativeWindow]] — NDK wrapper over producer API
- [[Triple buffering]] — why `mMaxDequeuedBufferCount` ≥ 1 and undequeued reserve exists
