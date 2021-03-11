from pygfc import Permutation


def test_gfc():
    perm = Permutation(2 ** 16, 8, 42)
    assert set(perm) == set(range(2 ** 16))
    assert len(perm) == 2 ** 16
