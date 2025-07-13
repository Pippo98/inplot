#include "figure.hpp"
#include "core/src/window/window.hpp"
#include "imgui.h"
#include "implot.h"
#include "implot3d.h"

#include <algorithm>

static Manager manager;

void Start() { manager.Start(); }
void Stop() { manager.Stop(); }
void WaitForEnd() { manager.WaitForEnd(); }

Manager::~Manager() {
  stopThread = true;
  WaitForEnd();
}
void Manager::Start() {
  stopThread = false;
  t = new std::thread(&Manager::Run, this);
}
void Manager::Stop() { stopThread = true; }
void Manager::WaitForEnd() { 
  if(t != nullptr && t->joinable()) {
    t->join();
  }
}

Figure *Manager::AddFigure(const std::string &name) {
  figures.push_back(new Figure(name));
  return figures.back();
}
bool Manager::RemoveFigure(Figure *fig) {
  return std::erase_if(figures, [&](const auto &ptr) {
    return ptr == fig;
  });
}

Figure *figure(const std::string &name = "fig") {
  return manager.AddFigure(name);
}

void Manager::Run() {
  OpenWindow(name);
  while (!stopThread && !ShouldClose()) {
    NewFrame();
    Dockspace();

    for (auto &fig : figures) {
      if (ImGui::Begin(fig->name.c_str())) {
        fig->Draw();
      }
      ImGui::End();
    }

    RenderFrame();
  }
}

Figure::~Figure() {

}

Figure::Figure(const std::string &_name) : name(_name) {}

void Figure::Draw() {
  ImGui::PushID("2D plots");
  for (auto &plot : plots) {
    if (ImPlot::BeginPlot(plot.name.c_str())) {
      for (auto &ax : plot.axis) {
        if (ax.type == element_type::line) {
          ImPlot::PlotLine(ax.name.c_str(), ax.x.data(), ax.y.data(),
                           ax.x.size());
        } else if (ax.type == element_type::scatter) {
          ImPlot::PlotScatter(ax.name.c_str(), ax.x.data(), ax.y.data(),
                              ax.x.size());
        }
      }
      ImPlot::EndPlot();
    }
  }
  ImGui::PopID();
  ImGui::PushID("3D plots");
  for (auto &plot : plots3) {
    if (ImPlot3D::BeginPlot(plot.name.c_str())) {
      for (auto &ax : plot.axis) {
        if (ax.type == element_type::line) {
          ImPlot3D::PlotLine(ax.name.c_str(), ax.x.data(), ax.y.data(),
                             ax.z.data(), ax.x.size());
        } else if (ax.type == element_type::scatter) {
          ImPlot3D::PlotScatter(ax.name.c_str(), ax.x.data(), ax.y.data(),
                                ax.z.data(), ax.x.size());
        }
      }
      ImPlot3D::EndPlot();
    }
  }
  ImGui::PopID();
}

void Figure::AddPlot(const std::string &name) {
  plt newPlot;
  newPlot.name = name;
  plots.push_back(std::move(newPlot));
}

int Figure::AddLinePlot(const std::string &name, const vec &x, const vec &y) {
  xy_element xy;
  xy.name = name;
  xy.type = element_type::line;
  xy.x = x;
  xy.y = y;
  plots.back().axis.push_back(std::move(xy));
  return plots.back().axis.size() - 1;
}
void Figure::SetLinePlot(int id, const vec &x, const vec &y) {
  xy_element &xy = plots.back().axis[id];
  xy.type = element_type::line;
  xy.x = x;
  xy.y = y;
}
int Figure::AddScatterPlot(const std::string &name, const vec &x,
                           const vec &y) {
  xy_element xy;
  xy.name = name;
  xy.type = element_type::scatter;
  xy.x = x;
  xy.y = y;
  plots.back().axis.push_back(std::move(xy));
  return plots.back().axis.size() - 1;
}
void Figure::SetScatterPlot(int id, const vec &x, const vec &y) {
  xy_element &xy = plots.back().axis[id];
  xy.type = element_type::scatter;
  xy.x = x;
  xy.y = y;
}

void Figure::AddPlot3(const std::string &name) {
  plt3 newPlot;
  newPlot.name = name;
  plots3.push_back(std::move(newPlot));
}
int Figure::AddLinePlot3(const std::string &name, const vec &x, const vec &y,
                         const vec &z) {
  xyz_element xyz;
  xyz.name = name;
  xyz.type = element_type::line;
  xyz.x = x;
  xyz.y = y;
  xyz.z = z;
  plots3.back().axis.push_back(std::move(xyz));
  return plots3.back().axis.size() - 1;
}
void Figure::SetLinePlot3(int id, const vec &x, const vec &y, const vec &z) {
  xyz_element &xyz = plots3.back().axis[id];
  xyz.type = element_type::line;
  xyz.x = x;
  xyz.y = y;
  xyz.z = z;
}
int Figure::AddScatterPlot3(const std::string &name, const vec &x, const vec &y,
                            const vec &z) {
  xyz_element xyz;
  xyz.name = name;
  xyz.type = element_type::scatter;
  xyz.x = x;
  xyz.y = y;
  xyz.z = z;
  plots3.back().axis.push_back(std::move(xyz));
  return plots3.back().axis.size() - 1;
}
void Figure::SetScatterPlot3(int id, const vec &x, const vec &y, const vec &z) {
  xyz_element &xyz = plots3.back().axis[id];
  xyz.type = element_type::scatter;
  xyz.x = x;
  xyz.y = y;
  xyz.z = z;
}
