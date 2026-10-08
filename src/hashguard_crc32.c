#include "hashguard_crc32.h"

uint32_t hashguard_crc32_init(void)
{
    return UINT32_C(0xffffffff);
}

uint32_t hashguard_crc32_update(uint32_t state, const void *data, size_t length)
{
    const unsigned char *bytes = (const unsigned char *)data;
    size_t i;
    unsigned bit;

    for (i = 0; i < length; ++i) {
        state ^= (uint32_t)bytes[i];
        for (bit = 0; bit < 8; ++bit) {
            state = (state >> 1) ^ ((state & 1U) ? UINT32_C(0xedb88320) : 0U);
        }
    }
    return state;
}

uint32_t hashguard_crc32_final(uint32_t state)
{
    return state ^ UINT32_C(0xffffffff);
}

uint32_t hashguard_crc32(const void *data, size_t length)
{
    return hashguard_crc32_final(hashguard_crc32_update(hashguard_crc32_init(), data, length));
}
