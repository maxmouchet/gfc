import pickle

import pytest

from pygfc import Permutation


def test_gfc():
    for range_ in [0, 1, 10, 2 ** 16]:
        for rounds in [0, 1, 6]:
            for seed in [0, 1, 42]:
                perm = Permutation(range_, rounds, seed)
                assert len(perm) == range_
                assert set(perm) == set(range(range_))
                for i in range(range_):
                    assert perm.inv(perm[i]) == i

    perm = Permutation(2 ** 16, 3, 42)
    assert all(perm[i] != i for i in range(range_))
    with pytest.raises(IndexError):
        perm[2 ** 16]


def test_pickle():
    perm1 = Permutation(2 ** 64 - 1, 6, 2021)
    perm2 = pickle.loads(pickle.dumps(perm1))
    for i in range(2048):
        assert perm1[i] == perm2[i]
