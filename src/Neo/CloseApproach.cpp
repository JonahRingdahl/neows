#include "CloseApproach.hpp"
#include "nlohmann/json.hpp"
#include <iostream>

CloseApproach::CloseApproach(nlohmann::json close_approach_json) {
  this->close_approach_date = close_approach_json["close_approach_date"];
  this->close_approach_date_full =
      close_approach_json["close_approach_date_full"];
  this->epoch_date_close_approach =
      close_approach_json["epoch_date_close_approach"];

  auto relative_velocity = close_approach_json["relative_velocity"];
  this->relative_vel_kps = relative_velocity["kilometers_per_second"];
  this->relative_vel_kph = relative_velocity["kilometers_per_hour"];
  this->relative_vel_mph = relative_velocity["miles_per_hour"];

  auto miss_distance = close_approach_json["miss_distance"];
  this->miss_dist_astronomical = miss_distance["astronomical"];
  this->miss_dist_lunar = miss_distance["lunar"];
  this->miss_dist_kilometer = miss_distance["kilometers"];
  this->miss_dist_miles = miss_distance["miles"];
}

CloseApproach::~CloseApproach() {}

void CloseApproach::PrintCloseApproach() {
  std::cout << "Approach Date:" << this->close_approach_date << '\n';
  std::cout << "Approach Date Full:" << this->close_approach_date_full << '\n';
  std::cout << "Approach Date:" << this->epoch_date_close_approach << '\n';

  std::cout << "Relative Velocity Kps:" << this->relative_vel_kps << '\n';
  std::cout << "Relative Velocity Kph:" << this->relative_vel_kph << '\n';
  std::cout << "Relative Velocity Mph:" << this->relative_vel_mph << '\n';

  std::cout << "Miss Distance (Astronomical Units):"
            << this->miss_dist_astronomical << '\n';
  std::cout << "Miss Distance (Lunar Distance Units):" << this->miss_dist_lunar
            << '\n';
  std::cout << "Miss Distance (Kilometers):" << this->miss_dist_kilometer
            << '\n';
  std::cout << "Miss Distance (Miles):" << this->miss_dist_miles << '\n';
  std::cout << "Approach Date:" << this->epoch_date_close_approach << '\n';
}
