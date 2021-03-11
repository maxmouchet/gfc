# gfc


(Partial) implementation of a generalized-feistel cipher [1, alg. 3] for generating random permutations.

```c
GFC* gfc_init(uint64_t range, uint64_t rounds, uint64_t seed);
void gfc_destroy(GFC* gfc);
uint64_t gfc_encrypt(GFC* gfc, uint64_t m);
```

[1] Black, John, and Phillip Rogaway. "Ciphers with arbitrary finite domains." _Cryptographers’ track at the RSA conference_. Springer, Berlin, Heidelberg, 2002.
https://web.cs.ucdavis.edu/~rogaway/papers/subset.pdf
