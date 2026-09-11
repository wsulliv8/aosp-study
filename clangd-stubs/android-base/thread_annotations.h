#pragma once

// Thread-annotation stubs for IDE parsing (no-ops).
#ifndef GUARDED_BY
#define GUARDED_BY(x)
#endif
#ifndef PT_GUARDED_BY
#define PT_GUARDED_BY(x)
#endif
#ifndef REQUIRES
#define REQUIRES(...)
#endif
#ifndef EXCLUDES
#define EXCLUDES(...)
#endif
#ifndef ACQUIRE
#define ACQUIRE(...)
#endif
#ifndef RELEASE
#define RELEASE(...)
#endif
#ifndef ASSERT_CAPABILITY
#define ASSERT_CAPABILITY(x)
#endif
#ifndef RETURN_CAPABILITY
#define RETURN_CAPABILITY(x)
#endif
#ifndef CAPABILITY
#define CAPABILITY(x)
#endif
#ifndef SCOPED_CAPABILITY
#define SCOPED_CAPABILITY
#endif
#ifndef NO_THREAD_SAFETY_ANALYSIS
#define NO_THREAD_SAFETY_ANALYSIS
#endif
