#pragma once

#include "nlohmann/json_fwd.hpp"

#include <string>

using json = nlohmann::json;

struct OrbitalData {
  OrbitalData(json data);
  ~OrbitalData();

  uint orbital_id;
  std::string orbit_determination_date;
  std::string first_observation_date;
  std::string last_observation_date;
  uint data_arc_in_days;
  uint observations_used;
  std::string orbital_uncertainty;
  double minimum_orbit_intersection;
  double jupiter_tisserand_invariant;
  double epoch_occultation;
  double eccentricity;
  double semi_major_axis;
  double inclination;
  double ascending_node_longitude;
  double orbital_period;
  double perihelion_distance;
  double perihelion_argument;
  double aphelion_distance;
  double perihelion_time;
  double mean_anomaly;
  double mean_motion;
  std::string equinox;
  // OrbitClass orbit_class;
};
