#!/bin/sh
set -eu
tmp="${TMPDIR:-/tmp}/hashguard-crc32-$$"
trap 'rm -f "$tmp"' EXIT HUP INT TERM
cc -std=c99 -Wall -Wextra -Werror -pedantic -Iinclude src/hashguard_crc32.c tests/test_crc32.c -o "$tmp"
"$tmp"
