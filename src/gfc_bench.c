#include <assert.h>
#include <gfc/gfc.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

double benchmark_dec(uint64_t range, uint64_t rounds, uint64_t seed,
                     uint64_t count) {
  uint64_t dec;
  GFC *gfc = gfc_init(range, rounds, seed);

  clock_t start = clock();
  for (uint64_t i = 0; i < count; i++) {
    dec = gfc_decrypt(gfc, i);
  }
  clock_t end = clock();
  double seconds = (double)(end - start) / CLOCKS_PER_SEC;

  gfc_destroy(gfc);
  return seconds;
}

double benchmark_enc(uint64_t range, uint64_t rounds, uint64_t seed,
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
  printf("range,mode,time\n");
  for (uint64_t i = 20; i < 64; i++) {
    uint64_t range = (uint64_t)pow(2, i);
    for (uint64_t j = 0; j < 3; j++) {
      double dec_s = benchmark_dec(range, 6, j, 1048576);
      double enc_s = benchmark_enc(range, 6, j, 1048576);
      printf("%llu,dec,%f\n", range, dec_s);
      printf("%llu,enc,%f\n", range, enc_s);
    }
  }
  return 0;
}
