#include "core/src/window/window.hpp"
#include <cstdlib>
#include <iostream>

int main() {

  OpenWindow("inplot");

  while(!ShouldClose()) {
    NewFrame();
    Dockspace();
    RenderFrame();
  }

  return EXIT_SUCCESS;
}
