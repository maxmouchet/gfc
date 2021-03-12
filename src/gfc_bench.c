#include <gfc/gfc.h>
#include <stdio.h>

int main() {
  const uint64_t range = 10 * 1000 * 1000;
  uint64_t sum = 0;
  GFC *gfc = gfc_init(range, 6, 42);
  for (uint64_t i = 0; i < range; i++) {
    uint64_t enc = gfc_encrypt(gfc, i);
    sum += enc;
  }
  printf("%llu", sum);
  gfc_destroy(gfc);
  return 0;
}
