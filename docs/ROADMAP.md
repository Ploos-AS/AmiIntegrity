# HashGuard Roadmap

## Design principles

HashGuard is a cross-platform file-integrity monitor, initially targeting classic AmigaOS. It should be useful on modest real hardware, so the core must avoid heavyweight runtime requirements and keep baseline/report formats transparent.

Integrity checks must distinguish content changes from metadata changes where practical. Baselines are evidence and should never be silently rewritten after a mismatch.

ARexx support is a project requirement. The integrity engine and CLI must remain fully usable without RexxMast, while systems with RexxMast should expose a documented `HASHGUARD` public port. Common commands should include `VERSION`, `STATUS` and `HELP`; integrity operations should become scriptable as their CLI equivalents mature. ARexx checks must never silently approve or rewrite a changed baseline.

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

Implement and qualify the required `HASHGUARD` ARexx port. At minimum expose `VERSION`, `STATUS` and `HELP`, plus appropriate integrity operations such as `INIT`, `CHECK`, `DIFF` and report/status retrieval. Baseline replacement/update must remain an explicit operation and must never happen as a side effect of `CHECK` or `DIFF`. Document arguments, results and return codes.

RexxMast is optional: CLI scanning and verification must continue to work without it. Add optional integration hooks for AmiGuard and AmiForensics; integrations must remain optional.

## M8 — Runtime qualification

Qualify supported AmigaOS/CPU combinations under emulation and selected real hardware. Qualification should cover both ARexx operation with RexxMast and ordinary CLI operation without RexxMast.

## M9 — Release

Produce installation documentation, release archive, checksums and first public release.


## M10 — Portable core and multi-platform architecture

Preserve AmigaOS 2.04+ and 68000 as the primary baseline. Separate hashing, baseline, comparison and reporting logic from operating-system interfaces in portable C. Coordinate with the proposed CrossApp SDK without making it a hard dependency. Define deterministic cross-platform test vectors, and document metadata, paths and timestamp semantics.

## M11 — Amiga-family and AxiomicaOS ports

Produce separate native builds for AmigaOS 4.x (PowerPC), MorphOS (PowerPC), AROS 68k and supported AROS x86/x86-64 targets. Add an AxiomicaOS adapter and native package when its SDK and ABI are ready. Keep CLI support independent of any GUI; MUI/Zune and native GUI integrations may follow.

## M12 — Haiku port

Target native Haiku x86-64 with an OS adapter, packaging and runtime tests. Consider an optional Interface Kit GUI. Haiku/m68k remains conditional on a functioning OS port and toolchain.

## M13 — Multi-platform CI and qualification

Build a platform matrix distinguishing planned, cross-compiled and runtime-qualified targets. Validate identical file hashes and baseline/report semantics across supported OSes, using emulators and physical machines where possible. Publish separate archives and checksums.

## M14 — Atari TOS / GEMDOS baseline

Introduce a native Atari m68k build using GEMDOS for filesystem access, with classic Atari ST/STE as the baseline. Add TOS-aware path, FAT timestamp and attribute handling; keep memory requirements modest and the CLI usable without GEM.

## M15 — EmuTOS, FreeMiNT and alternative Atari environments

Qualify the TOS build under EmuTOS and FreeMiNT. Add MiNT-specific adapters only where necessary (long filenames, richer metadata, process/file semantics). Test MultiTOS, MagiC, Geneva and relevant AES environments as compatibility targets rather than assuming each needs a separate port.

## M16 — Atari GEM/AES GUI

Add an optional GEM/AES user interface that works on classic TOS and is tested with EmuTOS and FreeMiNT/XaAES. Keep all integrity operations usable from the CLI.

## M17 — Atari CI and release

Qualify in Hatari and ARAnyM where appropriate, plus real ST/STE/TT/Falcon hardware when available. Publish Atari-specific packages, test evidence and compatibility notes. Never treat cross-compilation alone as runtime qualification.

M10–M17 must not delay the classic Amiga M0–M9 release. All future ports share the portable core, not an executable binary.
