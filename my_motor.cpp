#include <nanobind/nanobind.h>
// #include <nanobind/ndarray.h>
// #include <nanobind/stl/vector.h>
#include <nanobind/eigen/dense.h> // for EIGEN integration
#include <vector>
#include <string>
#include <nanobind/stl/string.h>

namespace nb = nanobind;
using namespace nb::literals;


Eigen::Matrix<double,1,3 > vec1{1,2,3};

class Motor {
public:

    std::string can_interface;

    int num_motors;
    Eigen::Matrix<uint8_t,Eigen::Dynamic,1> can_ids;
    Eigen::Matrix<uint8_t,Eigen::Dynamic,1> motor_types;

    Motor(
        
        std::string can_interface, 
        Eigen::Matrix<uint8_t,Eigen::Dynamic,1> can_ids,
        Eigen::Matrix<uint8_t,Eigen::Dynamic,1> motor_types
        
        ){
        this->can_interface = can_interface;
        this->num_motors = can_ids.size();
        this->can_ids = can_ids;
        this->motor_types = motor_types;
    }

};

NB_MODULE(motor, m) {

    m.attr("vec1") = vec1;

    nb::class_<Motor> motor(m, "Motor");

    motor.def(nb::init<std::string,Eigen::Matrix<uint8_t,Eigen::Dynamic,1>,Eigen::Matrix<uint8_t,Eigen::Dynamic,1>>());
    motor.def_ro("can_interface", &Motor::can_interface);
    motor.def_ro("num_motors", &Motor::num_motors);
    motor.def_ro("can_ids", &Motor::can_ids);
    motor.def_ro("motor_types", &Motor::motor_types);


}