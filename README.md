# AmiIntegrity

AmiIntegrity is a lightweight file-integrity monitoring and baseline verification tool for classic AmigaOS.

The project is inspired by host-integrity tools such as Tripwire, but is designed specifically for classic Amiga systems and their filesystem, startup and protection-bit conventions.

## Project goals

- Classic AmigaOS first.
- Target AmigaOS 2.04+ where practical.
- Target 68000 and higher CPUs where practical.
- Create trusted baselines of selected files and directories.
- Detect files that are new, removed or modified relative to a baseline.
- Record useful Amiga metadata such as protection bits and comments where practical.
- Keep the native client small enough for real classic hardware.
- Make reports machine-readable as well as human-readable.
- Integrate cleanly with AmiGuard and AmiForensics without making either a hard dependency.
- Add ARexx integration where useful and technically appropriate.

## Initial monitoring targets

A default system profile is expected to cover important locations such as:

```text
S:Startup-Sequence
S:User-Startup
C:
L:
LIBS:
DEVS:
WBStartup/
ENVARC:
```

The exact default set will be qualified before release and must remain configurable.

## Planned command model

The exact CLI is not frozen yet. The intended model is:

```text
AmiIntegrity version
AmiIntegrity init <path|profile>
AmiIntegrity check <path|profile>
AmiIntegrity verify <path>
AmiIntegrity diff
AmiIntegrity status
```

A later release may also provide shorter aliases, but M0 does not freeze those names.

## Baseline data

A baseline record is expected to capture enough information to detect meaningful changes without requiring a heavy database engine. Candidate fields include:

- path
- object type
- size
- datestamp
- protection bits
- file comment, where practical
- CRC32 for inexpensive change detection
- SHA-256 for stronger verification where supported by the implementation

M0 defines the format contract only. Hashing and filesystem scanning are implemented in later milestones.

## Repository layout

```text
src/                 Native Amiga client source
include/             Headers
docs/                Design and milestone documentation
profiles/            Monitoring profiles
examples/            Example baseline/report data
tools/               Host-side qualification/development tools
```

## Milestones

- **M0 — Foundation:** scope, data model, profiles, repository structure and validation gate.
- **M1 — Core hashing:** file metadata collection plus CRC32/SHA-256 primitives and host tests.
- **M2 — Baseline engine:** recursively create and load trusted baselines.
- **M3 — Integrity check:** classify NEW/REMOVED/MODIFIED/METADATA changes.
- **M4 — Profiles:** system/default/custom monitoring profiles and exclusions.
- **M5 — Reporting:** stable text and machine-readable report formats.
- **M6 — Operational hardening:** safe baseline replacement, corruption handling and resource limits.
- **M7 — Integration:** ARexx and optional AmiGuard/AmiForensics integration.
- **M8 — Runtime qualification:** emulator/real-Amiga qualification across supported OS/CPU profiles.
- **M9 — Release:** documentation, packaging and first public release.

See [docs/ROADMAP.md](docs/ROADMAP.md).

## M0 status

M0 is a design and repository baseline only. It intentionally does **not** claim to scan files or calculate hashes yet.

Run the host-side gate with:

```sh
python3 tools/check_m0.py
```

Expected result:

```text
M0 PASS
```

## License

MIT. See [LICENSE](LICENSE).

Copyright (c) 2026 Ploos AS.
