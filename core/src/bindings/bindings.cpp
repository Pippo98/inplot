#include "figure/figure.hpp"
#include "pybind11/pybind11.h"
#include "pybind11/detail/common.h"
#include "pybind11/iostream.h"
#include "pybind11/pytypes.h"
#include "pybind11/eigen.h"
#include "pybind11/stl.h"

namespace py = pybind11;

PYBIND11_MODULE(pyinplot, m) {
  py::class_<Figure>(m, "Figure")
      .def(py::init<std::string>());
}
