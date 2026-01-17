#pragma once
#include <nlohmann/json.hpp>
#include <tuple>

struct Diameter {
  Diameter(nlohmann::json diameter_json);
  Diameter(Diameter &&) = default;
  Diameter(const Diameter &) = default;
  Diameter &operator=(Diameter &&) = default;
  Diameter &operator=(const Diameter &) = default;
  ~Diameter();

  void DisplayDiameter();

  std::tuple<double, double> kilometer_min_max;
  std::tuple<double, double> meter_min_max;
  std::tuple<double, double> miles_min_max;
  std::tuple<double, double> feet_min_max;
};
