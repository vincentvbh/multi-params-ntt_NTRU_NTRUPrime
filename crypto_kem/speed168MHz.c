#include "api.h"
#include "hal.h"
#include "randombytes.h"
#include "sendfn.h"

#include "NTT_params.h"
#include "NTT.h"
#include <stdint.h>
#include <string.h>

#define printcycles(S, U) send_unsignedll((S), (U))

int main(void){

    unsigned char key_a[CRYPTO_BYTES], key_b[CRYPTO_BYTES];
    unsigned char sk[CRYPTO_SECRETKEYBYTES];
    unsigned char pk[CRYPTO_PUBLICKEYBYTES];
    unsigned char ct[CRYPTO_CIPHERTEXTBYTES];


    unsigned long long t0, t1;
    int i;
    int crypto_i;

    hal_setup(CLOCK_FAST);

    for(i = 0; i < 60; i++){
        hal_send_str("==========================");
    }

    for(crypto_i = 0; crypto_i < ITERATIONS; crypto_i++){

        // PolyMul
      {
        int16_t a[POLY_N];
        int32_t poly1_NTT[ARRAY_N];

        t0 = hal_get_time();
        NTT_forward(poly1_NTT, (int16_t*)a);
        t1 = hal_get_time();
        printcycles("NTT cycles:", t1 - t0);

        t0 = hal_get_time();
        NTT_forward_small(poly1_NTT, (int16_t*)a);
        t1 = hal_get_time();
        printcycles("NTT_small cycles:", t1 - t0);

        t0 = hal_get_time();
        NTT_mul(poly1_NTT, poly1_NTT, poly1_NTT);
        t1 = hal_get_time();
        printcycles("basemul cycles:", t1 - t0);
#if (NTRU_N > 800) 
        t0 = hal_get_time();
        NTT_inverse(poly1_NTT,poly1_NTT);
        t1 = hal_get_time();
        printcycles("iNTT cycles:", t1 - t0);
#else
        t0 = hal_get_time();
        NTT_inverse(poly1_NTT);
        t1 = hal_get_time();
        printcycles("iNTT cycles:", t1 - t0);
#endif       
        t0 = hal_get_time();
        Final_map(a,poly1_NTT);
        t1 = hal_get_time();
        printcycles("final_map cycles:", t1 - t0);

      }
        // Key-pair generation
        t0 = hal_get_time();
        crypto_kem_keypair(pk, sk);
        t1 = hal_get_time();
        printcycles("keypair cycles:", t1 - t0);

        // Encapsulation
        t0 = hal_get_time();
        crypto_kem_enc(ct, key_a, pk);
        t1 = hal_get_time();
        printcycles("encaps cycles:", t1 - t0);

        // Decapsulation
        t0 = hal_get_time();
        crypto_kem_dec(key_b, ct, sk);
        t1 = hal_get_time();
        printcycles("decaps cycles:", t1 - t0);

        if(memcmp(key_a, key_b, CRYPTO_BYTES)) {
            hal_send_str("ERROR KEYS\n");
        }
        else{
            hal_send_str("OK KEYS\n");
        }

        hal_send_str("#");
    }

    while(1);

    return 0;
}
