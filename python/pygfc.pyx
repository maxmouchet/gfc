# distutils: sources = src/gfc.c
# distutils: include_dirs = include/
from libc.stdint cimport uint64_t


cdef extern from "gfc/gfc.h":
    cdef struct GFC:
        pass

    GFC* gfc_init(uint64_t range, uint64_t rounds, uint64_t seed)
    void gfc_destroy(GFC* gfc)
    uint64_t gfc_encrypt(GFC* gfc, uint64_t m)


cdef class Permutation:
    cdef uint64_t range
    cdef uint64_t rounds
    cdef uint64_t seed

    def __init__(self, uint64_t range, uint64_t rounds, uint64_t seed):
        self.range = range
        self.rounds = rounds
        self.seed = seed

    def __iter__(self):
        return PermutationIterator(self.range, self.rounds, self.seed)

    def __len__(self):
        return self.range


cdef class PermutationIterator:
    cdef uint64_t counter
    cdef uint64_t range
    cdef GFC* perm;

    def __cinit__(self, uint64_t range, uint64_t rounds, uint64_t seed):
        self.counter = 0
        self.range = range
        self.perm = gfc_init(range, rounds, seed)

    def __dealloc__(self):
        gfc_destroy(self.perm)

    def __iter__(self):
        return self

    def __len__(self):
        return self.range

    def __next__(self):
        if self.counter >= self.range:
            raise StopIteration
        enc = gfc_encrypt(self.perm, self.counter)
        self.counter += 1
        return enc
