#include <gfc/gfc.h>
#include <stdio.h>
#include <stdlib.h>

void test_range(uint64_t range, uint64_t rounds) {
  uint64_t *counts = calloc(range, sizeof(uint64_t));
  if (counts == NULL) {
    exit(1);
  }
  GFC *gfc = gfc_init(range, rounds, 42);
  for (uint64_t i = 0; i < range; i++) {
    uint64_t enc = gfc_encrypt(gfc, i);
    uint64_t dec = gfc_decrypt(gfc, enc);
    if (dec != i) {
      printf("dec[%llu] = %llu\n", i, dec);
      exit(1);
    }
    counts[enc]++;
  }
  for (uint64_t i = 0; i < range; i++) {
    if (counts[i] != 1) {
      printf("counts[%llu] = %llu\n", i, counts[i]);
      exit(1);
    }
  }
  gfc_destroy(gfc);
  free(counts);
}

int main() {
  test_range(0, 0);
  test_range(0, 1);
  test_range(1, 0);
  test_range(1, 1);
  test_range(10, 1);
  test_range(100, 1);
  test_range(100, 6);
  test_range(500 * 1000, 6);
  return 0;
}
