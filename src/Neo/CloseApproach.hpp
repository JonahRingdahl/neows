#pragma once

#include <nlohmann/json.hpp>
#include <string>

struct CloseApproach {
  CloseApproach(nlohmann::json close_approach_json);
  ~CloseApproach();

  void PrintCloseApproach();

  std::string close_approach_date;
  std::string close_approach_date_full;
  unsigned long long epoch_date_close_approach;
  std::string relative_vel_kps;
  std::string relative_vel_kph;
  std::string relative_vel_mph;

  std::string miss_dist_astronomical;
  std::string miss_dist_lunar;
  std::string miss_dist_kilometer;
  std::string miss_dist_miles;
  std::string orbiting_body;
};
