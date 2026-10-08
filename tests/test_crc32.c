#include "hashguard_crc32.h"
#include <stdio.h>
#include <string.h>

static int check(const char *name, const char *data, uint32_t expected)
{
    uint32_t actual = hashguard_crc32(data, strlen(data));
    if (actual != expected) {
        fprintf(stderr, "%s: expected %08lx, got %08lx\n",
                name, (unsigned long)expected, (unsigned long)actual);
        return 1;
    }
    return 0;
}

int main(void)
{
    uint32_t state;
    int failures = 0;

    failures += check("empty", "", UINT32_C(0x00000000));
    failures += check("123456789", "123456789", UINT32_C(0xcbf43926));
    failures += check("abc", "abc", UINT32_C(0x352441c2));

    state = hashguard_crc32_init();
    state = hashguard_crc32_update(state, "1234", 4);
    state = hashguard_crc32_update(state, "56789", 5);
    if (hashguard_crc32_final(state) != UINT32_C(0xcbf43926)) {
        fprintf(stderr, "chunked CRC32 mismatch\n");
        ++failures;
    }
    if (failures) return 1;
    puts("CRC32 PASS");
    return 0;
}
