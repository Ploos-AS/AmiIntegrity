# AmiIntegrity baseline format — draft v0

M0 defines a simple text representation intended to be easy to parse on classic AmigaOS and easy to inspect manually.

The format is not yet frozen for public compatibility.

## Header

```text
format=0
profile=system
created=UNSET
hashes=crc32,sha256
```

`created=UNSET` is allowed only in example/test data during early milestones.

## File records

Each record starts with `[entry]` and uses `key=value` fields:

```text
[entry]
path=S:Startup-Sequence
type=file
size=1234
datestamp=UNSET
protection=----rwed
comment=
crc32=UNSET
sha256=UNSET
```

Candidate keys:

- `path`: Amiga path exactly as recorded.
- `type`: initially `file` or `dir`.
- `size`: byte size for files.
- `datestamp`: canonical AmiIntegrity representation of the Amiga datestamp.
- `protection`: protection-bit representation.
- `comment`: filesystem comment when available.
- `crc32`: hexadecimal CRC32.
- `sha256`: hexadecimal SHA-256.

## Comparison model

Later milestones must distinguish at least:

- `OK`: current object matches baseline.
- `NEW`: current object was not in the baseline.
- `REMOVED`: baseline object no longer exists.
- `MODIFIED`: content differs.
- `METADATA`: content is unchanged but tracked metadata differs.
- `ERROR`: object could not be checked reliably.

Exact precedence is defined when M3 is implemented.

## Trust rules

A baseline is evidence, not a cache.

- A failed integrity check must never silently update the baseline.
- Baseline creation/replacement must be an explicit operation.
- Malformed or truncated baselines must fail closed and be reported.
- `UNSET` hashes are permitted only in example/development data and must never be interpreted as successful verification.
- Unknown fields should be handled predictably; compatibility policy will be frozen before release.
