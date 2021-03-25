#pragma once

#include <stdint.h>

typedef struct GFC GFC;

struct GFC {
  uint64_t M;  // Range
  uint64_t r;  // Number of feistel rounds
  uint64_t a;
  uint64_t b;
  uint32_t* speck_exp;
};

GFC* gfc_init(uint64_t range, uint64_t rounds, uint64_t seed);
void gfc_destroy(GFC* gfc);
uint64_t gfc_decrypt(const GFC* gfc, uint64_t m);
uint64_t gfc_encrypt(const GFC* gfc, uint64_t m);
