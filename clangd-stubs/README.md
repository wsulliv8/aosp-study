# clangd stubs

Minimal header stubs for IDE navigation in this partial AOSP checkout.

This tree includes `native/` and `interfaces/` but not `system/core` (libutils,
libcutils, libbase, etc.). The stubs in this directory let clangd parse common
includes so Go to Definition works for most of `libgui`, `libui`, and
SurfaceFlinger.

These files are **not** used for building — only for clangd indexing.

If you have a full AOSP tree, prefer generating `compile_commands.json` from
Soong and pointing `.clangd` at it instead.
