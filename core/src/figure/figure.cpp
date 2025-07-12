#include "figure.hpp"
#include "core/src/window/window.hpp"
#include <memory>

Figure::Figure(const std::string &_name) : name(_name), stopThread(false) {
  t = new std::thread(&Figure::Run, this);
}

void Figure::Run() {
  OpenWindow(name);
  while (!stopThread && !ShouldClose()) {
    NewFrame();
    Dockspace();

    RenderFrame();
  }
}
