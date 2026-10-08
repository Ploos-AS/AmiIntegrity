#!/bin/sh
set -eu
tmp="${TMPDIR:-/tmp}/hashguard-sha256-$$"
trap 'rm -f "$tmp"' EXIT HUP INT TERM
cc -std=c99 -Wall -Wextra -Werror -pedantic -Iinclude src/hashguard_sha256.c tests/test_sha256.c -o "$tmp"
"$tmp"
