# AmiIntegrity Roadmap

## Design principles

AmiIntegrity is a classic-Amiga file-integrity monitor. It should be useful on modest real hardware, so the core must avoid heavyweight runtime requirements and keep baseline/report formats transparent.

Integrity checks must distinguish content changes from metadata changes where practical. Baselines are evidence and should never be silently rewritten after a mismatch.

## M0 — Foundation

Acceptance criteria:

- Scope and supported direction documented.
- MIT license present.
- Repository structure established.
- Baseline format draft documented.
- Example monitoring profile present.
- Example baseline record present.
- Host-side `tools/check_m0.py` validates the repository contract.
- M0 makes no claim that hashing or recursive scanning is implemented.

## M1 — Core hashing

Implement portable file metadata collection and hashing primitives with deterministic test vectors. Initial targets:

- CRC32
- SHA-256
- file size
- metadata representation

The implementation should remain suitable for a 68000 build.

## M2 — Baseline engine

Create, save and load baseline databases. Add recursive traversal, stable ordering and exclusion handling.

## M3 — Integrity check

Compare current state with a stored baseline and classify at least:

- NEW
- REMOVED
- MODIFIED
- METADATA
- OK

## M4 — Profiles

Add configurable system and custom profiles, include/exclude rules and safe defaults for common system locations.

## M5 — Reporting

Provide concise console output plus a stable machine-readable representation suitable for downstream tooling.

## M6 — Operational hardening

Protect baseline replacement, detect corrupt/truncated baseline files, handle inaccessible files explicitly and bound memory/path usage.

## M7 — Integration

Add ARexx where useful and optional integration hooks for AmiGuard and AmiForensics. Integrations must remain optional.

## M8 — Runtime qualification

Qualify supported AmigaOS/CPU combinations under emulation and selected real hardware.

## M9 — Release

Produce installation documentation, release archive, checksums and first public release.
