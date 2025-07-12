message("[External]")
set(CDIR ${CMAKE_CURRENT_LIST_DIR})

set(EXTERNAL_DIRS
  ${CDIR}
  ${CDIR}/pybind11/include/
  ${CDIR}/eigen
)
include_directories(PUBLIC ${EXTERNAL_DIRS})

add_library(im_all
  STATIC
  # imgui
  ${CDIR}/imgui/imgui.cpp
  ${CDIR}/imgui/imgui_demo.cpp
  ${CDIR}/imgui/imgui_draw.cpp
  ${CDIR}/imgui/imgui_tables.cpp
  ${CDIR}/imgui/imgui_widgets.cpp
  ${CDIR}/imgui/backends/imgui_impl_glfw.cpp
  ${CDIR}/imgui/backends/imgui_impl_opengl2.cpp
  ${CDIR}/imgui/misc/cpp/imgui_stdlib.cpp
  # implot
  ${CDIR}/implot/implot.cpp
  ${CDIR}/implot/implot_demo.cpp
  ${CDIR}/implot/implot_items.cpp
  # implot3d
  ${CDIR}/implot3d/implot3d.cpp
  ${CDIR}/implot3d/implot3d_demo.cpp
  ${CDIR}/implot3d/implot3d_items.cpp
  ${CDIR}/implot3d/implot3d_meshes.cpp
)
target_include_directories(
  im_all
  PUBLIC
  ${CDIR}/imgui
  ${CDIR}/implot
  ${CDIR}/implot3d
)
target_link_libraries(
  im_all
  PUBLIC
  glfw
  ${GLEW_LIBRARIES}
  GLEW::GLEW
  OpenGL::GL
)
target_compile_options(im_all PRIVATE -w)

set(PYBIND11_FINDPYTHON ON)
add_subdirectory(${CDIR}/pybind11)

add_subdirectory(${CDIR}/eigen)

set(EXTERNAL_DIRS ${EXTERNAL_DIRS} PARENT_SCOPE)
