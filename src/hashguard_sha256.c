#include "hashguard_sha256.h"
#include <string.h>
#define ROTR(x,n) (((x) >> (n)) | ((x) << (32U-(n))))
static const uint32_t k[64] = {
0x428a2f98U,0x71374491U,0xb5c0fbcfU,0xe9b5dba5U,0x3956c25bU,0x59f111f1U,0x923f82a4U,0xab1c5ed5U,
0xd807aa98U,0x12835b01U,0x243185beU,0x550c7dc3U,0x72be5d74U,0x80deb1feU,0x9bdc06a7U,0xc19bf174U,
0xe49b69c1U,0xefbe4786U,0x0fc19dc6U,0x240ca1ccU,0x2de92c6fU,0x4a7484aaU,0x5cb0a9dcU,0x76f988daU,
0x983e5152U,0xa831c66dU,0xb00327c8U,0xbf597fc7U,0xc6e00bf3U,0xd5a79147U,0x06ca6351U,0x14292967U,
0x27b70a85U,0x2e1b2138U,0x4d2c6dfcU,0x53380d13U,0x650a7354U,0x766a0abbU,0x81c2c92eU,0x92722c85U,
0xa2bfe8a1U,0xa81a664bU,0xc24b8b70U,0xc76c51a3U,0xd192e819U,0xd6990624U,0xf40e3585U,0x106aa070U,
0x19a4c116U,0x1e376c08U,0x2748774cU,0x34b0bcb5U,0x391c0cb3U,0x4ed8aa4aU,0x5b9cca4fU,0x682e6ff3U,
0x748f82eeU,0x78a5636fU,0x84c87814U,0x8cc70208U,0x90befffaU,0xa4506cebU,0xbef9a3f7U,0xc67178f2U
};
static uint32_t load32(const unsigned char *p) {
    return ((uint32_t)p[0]<<24)|((uint32_t)p[1]<<16)|((uint32_t)p[2]<<8)|(uint32_t)p[3];
}
static void store32(unsigned char *p, uint32_t x) {
    p[0]=(unsigned char)(x>>24);p[1]=(unsigned char)(x>>16);p[2]=(unsigned char)(x>>8);p[3]=(unsigned char)x;
}
static void block(hashguard_sha256_ctx *ctx, const unsigned char *p) {
    uint32_t w[64],a,b,c,d,e,f,g,h,t1,t2,s0,s1,ch,maj;
    unsigned i;
    for(i=0;i<16;i++) w[i]=load32(p+4*i);
    for(i=16;i<64;i++) {
        s0=ROTR(w[i-15],7)^ROTR(w[i-15],18)^(w[i-15]>>3);
        s1=ROTR(w[i-2],17)^ROTR(w[i-2],19)^(w[i-2]>>10);
        w[i]=w[i-16]+s0+w[i-7]+s1;
    }
    a=ctx->state[0];b=ctx->state[1];c=ctx->state[2];d=ctx->state[3];
    e=ctx->state[4];f=ctx->state[5];g=ctx->state[6];h=ctx->state[7];
    for(i=0;i<64;i++) {
        s1=ROTR(e,6)^ROTR(e,11)^ROTR(e,25);ch=(e&f)^(~e&g);
        t1=h+s1+ch+k[i]+w[i];
        s0=ROTR(a,2)^ROTR(a,13)^ROTR(a,22);maj=(a&b)^(a&c)^(b&c);
        t2=s0+maj;
        h=g;g=f;f=e;e=d+t1;d=c;c=b;b=a;a=t1+t2;
    }
    ctx->state[0]+=a;ctx->state[1]+=b;ctx->state[2]+=c;ctx->state[3]+=d;
    ctx->state[4]+=e;ctx->state[5]+=f;ctx->state[6]+=g;ctx->state[7]+=h;
}
void hashguard_sha256_init(hashguard_sha256_ctx *ctx) {
    static const uint32_t iv[8]={0x6a09e667U,0xbb67ae85U,0x3c6ef372U,0xa54ff53aU,
        0x510e527fU,0x9b05688cU,0x1f83d9abU,0x5be0cd19U};
    memcpy(ctx->state,iv,sizeof iv);ctx->total_bytes=0;ctx->used=0;
}
void hashguard_sha256_update(hashguard_sha256_ctx *ctx,const void *data,size_t len) {
    const unsigned char *p=(const unsigned char *)data;
    size_t n;
    ctx->total_bytes+=(uint64_t)len;
    while(len) {
        n=64-ctx->used;if(n>len)n=len;
        memcpy(ctx->buffer+ctx->used,p,n);ctx->used+=n;p+=n;len-=n;
        if(ctx->used==64) {block(ctx,ctx->buffer);ctx->used=0;}
    }
}
void hashguard_sha256_final(hashguard_sha256_ctx *ctx,unsigned char digest[32]) {
    uint64_t bits=ctx->total_bytes*8U;
    unsigned i;
    ctx->buffer[ctx->used++]=0x80U;
    if(ctx->used>56) {
        memset(ctx->buffer+ctx->used,0,64-ctx->used);
        block(ctx,ctx->buffer);ctx->used=0;
    }
    memset(ctx->buffer+ctx->used,0,56-ctx->used);
    for(i=0;i<8;i++)ctx->buffer[56+i]=(unsigned char)(bits>>(56-8*i));
    block(ctx,ctx->buffer);
    for(i=0;i<8;i++)store32(digest+4*i,ctx->state[i]);
    memset(ctx,0,sizeof *ctx);
}
void hashguard_sha256(const void *data,size_t len,unsigned char digest[32]) {
    hashguard_sha256_ctx ctx;hashguard_sha256_init(&ctx);
    hashguard_sha256_update(&ctx,data,len);hashguard_sha256_final(&ctx,digest);
}
