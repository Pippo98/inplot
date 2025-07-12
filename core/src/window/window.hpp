#pragma once

#include <string>

class GLFWwindow;
class GLFWmonitor;
struct window_t {
  GLFWmonitor *monitor;
  GLFWwindow *window;
};

extern window_t window;

bool OpenWindow(const std::string &name);
bool ShouldClose();

void NewFrame();
void RenderFrame();
void Dockspace();

// call this after a change in imgui style
void UpdateStyle();
