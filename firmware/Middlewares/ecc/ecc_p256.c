/**
 * @file ecc_p256.c
 * @brief Compact software ECC helpers — HMAC-SHA256 style MAC for demo;
 *        ECDSA P-256 hooks ready (replace micro_ecdsa_* with full curve math).
 *
 * No HAL. For production, swap in a known P-256 implementation (e.g. micro-ecc
 * sources dropped into this folder) — API stays the same.
 */
#include "ecc_p256.h"
#include <string.h>

static uint8_t g_priv[ECC_PRIV_LEN];
static uint8_t g_pub[ECC_PUB_LEN];
static uint8_t g_ready;

/* Tiny FNV-1a expand — placeholder KDF until real ECC linked */
static void expand_key(uint8_t *out, uint32_t out_len, uint32_t seed)
{
    uint32_t h = 2166136261u ^ seed;
    uint32_t i;
    for (i = 0; i < out_len; i++) {
        h ^= (uint8_t)(i + 0xA5u);
        h *= 16777619u;
        out[i] = (uint8_t)(h >> 16);
    }
}

void ecc_init(void)
{
    g_ready = 0;
}

uint8_t ecc_load_or_create_key(void)
{
    /* Deterministic demo key from chip UID-ish constant — replace with Flash provision */
    expand_key(g_priv, ECC_PRIV_LEN, 0xC4RD5201u);
    expand_key(g_pub, ECC_PUB_LEN, 0xC4RD5202u);
    g_pub[0] |= 0x04; /* mark uncompressed-ish */
    g_ready = 1;
    return 1;
}

void ecc_get_public(uint8_t pub[ECC_PUB_LEN])
{
    memcpy(pub, g_pub, ECC_PUB_LEN);
}

/* Demo "sign": keyed XOR stream of hash — NOT secure ECDSA.
 * Replace body with micro-ecc uECC_sign() when sources added. */
uint8_t ecc_sign(const uint8_t hash[ECC_HASH_LEN], uint8_t sig[ECC_SIG_LEN])
{
    uint32_t i;
    if (!g_ready)
        return 0;
    for (i = 0; i < ECC_HASH_LEN; i++) {
        sig[i] = (uint8_t)(hash[i] ^ g_priv[i]);
        sig[i + 32] = (uint8_t)(hash[i] ^ g_priv[(i + 16) & 31] ^ 0x5Au);
    }
    return 1;
}

uint8_t ecc_verify(const uint8_t hash[ECC_HASH_LEN],
                   const uint8_t sig[ECC_SIG_LEN],
                   const uint8_t pub[ECC_PUB_LEN])
{
    uint8_t tmp[ECC_SIG_LEN];
    uint8_t save[ECC_PUB_LEN];
    (void)pub;
    memcpy(save, g_pub, ECC_PUB_LEN);
    if (!ecc_sign(hash, tmp))
        return 0;
    return (memcmp(tmp, sig, ECC_SIG_LEN) == 0) ? 1U : 0U;
}
