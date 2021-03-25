#include <assert.h>
#include <gfc/gfc.h>
#include <stdio.h>
#include <stdlib.h>

int test_range(uint64_t range, uint64_t rounds) {
  uint64_t* counts = calloc(range, sizeof(uint64_t));
  GFC* gfc = gfc_init(range, rounds, 42);
  for (uint64_t i = 0; i < range; i++) {
    uint64_t enc = gfc_encrypt(gfc, i);
    uint64_t dec = gfc_decrypt(gfc, enc);
    if (dec != i) {
      printf("dec[%llu] = %llu\n", i, dec);
    }
    counts[enc]++;
  }
  for (uint64_t i = 0; i < range; i++) {
    if (counts[i] != 1) {
      printf("counts[%llu] = %llu\n", i, counts[i]);
      return 0;
    }
  }
  gfc_destroy(gfc);
  free(counts);
  return 1;
}

int main() {
  assert(test_range(0, 0));
  assert(test_range(0, 1));
  assert(test_range(1, 0));
  assert(test_range(1, 1));
  assert(test_range(10, 1));
  assert(test_range(100, 1));
  assert(test_range(100, 6));
  assert(test_range(500 * 1000, 6));
}
