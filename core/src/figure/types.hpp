#pragma once
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
