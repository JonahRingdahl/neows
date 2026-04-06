#pragma once

#include <nlohmann/json.hpp>
#include <raylib.h>
#include <raymath.h>
#include <string>
#include <vector>

namespace neows {

struct EstimatedDiameter {
  double min_kilometers;
  double max_kilometers;
  double min_meters;
  double max_meters;
  double min_miles;
  double max_miles;
  double min_feet;
  double max_feet;

  static EstimatedDiameter fromJson(const nlohmann::json &j);
};

struct RelativeVelocity {
  double kilometers_per_second;
  double kilometers_per_hour;
  double miles_per_hour;

  static RelativeVelocity fromJson(const nlohmann::json &j);
};

struct MissDistance {
  double astronomical;
  double lunar;
  double kilometers;
  double miles;

  static MissDistance fromJson(const nlohmann::json &j);
};

struct CloseApproachData {
  std::string close_approach_date;
  int64_t epoch_date_close_approach;
  RelativeVelocity relative_velocity;
  MissDistance miss_distance;
  std::string orbiting_body;

  static CloseApproachData fromJson(const nlohmann::json &j);
};

class Neo {
public:
  explicit Neo(const nlohmann::json &json);

  std::string Id() { return id; }
  std::string NeoReferenceId() { return neo_reference_id; }
  std::string Name() { return name; }
  std::string NasaJplUrl() { return nasa_jpl_url; }
  double AbsoluteMagnitude() { return absolute_magnitude; }
  EstimatedDiameter &GetEstimatedDiameter() { return estimated_diameter; }
  bool IsPotentiallyHazardous() { return is_potentially_hazardous; }
  bool IsSentryObject() { return is_sentry_object; }
  std::vector<CloseApproachData> &GetCloseApproachData() {
    return close_approach_data;
  }

  std::string SelfLink() const { return self_link; }

  const Vector3 GetNeoPosition() const { return position; }
  void UpdateNeoPosition(Vector3 new_position) { position = new_position; }
  void DrawNeo(Model &asteroid_model) {
    DrawModel(asteroid_model, this->position, this->scale, WHITE);
  }

private:
  std::string id;
  std::string neo_reference_id;
  std::string name;
  std::string nasa_jpl_url;
  double absolute_magnitude = 0.0;
  EstimatedDiameter estimated_diameter;
  bool is_potentially_hazardous = false;
  bool is_sentry_object = false;
  std::vector<CloseApproachData> close_approach_data;
  std::string self_link;
  float scale = 1;

  Vector3 position;
};

} // namespace neows
