# distutils: sources = src/gfc.c
# distutils: include_dirs = include/
from libc.stdint cimport uint64_t


cdef extern from "gfc/gfc.h":
    cdef struct GFC:
        pass

    GFC* gfc_init(uint64_t range, uint64_t rounds, uint64_t seed)
    void gfc_destroy(GFC* gfc)
    uint64_t gfc_encrypt(GFC* gfc, uint64_t m)


class Permutation:
    def __init__(self, range, rounds, seed):
        self.range = range
        self.rounds = rounds
        self.seed = seed

    def __iter__(self):
        return PermutationIterator(self.range, self.rounds, self.seed)

    def __len__(self):
        return self.range


cdef class PermutationIterator:
    cdef uint64_t _counter
    cdef uint64_t _range
    cdef GFC* _perm;

    def __cinit__(self, range, rounds, seed):
        self._counter = 0
        self._range = range
        self._perm = gfc_init(range, rounds, seed)

    def __dealloc__(self):
        gfc_destroy(self._perm)

    def __iter__(self):
        return self

    def __next__(self):
        if self._counter >= self._range:
            raise StopIteration
        enc = gfc_encrypt(self._perm, self._counter)
        self._counter += 1
        return enc
