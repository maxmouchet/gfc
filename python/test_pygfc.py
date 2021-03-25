import pytest

from pygfc import Permutation


def test_gfc():
    for range_ in [0, 1, 10, 2 ** 16]:
        for rounds in [0, 1, 6]:
            for seed in [0, 1, 42]:
                perm = Permutation(range_, rounds, 42)
                assert len(perm) == range_
                assert set(perm) == set(range(range_))
                for i in range(range_):
                    assert perm.inv(perm[i]) == i

    perm = Permutation(2 ** 16, 3, 42)
    assert all(perm[i] != i for i in range(range_))
    with pytest.raises(IndexError):
        perm[2 ** 16]
