#ifndef ECC_P256_H
#define ECC_P256_H

#include <stdint.h>

/* Software ECDSA P-256 (secp256r1) — compact implementation, no HAL */

#define ECC_PRIV_LEN  32
#define ECC_PUB_LEN   64
#define ECC_SIG_LEN   64
#define ECC_HASH_LEN  32

void ecc_init(void);
/* Load or generate device key (stored in last Flash page abstraction) */
uint8_t ecc_load_or_create_key(void);
/* Sign 32-byte hash → 64-byte (r||s) */
uint8_t ecc_sign(const uint8_t hash[ECC_HASH_LEN], uint8_t sig[ECC_SIG_LEN]);
uint8_t ecc_verify(const uint8_t hash[ECC_HASH_LEN],
                   const uint8_t sig[ECC_SIG_LEN],
                   const uint8_t pub[ECC_PUB_LEN]);
void ecc_get_public(uint8_t pub[ECC_PUB_LEN]);

#endif
