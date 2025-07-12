#include "window.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl2.h"
#include "implot.h"
#include "implot3d.h"
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif
#include <GLFW/glfw3.h>

window_t window;

bool OpenWindow(const std::string &name) {
  if (!glfwInit())
    return false;
  window.monitor = glfwGetPrimaryMonitor();

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
#ifndef __APPLE__
  glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
#endif

  int x, y, w, h;
  glfwGetMonitorWorkarea(window.monitor, &x, &y, &w, &h);

  glfwWindowHint(GLFW_MAXIMIZED, GL_TRUE);

  // Create window with graphics context
  float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(window.monitor);
  window.window = glfwCreateWindow((int)(w * main_scale), (int)(h * main_scale),
                                   name.c_str(), nullptr, nullptr);
  if (window.window == nullptr)
    return false;
  glfwMakeContextCurrent(window.window);
  glfwSwapInterval(1); // Enable vsync

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard;           // Enable Keyboard Controls
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking

  ImPlot::CreateContext();
  ImPlot3D::CreateContext();

  ImGui::StyleColorsDark();
  UpdateStyle();

  ImGui_ImplGlfw_InitForOpenGL(window.window, true);
  ImGui_ImplOpenGL2_Init();

  glEnable(GL_MULTISAMPLE);
  glfwShowWindow(window.window);

  return true;
}

bool ShouldClose() { return glfwWindowShouldClose(window.window) != 0; }

void NewFrame() {
  glfwPollEvents();
  ImGui_ImplOpenGL2_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

void RenderFrame() {
  static int display_w;
  static int display_h;

  ImGui::Render();
  glfwGetFramebufferSize(window.window, &display_w, &display_h);

  constexpr ImVec4 clearColor{0.0, 0.0, 0.0, 1.0};

  glViewport(0, 0, display_w, display_h);
  glClearColor(clearColor.x * clearColor.w, clearColor.y * clearColor.w,
               clearColor.z * clearColor.w, clearColor.w);
  glClear(GL_COLOR_BUFFER_BIT);

  ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
  if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
  }
  glfwMakeContextCurrent(window.window);
  glfwSwapBuffers(window.window);
}

void UpdateStyle() {
  float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(window.monitor);
  ImGuiIO &io = ImGui::GetIO();
  ImGuiStyle &style = ImGui::GetStyle();
  style.ScaleAllSizes(main_scale);
  style.FontScaleDpi = main_scale;
#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
  io.ConfigDpiScaleFonts = true;
  io.ConfigDpiScaleViewports = true;
#endif
}


void Dockspace() {
  ImGui::SetNextWindowPos(ImGui::GetMainViewport()->WorkPos);
  ImGui::SetNextWindowSize(ImVec2(ImGui::GetMainViewport()->WorkSize.x, ImGui::GetMainViewport()->WorkSize.y));

  ImGuiWindowFlags host_window_flags = 0;
  host_window_flags |= ImGuiWindowFlags_NoTitleBar |
                       ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
                       ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDocking;
  host_window_flags |=
      ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

  ImGuiDockNodeFlags dockspace_flags =
      ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode;

  ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  ImGui::Begin("MainDockspace", nullptr, host_window_flags);
  ImGui::PopStyleVar(3);

  ImGui::SetCursorPos({0, 0});

  ImGuiID dockspace_id = ImGui::GetID("DockSpace");
  ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags, nullptr);
  ImGui::End();
}
