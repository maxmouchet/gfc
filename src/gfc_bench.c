#include <assert.h>
#include <gfc/gfc.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

double benchmark(uint64_t range, uint64_t rounds, uint64_t seed,
                 uint64_t count) {
  uint64_t enc;
  GFC *gfc = gfc_init(range, rounds, seed);

  clock_t start = clock();
  for (uint64_t i = 0; i < count; i++) {
    enc = gfc_encrypt(gfc, i);
  }
  clock_t end = clock();
  double seconds = (double)(end - start) / CLOCKS_PER_SEC;

  gfc_destroy(gfc);
  return seconds;
}

int main() {
  printf("range,time\n");
  for (uint64_t i = 20; i < 64; i++) {
    uint64_t range = (uint64_t)pow(2, i);
    for (uint64_t j = 0; j < 3; j++) {
      double secs = benchmark(range, 6, j, 1048576);
      printf("%llu,%f\n", range, secs);
    }
  }
  return 0;
}
