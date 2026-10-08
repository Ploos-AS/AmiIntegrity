#ifndef HASHGUARD_CRC32_H
#define HASHGUARD_CRC32_H

#include <stddef.h>
#include <stdint.h>

/* IEEE CRC-32 (reflected polynomial 0xEDB88320).
 * Start with hashguard_crc32_init(), update with arbitrary chunks,
 * then call hashguard_crc32_final(). */
uint32_t hashguard_crc32_init(void);
uint32_t hashguard_crc32_update(uint32_t state, const void *data, size_t length);
uint32_t hashguard_crc32_final(uint32_t state);
uint32_t hashguard_crc32(const void *data, size_t length);

#endif
