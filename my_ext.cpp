#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/stl/vector.h>
#include <nanobind/eigen/dense.h> // for EIGEN integration
#include <vector>

namespace nb = nanobind;
using namespace nb::literals;

int add(int a, int b = 1) { return a + b; }


std::vector<float> get_floats_in_range(int start, int end) {
    std::vector<float> floats;
    for (int i = start; i < end; i++)
        floats.push_back(float(i));

    return floats;
}

float data[] = {1, 2, 3, 4, 5, 6, 7, 8};

Eigen::Matrix3d mat33{ {1, 2, 3}, 
                        {4, 5, 6}, 
                        {7, 8, 9} };

// Classes
class Mesh {
public:
    Mesh(std::vector<float> positions,
         std::vector<uint32_t> indices){
    this->positions = std::move(positions);
    this->indices = std::move(indices);

}


    std::vector<float> positions;
    std::vector<uint32_t> indices;

};

Eigen::Matrix<double,1,3 > vec1{1,2,3};


Mesh get_mesh() {
    std::vector<float> positions = {1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<uint32_t> indices = {1, 2, 3, 4, 5, 6, 7, 8};
    return {positions, indices};
}

Eigen::Matrix<double,1,1 > eigen_add(Eigen::Matrix<double,1,1> a=Eigen::Matrix<double,1,1>::Zero(), Eigen::Matrix<double,1,1> b=Eigen::Matrix<double,1,1>::Zero()){
    return a + b;
}

NB_MODULE(my_ext, m) {
    m.def("add", &add, "a"_a, "b"_a = 1,
          "This function adds two numbers and increments if only one is provided."); // this need: using namespace nb::literals;

    m.def("add_no_literals", &add, nb::arg("a"), nb::arg("b"),
    "This function adds two numbers and does not use the namespace nb::literals");

    m.def("eigen_add", &eigen_add, "a"_a=Eigen::Matrix<double,1,1>::Zero(), "b"_a=Eigen::Matrix<double,1,1>::Zero());


    m.def("get_floats_in_range", &get_floats_in_range, "start"_a, "end"_a,
          "This function returns a vector of floats based on a start and end value.");

    m.def("get_numpy_data", []() {
        size_t shape[2] = {2, 4};
        return nb::ndarray<nb::numpy, float, nb::shape<2, 4>>(
                data, /* ndim = */ 2, shape);
    });

    m.def("get_mesh", &get_mesh, "This function returns a Mesh class.");
    nb::class_<Mesh>(std::move(m), "Mesh")
            .def_rw("positions", &Mesh::positions)
            .def_rw("indices", &Mesh::indices);

    m.attr("vec1") = vec1; 

    m.def("test_release_gil", []() -> bool {
        return PyGILState_Check();
    }, nb::call_guard<nb::gil_scoped_release>());

    m.def("test_no_release_gil", []() -> bool {
        return PyGILState_Check();
    });
}