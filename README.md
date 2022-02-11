# 🎲 gfc — fast & lazy random permutations

[![PyPI Status](https://img.shields.io/github/workflow/status/maxmouchet/gfc/PyPI?logo=github&label=pypi)](https://github.com/maxmouchet/gfc/actions/workflows/pypi.yml)
[![Tests Status](https://img.shields.io/github/workflow/status/maxmouchet/gfc/Tests?logo=github&label=tests)](https://github.com/maxmouchet/gfc/actions/workflows/tests.yml)
[![PyPI](https://img.shields.io/pypi/v/pygfc?color=blue&logo=pypi&logoColor=white)](https://pypi.org/project/pygfc/)

gfc is a C implementation of a Generalized-Feistel Cipher [[1, alg. 3]](#1) for generating random permutations.  
It uses [Speck](https://en.wikipedia.org/wiki/Speck_%28cipher%29) 64/128 as the random function, and can generate permutations with up to `2^64` elements.  
The permutation is computed, and reversed, _on-the-fly_, without any mutable state and by using very little memory.

## Usage

### C / C++

#### API

```c
#include <gfc/gfc.h>
GFC* gfc_init(uint64_t range, uint64_t rounds, uint64_t seed);
void gfc_destroy(GFC* gfc);
uint64_t gfc_decrypt(const GFC* gfc, uint64_t m);
uint64_t gfc_encrypt(const GFC* gfc, uint64_t m);
```

#### Example

```c
// main.c
// gcc -Iinclude/ src/gfc.c main.c -o main
#include <assert.h>
#include <gfc/gfc.h>

int main() {
  GFC* gfc = gfc_init(65536, 6, 42);
  
  for (uint64_t i = 0; i < 65536; i++) {
    uint64_t enc = gfc_encrypt(gfc, i);
    uint64_t dec = gfc_decrypt(gfc, enc);
    assert(enc != i);
    assert(dec == i);
  }

  gfc_destroy(gfc);
  return 0;
}
```

#### CMake Integration

```cmake
cmake_minimum_required(VERSION 3.12)
project(example)
add_subdirectory(gfc)
add_executable(main main.c)
target_link_libraries(main PRIVATE gfc)
```

```bash
git submodule add https://github.com/maxmouchet/gfc.git
mkdir build && cd build
cmake .. && cmake --build .
./main
```

### Python

```
pip install pygfc
```

```python
from pygfc import Permutation
# Permutation(range, rounds, seed)
perm = Permutation(2 ** 16, 8, 42)
assert set(perm) == set(range(2 ** 16))
assert all(perm.inv(perm[i]) == i for i in range(2 ** 16))
```

## Dependencies

The Speck implementation is from [madmo/speck](https://github.com/madmo/speck) and is licensed under the ISC license (MIT-compatible).  

## References

<a id="1">[1]</a> Black, John, and Phillip Rogaway. "Ciphers with arbitrary finite domains." _Cryptographers’ track at the RSA conference_. Springer, Berlin, Heidelberg, 2002.
https://web.cs.ucdavis.edu/~rogaway/papers/subset.pdf
