from pygfc import Permutation


def test_gfc():
    for range_ in [0, 1, 10, 2 ** 16]:
        for rounds in [0, 1, 6]:
            for seed in [0, 1, 42]:
                perm = Permutation(range_, rounds, 42)
                assert set(perm) == set(range(range_))
                assert len(perm) == range_
