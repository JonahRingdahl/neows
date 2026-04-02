#include "neo.hpp"

namespace neows {

EstimatedDiameter EstimatedDiameter::fromJson(const nlohmann::json &j) {
  EstimatedDiameter d;
  d.minKilometers = j["kilometers"]["estimated_diameter_min"].get<double>();
  d.maxKilometers = j["kilometers"]["estimated_diameter_max"].get<double>();
  d.minMeters = j["meters"]["estimated_diameter_min"].get<double>();
  d.maxMeters = j["meters"]["estimated_diameter_max"].get<double>();
  d.minMiles = j["miles"]["estimated_diameter_min"].get<double>();
  d.maxMiles = j["miles"]["estimated_diameter_max"].get<double>();
  d.minFeet = j["feet"]["estimated_diameter_min"].get<double>();
  d.maxFeet = j["feet"]["estimated_diameter_max"].get<double>();
  return d;
}

RelativeVelocity RelativeVelocity::fromJson(const nlohmann::json &j) {
  RelativeVelocity v;
  v.kilometersPerSecond =
      std::stod(j["kilometers_per_second"].get<std::string>());
  v.kilometersPerHour = std::stod(j["kilometers_per_hour"].get<std::string>());
  v.milesPerHour = std::stod(j["miles_per_hour"].get<std::string>());
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
  cad.closeApproachDate = j["close_approach_date"].get<std::string>();
  cad.epochDateCloseApproach = j["epoch_date_close_approach"].get<int64_t>();
  cad.relativeVelocity = RelativeVelocity::fromJson(j["relative_velocity"]);
  cad.missDistance = MissDistance::fromJson(j["miss_distance"]);
  cad.orbitingBody = j["orbiting_body"].get<std::string>();
  return cad;
}

Neo::Neo(const nlohmann::json &json) {
  if (json.contains("Err"))
    return;

  if (json.contains("id")) {
    m_id = json["id"].get<std::string>();
  }

  if (json.contains("neo_reference_id")) {
    m_neoReferenceId = json["neo_reference_id"].get<std::string>();
  } else if (json.contains("id")) {
    m_neoReferenceId = json["id"].get<std::string>();
  }

  if (json.contains("name")) {
    m_name = json["name"].get<std::string>();
  } else if (json.contains("designation")) {
    m_name = json["designation"].get<std::string>();
  }

  if (json.contains("nasa_jpl_url")) {
    m_nasaJplUrl = json["nasa_jpl_url"].get<std::string>();
  }

  if (json.contains("absolute_magnitude_h")) {
    m_absoluteMagnitude = json["absolute_magnitude_h"].get<double>();
  }

  if (json.contains("estimated_diameter")) {
    m_estimatedDiameter =
        EstimatedDiameter::fromJson(json["estimated_diameter"]);
  }

  if (json.contains("is_potentially_hazardous_asteroid")) {
    m_isPotentiallyHazardous =
        json["is_potentially_hazardous_asteroid"].get<bool>();
  }

  if (json.contains("is_sentry_object")) {
    m_isSentryObject = json["is_sentry_object"].get<bool>();
  }

  if (json.contains("close_approach_data")) {
    for (const auto &cadJson : json["close_approach_data"]) {
      m_closeApproachData.push_back(CloseApproachData::fromJson(cadJson));
    }
  }

  if (json.contains("links") && json["links"].contains("self")) {
    m_selfLink = json["links"]["self"].get<std::string>();
  }
}

} // namespace neows
