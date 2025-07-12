#pragma once

#include "window/window.hpp"
#include <memory>
#include <thread>
#include <string>
#include <vector>

#include <Eigen/Core>

using vec = Eigen::VectorXd;

enum class element_type {
  line,
  scatter,
  bar
};

struct xy_element {
  std::string name;

  vec x;
  vec y;

  element_type type;
};
struct xyz_element {
  std::string name;

  vec x;
  vec y;
  vec z;

  element_type type;
};

struct plt {
  std::string name;
  std::vector<xy_element> axis;
};
struct plt3 {
  std::string name;
  std::vector<xyz_element> axis;
};

struct sub {
  std::string name;
  std::vector<plt> plots;
};
struct sub3 {
  std::string name;
  std::vector<plt3> plots;
};

class Figure {
public:
  Figure(const std::string &name="fig");
  void WaitForEnd();
  void Close();

  // 2D
  void AddPlot(const std::string &name);
  int AddLinePlot(const std::string &name, const vec &x, const vec &y);
  void SetLinePlot(int id, const vec &x, const vec &y);
  int AddScatterPlot(const std::string &name, const vec &x, const vec &y);
  void SetScatterPlot(int id, const vec &x, const vec &y);
  // 3D
  void AddPlot3(const std::string &name);
  int AddLinePlot3(const std::string &name, const vec &x, const vec &y, const vec &z);
  void SetLinePlot3(int id, const vec &x, const vec &y, const vec &z);
  int AddScatterPlot3(const std::string &name, const vec &x, const vec &y, const vec &z);
  void SetScatterPlot3(int id, const vec &x, const vec &y, const vec &z);

private:
  std::string name;
  std::thread *t;
  bool stopThread;

  window_t window;

  std::vector<sub> subplots;
  std::vector<sub3> subplots3;
  std::vector<plt> plots;
  std::vector<plt3> plots3;

  void Run();
};
