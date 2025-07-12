message("[CORE]")
set(CDIR ${CMAKE_CURRENT_LIST_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PDIR}/bin/core/)
include_directories(${CDIR}/src)

add_library(
  core
  STATIC
  ${CDIR}/src/window/window.cpp
  ${CDIR}/src/figure/figure.cpp
)
target_link_libraries(
  core
  PUBLIC
  im_all
)

add_executable(main ${CDIR}/executables/main.cpp)
target_link_libraries(
  main
  PRIVATE
  core
)

pybind11_add_module(pyinplot ${CDIR}/src/bindings/bindings.cpp)
target_link_libraries(pyinplot PUBLIC im_all core pybind11::pybind11 pybind11::module pybind11::lto pybind11::windows_extras)
