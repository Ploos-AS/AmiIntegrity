# AmiIntegrity Roadmap

## Design principles

AmiIntegrity is a classic-Amiga file-integrity monitor. It should be useful on modest real hardware, so the core must avoid heavyweight runtime requirements and keep baseline/report formats transparent.

Integrity checks must distinguish content changes from metadata changes where practical. Baselines are evidence and should never be silently rewritten after a mismatch.

ARexx support is a project requirement. The integrity engine and CLI must remain fully usable without RexxMast, while systems with RexxMast should expose a documented `AMIINTEGRITY` public port. Common commands should include `VERSION`, `STATUS` and `HELP`; integrity operations should become scriptable as their CLI equivalents mature. ARexx checks must never silently approve or rewrite a changed baseline.

## M0 — Foundation

Acceptance criteria:

- Scope and supported direction documented.
- MIT license present.
- Repository structure established.
- Baseline format draft documented.
- Example monitoring profile present.
- Example baseline record present.
- ARexx is recorded as a required automation interface, while integrity operation remains independent of RexxMast.
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

## M7 — ARexx and integration

Implement and qualify the required `AMIINTEGRITY` ARexx port. At minimum expose `VERSION`, `STATUS` and `HELP`, plus appropriate integrity operations such as `INIT`, `CHECK`, `DIFF` and report/status retrieval. Baseline replacement/update must remain an explicit operation and must never happen as a side effect of `CHECK` or `DIFF`. Document arguments, results and return codes.

RexxMast is optional: CLI scanning and verification must continue to work without it. Add optional integration hooks for AmiGuard and AmiForensics; integrations must remain optional.

## M8 — Runtime qualification

Qualify supported AmigaOS/CPU combinations under emulation and selected real hardware. Qualification should cover both ARexx operation with RexxMast and ordinary CLI operation without RexxMast.

## M9 — Release

Produce installation documentation, release archive, checksums and first public release.
