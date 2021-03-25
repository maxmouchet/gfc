# gfc

[![build](https://github.com/maxmouchet/gfc/actions/workflows/build.yml/badge.svg)](https://github.com/maxmouchet/gfc/actions/workflows/build.yml)
[![PyPI](https://img.shields.io/pypi/v/pygfc)](https://pypi.org/project/pygfc/)

Implementation of a Generalized-Feistel Cipher [1, alg. 3] for generating random permutations.  
It uses [Speck](https://en.wikipedia.org/wiki/Speck_%28cipher%29) 64/128 as the random function, and can generate permutations up to `2^64`.  

### C API

```c
#include <gfc/gfc.h>
GFC* gfc_init(uint64_t range, uint64_t rounds, uint64_t seed);
void gfc_destroy(GFC* gfc);
uint64_t gfc_decrypt(const GFC* gfc, uint64_t m);
uint64_t gfc_encrypt(const GFC* gfc, uint64_t m);
```

### Python API

```python
from pygfc import Permutation
# Permutation(range, rounds, seed)
perm = Permutation(2 ** 16, 8, 42)
assert set(perm) == set(range(2 ** 16))
assert all(perm.inv(perm[i]) == i for i in range(2 ** 16))
```

### Dependencies

The Speck implementation is from [madmo/speck](https://github.com/madmo/speck) and is licensed under the ISC license (MIT-compatible).  

### References

[1] Black, John, and Phillip Rogaway. "Ciphers with arbitrary finite domains." _Cryptographers’ track at the RSA conference_. Springer, Berlin, Heidelberg, 2002.
https://web.cs.ucdavis.edu/~rogaway/papers/subset.pdf
