#include <gfc/gfc.h>
#include <math.h>
#include <stdlib.h>

// The speck code is a cut down version of https://github.com/madmo/speck,
// licensed under the ISC license.
#define SPECK_TYPE uint32_t
#define SPECK_ROUNDS 27
#define SPECK_KEY_LEN 4

#define ROR(x, r) ((x >> r) | (x << ((sizeof(SPECK_TYPE) * 8) - r)))
#define ROL(x, r) ((x << r) | (x >> ((sizeof(SPECK_TYPE) * 8) - r)))
#define R(x, y, k) (x = ROR(x, 8), x += y, x ^= k, y = ROL(y, 3), y ^= x)

void speck_expand(SPECK_TYPE const K[static SPECK_KEY_LEN],
                  SPECK_TYPE S[static SPECK_ROUNDS]) {
  SPECK_TYPE i, b = K[0];
  SPECK_TYPE a[SPECK_KEY_LEN - 1];

  for (i = 0; i < (SPECK_KEY_LEN - 1); i++) {
    a[i] = K[i + 1];
  }
  S[0] = b;
  for (i = 0; i < SPECK_ROUNDS - 1; i++) {
    R(a[i % (SPECK_KEY_LEN - 1)], b, i);
    S[i + 1] = b;
  }
}

void speck_encrypt(SPECK_TYPE const pt[static 2], SPECK_TYPE ct[static 2],
                   SPECK_TYPE const K[static SPECK_ROUNDS]) {
  SPECK_TYPE i;
  ct[0] = pt[0];
  ct[1] = pt[1];

  for (i = 0; i < SPECK_ROUNDS; i++) {
    R(ct[1], ct[0], K[i]);
  }
}

// Function Fe and fe are from the Figure 3 of
// https://www.cs.ucdavis.edu/~rogaway/papers/subset.pdf
// For the random function F we use speck
// with a block size of 64 bits and a key size of 128 bits.

// This is the random function F_j(R) in the paper.
uint64_t F(const GFC *gfc, const uint64_t j, const uint64_t R) {
  uint64_t enc;
  const uint32_t *key = gfc->speck_exp + (j - 1) * SPECK_ROUNDS;
  speck_encrypt((const uint32_t *)&R, (uint32_t *)&enc, key);
  return enc;
}

// This is the function fe[r,a,b]_K(m) in the paper.
uint64_t fe(const GFC *gfc, const uint64_t m) {
  uint64_t L, R, tmp;

  L = m % gfc->a;
  R = m / gfc->a;

  for (uint64_t j = 1; j <= gfc->r; j++) {
    // j & 1 is true if j is odd
    if (j & 1) {
      tmp = (L + F(gfc, j, R)) % gfc->a;
    } else {
      tmp = (L + F(gfc, j, R)) % gfc->b;
    }
    L = R;
    R = tmp;
  }

  if (gfc->r & 1) {
    return gfc->a * L + R;
  } else {
    return gfc->a * R + L;
  }
}

// This is the function fe^-1[r,a,b]_K(m) in the paper.
uint64_t fe_inv(const GFC *gfc, const uint64_t m) {
  uint64_t L, R, tmp;

  if (gfc->r & 1) {
    R = m % gfc->a;
    L = m / gfc->a;
  } else {
    L = m % gfc->a;
    R = m / gfc->a;
  }

  for (uint64_t j = gfc->r; j >= 1; j--) {
    if (j & 1) {
      // We apply the same trick as the following impl. to prevent underflows:
      // https://github.com/urbit/urbit-ob/blob/master/src/internal/ob.js#L152-L157
      tmp = (R + gfc->a - (F(gfc, j, L) % gfc->a)) % gfc->a;
      // tmp = (R - tmp) % gfc->a;
    } else {
      tmp = (R + gfc->b - (F(gfc, j, L) % gfc->b)) % gfc->b;
      // tmp = (R - tmp) % gfc->b;
    }
    R = L;
    L = tmp;
  }

  return gfc->a * R + L;
}

GFC *gfc_init(uint64_t range, uint64_t rounds, uint64_t seed) {
  GFC *gfc = calloc(1, sizeof(GFC));
  if (gfc == NULL) {
    return NULL;
  }
  gfc->M = range;
  gfc->r = rounds;
  // Compute the constants a and b such that ab >= range,
  // according to the method of Section 6.
  const double tmp = ceil(sqrt((double)range));
  gfc->a = (uint64_t)tmp;
  gfc->b = (uint64_t)tmp;
  // Precompute the speck round keys
  gfc->speck_exp = calloc(gfc->r * SPECK_ROUNDS, sizeof(uint32_t));
  for (uint64_t i = 0; i < gfc->r; i++) {
    const uint64_t key[2] = {seed, i};
    speck_expand((const uint32_t *)key, gfc->speck_exp + i * SPECK_ROUNDS);
  }
  return gfc;
}

void gfc_destroy(GFC *gfc) {
  free(gfc->speck_exp);
  free(gfc);
}

// This is the function Fe^-1[r,a,b]_K(m) in the paper.
uint64_t gfc_decrypt(const GFC *gfc, const uint64_t m) {
  uint64_t c = fe_inv(gfc, m);
  while (c >= gfc->M) {
    c = fe_inv(gfc, c);
  }
  return c;
}

// This is the function Fe[r,a,b]_K(m) in the paper.
uint64_t gfc_encrypt(const GFC *gfc, const uint64_t m) {
  uint64_t c = fe(gfc, m);
  while (c >= gfc->M) {
    c = fe(gfc, c);
  }
  return c;
}
