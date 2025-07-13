#pragma once

#include "window/window.hpp"
#include <memory>
#include <thread>
#include <string>
#include <vector>

#include <Eigen/Core>
#include "types.hpp"

class Figure;

class Manager {
public:
  ~Manager();
  void Start();
  void Stop();
  void WaitForEnd();

  Figure *AddFigure(const std::string &name);
  bool RemoveFigure(Figure *fig);
private:
  std::string name;
  std::thread *t = nullptr;
  bool stopThread = false;

  std::vector<Figure *> figures;

  void Run();
};

class Figure {
public:
  ~Figure();
  Figure(const std::string &name="fig");
  void Draw();
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
  std::vector<sub> subplots;
  std::vector<sub3> subplots3;
  std::vector<plt> plots;
  std::vector<plt3> plots3;

  friend class Manager;
};

void Start();
void Stop();
void WaitForEnd();
Figure *figure(const std::string &name);
