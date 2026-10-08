#ifndef HASHGUARD_SHA256_H
#define HASHGUARD_SHA256_H
#include <stddef.h>
#include <stdint.h>
typedef struct {
    uint32_t state[8];
    uint64_t total_bytes;
    unsigned char buffer[64];
    size_t used;
} hashguard_sha256_ctx;
void hashguard_sha256_init(hashguard_sha256_ctx *ctx);
void hashguard_sha256_update(hashguard_sha256_ctx *ctx, const void *data, size_t len);
void hashguard_sha256_final(hashguard_sha256_ctx *ctx, unsigned char digest[32]);
void hashguard_sha256(const void *data, size_t len, unsigned char digest[32]);
#endif
