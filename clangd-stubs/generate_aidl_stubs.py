#!/usr/bin/env python3
"""Generate minimal AIDL C++ enum stubs for clangd from .aidl sources."""

import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
AIDL_DIR = ROOT / "interfaces/graphics/common/aidl/android/hardware/graphics/common"
OUT_DIR = Path(__file__).resolve().parent / "aidl/android/hardware/graphics/common"


def parse_enum(aidl_path: Path) -> tuple[str, list[tuple[str, int | None]]] | None:
    text = aidl_path.read_text()
    name_match = re.search(r"enum\s+(\w+)\s*\{", text)
    if not name_match:
        return None
    enum_name = name_match.group(1)
    values: list[tuple[str, int | None]] = []
    for line in text.splitlines():
        line = re.sub(r"/\*.*?\*/", "", line)
        line = re.sub(r"//.*", "", line).strip()
        if not line or line.startswith("@"):
            continue
        m = re.match(r"(\w+)\s*=\s*(-?\d+)\s*,?\s*$", line)
        if m:
            values.append((m.group(1), int(m.group(2))))
        elif re.match(r"(\w+)\s*,?\s*$", line):
            values.append((line.rstrip(","), None))
    return enum_name, values


def emit_header(enum_name: str, values: list[tuple[str, int | None]]) -> str:
    lines = [
        "#pragma once",
        "",
        "#include <cstdint>",
        "",
        "namespace aidl {",
        "namespace android {",
        "namespace hardware {",
        "namespace graphics {",
        "namespace common {",
        "",
        f"enum class {enum_name} : int32_t {{",
    ]
    next_val = 0
    for ident, val in values:
        if val is None:
            val = next_val
        lines.append(f"    {ident} = {val},")
        next_val = val + 1
    lines += [
        "};",
        "",
        "}  // namespace common",
        "}  // namespace graphics",
        "}  // namespace hardware",
        "}  // namespace android",
        "}  // namespace aidl",
        "",
    ]
    return "\n".join(lines)


def main() -> int:
    OUT_DIR.mkdir(parents=True, exist_ok=True)
    if not AIDL_DIR.is_dir():
        print(f"missing AIDL dir: {AIDL_DIR}", file=sys.stderr)
        return 1
    for aidl in sorted(AIDL_DIR.glob("*.aidl")):
        parsed = parse_enum(aidl)
        if parsed is None:
            continue
        enum_name, values = parsed
        out = OUT_DIR / f"{enum_name}.h"
        out.write_text(emit_header(enum_name, values))
        print(out)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
