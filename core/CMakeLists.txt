message("[CORE]")
set(CDIR ${CMAKE_CURRENT_LIST_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PDIR}/bin/core/)

add_library(
  core
  STATIC
  ${CDIR}/src/window/window.cpp
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
