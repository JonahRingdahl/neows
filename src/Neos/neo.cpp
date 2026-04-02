#include "neo.hpp"

namespace neows {

EstimatedDiameter EstimatedDiameter::fromJson(const nlohmann::json &j) {
  EstimatedDiameter d;
  d.min_kilometers = j["kilometers"]["estimated_diameter_min"].get<double>();
  d.max_kilometers = j["kilometers"]["estimated_diameter_max"].get<double>();
  d.min_meters = j["meters"]["estimated_diameter_min"].get<double>();
  d.max_meters = j["meters"]["estimated_diameter_max"].get<double>();
  d.min_miles = j["miles"]["estimated_diameter_min"].get<double>();
  d.max_miles = j["miles"]["estimated_diameter_max"].get<double>();
  d.min_meet = j["feet"]["estimated_diameter_min"].get<double>();
  d.max_meet = j["feet"]["estimated_diameter_max"].get<double>();
  return d;
}

RelativeVelocity RelativeVelocity::fromJson(const nlohmann::json &j) {
  RelativeVelocity v;
  v.kilometers_per_second =
      std::stod(j["kilometers_per_second"].get<std::string>());
  v.kilometers_per_hour = std::stod(j["kilometers_per_hour"].get<std::string>());
  v.miles_per_hour = std::stod(j["miles_per_hour"].get<std::string>());
  return v;
}

MissDistance MissDistance::fromJson(const nlohmann::json &j) {
  MissDistance m;
  m.astronomical = std::stod(j["astronomical"].get<std::string>());
  m.lunar = std::stod(j["lunar"].get<std::string>());
  m.kilometers = std::stod(j["kilometers"].get<std::string>());
  m.miles = std::stod(j["miles"].get<std::string>());
  return m;
}

CloseApproachData CloseApproachData::fromJson(const nlohmann::json &j) {
  CloseApproachData cad;
  cad.close_approach_date = j["close_approach_date"].get<std::string>();
  cad.epoch_date_close_approach = j["epoch_date_close_approach"].get<int64_t>();
  cad.relative_velocity = RelativeVelocity::fromJson(j["relative_velocity"]);
  cad.miss_distance = MissDistance::fromJson(j["miss_distance"]);
  cad.orbiting_body = j["orbiting_body"].get<std::string>();
  return cad;
}

Neo::Neo(const nlohmann::json &json) {
  if (json.contains("Err"))
    return;

  if (json.contains("id")) {
    id = json["id"].get<std::string>();
  }

  if (json.contains("neo_reference_id")) {
    neo_reference_id = json["neo_reference_id"].get<std::string>();
  } else if (json.contains("id")) {
    neo_reference_id = json["id"].get<std::string>();
  }

  if (json.contains("name")) {
    name = json["name"].get<std::string>();
  } else if (json.contains("designation")) {
    name = json["designation"].get<std::string>();
  }

  if (json.contains("nasa_jpl_url")) {
    nasa_jpl_url = json["nasa_jpl_url"].get<std::string>();
  }

  if (json.contains("absolute_magnitude_h")) {
    absolute_magnitude = json["absolute_magnitude_h"].get<double>();
  }

  if (json.contains("estimated_diameter")) {
    estimated_diameter =
        EstimatedDiameter::fromJson(json["estimated_diameter"]);
  }

  if (json.contains("is_potentially_hazardous_asteroid")) {
    is_potentially_hazardous =
        json["is_potentially_hazardous_asteroid"].get<bool>();
  }

  if (json.contains("is_sentry_object")) {
    is_sentry_object = json["is_sentry_object"].get<bool>();
  }

  if (json.contains("close_approach_data")) {
    for (const auto &cadJson : json["close_approach_data"]) {
      close_approach_data.push_back(CloseApproachData::fromJson(cadJson));
    }
  }

  if (json.contains("links") && json["links"].contains("self")) {
    self_link = json["links"]["self"].get<std::string>();
  }
}

} // namespace neows
