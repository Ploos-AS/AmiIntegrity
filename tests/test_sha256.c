#include "hashguard_sha256.h"
#include <stdio.h>
#include <string.h>
static int verify(const char *label,const char *input,const char *expected) {
    unsigned char digest[32];char hex[65];unsigned i;
    hashguard_sha256(input,strlen(input),digest);
    for(i=0;i<32;i++)sprintf(hex+2*i,"%02x",(unsigned)digest[i]);
    hex[64]=0;
    if(strcmp(hex,expected)) {fprintf(stderr,"%s: %s != %s\n",label,hex,expected);return 1;}
    return 0;
}
int main(void) {
    hashguard_sha256_ctx ctx;unsigned char out[32];char hex[65];unsigned i;
    int fail=0;
    fail+=verify("empty","","e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");
    fail+=verify("abc","abc","ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad");
    fail+=verify("56-byte","abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq","248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1");
    hashguard_sha256_init(&ctx);
    hashguard_sha256_update(&ctx,"a",1);hashguard_sha256_update(&ctx,"bc",2);
    hashguard_sha256_final(&ctx,out);
    for(i=0;i<32;i++)sprintf(hex+2*i,"%02x",(unsigned)out[i]);hex[64]=0;
    if(strcmp(hex,"ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad"))fail++;
    if(fail)return 1;puts("SHA256 PASS");return 0;
}
