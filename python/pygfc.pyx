# distutils: sources = src/gfc.c
# distutils: include_dirs = include/
from libc.stdint cimport uint64_t


cdef extern from "gfc/gfc.h":
    cdef struct GFC:
        pass

    GFC* gfc_init(uint64_t range, uint64_t rounds, uint64_t seed)
    void gfc_destroy(GFC* gfc)
    uint64_t gfc_decrypt(const GFC* gfc, const uint64_t m)
    uint64_t gfc_encrypt(const GFC* gfc, const uint64_t m)


cdef class Permutation:
    cdef uint64_t range
    cdef uint64_t rounds
    cdef uint64_t seed
    cdef GFC* perm;

    def __init__(self, uint64_t range, uint64_t rounds, uint64_t seed):
        self.range = range
        self.rounds = rounds
        self.seed = seed
        self.perm = gfc_init(range, rounds, seed)

    def __dealloc__(self):
         gfc_destroy(self.perm)

    def __getstate__(self):
        return (self.range, self.rounds, self.seed)

    def __setstate__(self, state):
        self.__init__(*state)

    def __getitem__(self, uint64_t i):
        if i >= self.range:
            raise IndexError
        return gfc_encrypt(self.perm, i)

    def __iter__(self):
        for i in range(len(self)):
            yield self[i]

    def __len__(self):
        return self.range

    cpdef uint64_t inv(self, uint64_t i):
        if i >= self.range:
            raise IndexError
        return gfc_decrypt(self.perm, i)
