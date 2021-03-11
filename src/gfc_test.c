#include <gfc/gfc.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  uint64_t range = 500 * 1000;
  uint64_t* counts = calloc(range, sizeof(uint64_t));
  GFC* gfc = gfc_init(range, 8, 42);
  for (uint64_t i = 0; i < range; i++) {
    uint64_t enc = gfc_encrypt(gfc, i);
    counts[enc]++;
  }
  for (uint64_t i = 0; i < range; i++) {
    if (counts[i] != 1) {
      printf("counts[%llu] = %llu\n", i, counts[i]);
      return 1;
    }
  }
  gfc_destroy(gfc);
  free(counts);
  return 0;
}
