#include "figure/figure.hpp"
#include "pybind11/pybind11.h"
#include "pybind11/detail/common.h"
#include "pybind11/iostream.h"
#include "pybind11/pytypes.h"
#include "pybind11/eigen.h"
#include "pybind11/stl.h"

namespace py = pybind11;

PYBIND11_MODULE(pyinplot, m) {
  m.def("Start", &Start);
  m.def("Stop", &Stop);
  m.def("WaitForEnd", &WaitForEnd);
  m.def("figure", &figure);
  py::class_<Figure>(m, "Figure")
    .def("AddPlot", &Figure::AddPlot)
    .def("AddLinePlot", &Figure::AddLinePlot)
    .def("SetLinePlot", &Figure::SetLinePlot)
    .def("AddScatterPlot", &Figure::AddScatterPlot)
    .def("SetScatterPlot", &Figure::SetScatterPlot)
    .def("AddPlot3", &Figure::AddPlot3)
    .def("AddLinePlot3", &Figure::AddLinePlot3)
    .def("SetLinePlot3", &Figure::SetLinePlot3)
    .def("AddScatterPlot3", &Figure::AddScatterPlot3)
    .def("SetScatterPlot3", &Figure::SetScatterPlot3)
    .def(py::init<std::string>());
}
