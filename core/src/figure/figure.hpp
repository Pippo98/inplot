#pragma once

#include <memory>
#include <thread>
#include <string>
#include <vector>

#include <Eigen/Core>

struct xy_pair {
  Eigen::VectorXd x;
  Eigen::VectorXd y;
};
struct xyz_pair {
  Eigen::VectorXd x;
  Eigen::VectorXd y;
  Eigen::VectorXd z;
};

struct plt {
  std::string name;
  std::vector<xy_pair> axis;
};
struct plt3 {
  std::string name;
  std::vector<xyz_pair> axis;
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
private:
  std::string name;
  std::thread *t;
  bool stopThread;

  void Run();
};
