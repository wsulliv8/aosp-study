# clangd stubs

Minimal header stubs for IDE navigation in this partial AOSP checkout
(`native/` + `interfaces/`, without full `system/core` / generated AIDL).

## Setup

- Root `.clangd` points include paths at these stubs and real tree headers.
- Root `compile_commands.json` lists key `libgui` / `libui` sources so
  **Go to Definition / Implementation** works (e.g. `BufferQueueProducer.h`
  → `BufferQueueProducer.cpp`).

After changing stubs or `compile_commands.json`:

1. Command Palette → **clangd: Restart language server**
2. Or **Developer: Reload Window**
3. If still stale: delete `~/.cache/clangd` and restart

## Not for building

These stubs are **not** used by Soong/Make. Real device builds use the
full Android tree and generated headers.

## Regenerating AIDL enum stubs

```bash
python3 clangd-stubs/generate_aidl_stubs.py
```

Then hand-maintain parcelable stubs (`ExtendableType`, `Smpte2086`, etc.).
