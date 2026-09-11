#!/usr/bin/env python3
"""AmiIntegrity M0 repository qualification gate."""

from pathlib import Path
import sys

ROOT = Path(__file__).resolve().parents[1]

REQUIRED = [
    "README.md",
    "LICENSE",
    "docs/ROADMAP.md",
    "docs/BASELINE_FORMAT.md",
    "profiles/system.profile",
    "examples/baseline.example",
    "src/README.md",
    "include/README.md",
    "tools/check_m0.py",
]


def fail(message: str) -> None:
    print(f"M0 FAIL: {message}")
    raise SystemExit(1)


def main() -> int:
    missing = [name for name in REQUIRED if not (ROOT / name).is_file()]
    if missing:
        fail("missing required files: " + ", ".join(missing))

    readme = (ROOT / "README.md").read_text(encoding="utf-8")
    for marker in ("AmigaOS 2.04+", "68000", "CRC32", "SHA-256", "M0"):
        if marker not in readme:
            fail(f"README missing marker: {marker}")

    profile = (ROOT / "profiles/system.profile").read_text(encoding="utf-8")
    for marker in ("S:Startup-Sequence", "S:User-Startup", "C:", "L:", "LIBS:", "DEVS:", "ENVARC:"):
        if marker not in profile:
            fail(f"system profile missing target: {marker}")

    baseline = (ROOT / "examples/baseline.example").read_text(encoding="utf-8")
    for marker in ("format=0", "[entry]", "path=S:Startup-Sequence", "crc32=UNSET", "sha256=UNSET"):
        if marker not in baseline:
            fail(f"example baseline missing marker: {marker}")

    design = (ROOT / "docs/BASELINE_FORMAT.md").read_text(encoding="utf-8")
    for marker in ("NEW", "REMOVED", "MODIFIED", "METADATA", "must never silently update the baseline"):
        if marker not in design:
            fail(f"baseline design missing marker: {marker}")

    print("M0 PASS")
    return 0


if __name__ == "__main__":
    sys.exit(main())
