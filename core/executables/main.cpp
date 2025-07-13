#include "core/src/window/window.hpp"
#include "figure/figure.hpp"
#include <cstdlib>
#include <iostream>

int main() {
  Start();
  auto f = figure("fig 1");
  f->AddPlot("aaa");
  WaitForEnd();
  return EXIT_SUCCESS;
}
