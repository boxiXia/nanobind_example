# reference: https://github.com/Krande/nanobind-minimal/blob/main/tests/test_basic.py
from build import my_ext
import numpy as np


def test_basic_add_args():
    assert my_ext.add(1, 2) == 3
    assert my_ext.add(a=1, b=2) == 3
    assert my_ext.add_no_literals(1,2) == 3
    np.testing.assert_array_equal(my_ext.eigen_add(np.array([1]), np.array([2])), np.array([3]))
    

def test_realease_gil():
    assert my_ext.test_release_gil()==0
    assert my_ext.test_no_release_gil()==1

def test_get_floats_from_range():
    res = my_ext.get_floats_in_range(start=0, end=10)
    assert isinstance(res, list)
    assert len(res) == 10
    assert res[0] == 0.0
    assert res[-1] == 9.0
    assert isinstance(res[0], float)


def test_numpy():
    res = my_ext.get_numpy_data()

    assert isinstance(res, np.ndarray)
    assert res.shape == (2, 4)


def test_eigen():
    np.testing.assert_array_equal(my_ext.vec1, np.array([1,2,3]))
    my_ext.vec1 += 1
    np.testing.assert_array_equal(my_ext.vec1, np.array([2,3,4]))
    

def test_get_mesh_class():
    res = my_ext.get_mesh()
    assert isinstance(res, my_ext.Mesh)
    assert hasattr(res, "positions")
    assert hasattr(res, "indices")


if __name__ == "__main__":
    test_basic_add_args()
    test_get_floats_from_range()
    test_numpy()
    test_eigen()
    test_get_mesh_class()
    test_realease_gil()