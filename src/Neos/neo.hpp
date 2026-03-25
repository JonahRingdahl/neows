#pragma once

#include <nlohmann/json.hpp>
#include <optional>
#include <string>
#include <vector>

namespace neows {

struct EstimatedDiameter {
  double minKilometers;
  double maxKilometers;
  double minMeters;
  double maxMeters;
  double minMiles;
  double maxMiles;
  double minFeet;
  double maxFeet;

  static EstimatedDiameter fromJson(const nlohmann::json &j);
};

struct RelativeVelocity {
  double kilometersPerSecond;
  double kilometersPerHour;
  double milesPerHour;

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
  std::string closeApproachDate;
  int64_t epochDateCloseApproach;
  RelativeVelocity relativeVelocity;
  MissDistance missDistance;
  std::string orbitingBody;

  static CloseApproachData fromJson(const nlohmann::json &j);
};

class Neo {
public:
  explicit Neo(const nlohmann::json &json);

  std::string id() const { return m_id; }
  std::string neoReferenceId() const { return m_neoReferenceId; }
  std::string name() const { return m_name; }
  std::string nasaJplUrl() const { return m_nasaJplUrl; }
  double absoluteMagnitude() const { return m_absoluteMagnitude; }
  const EstimatedDiameter &estimatedDiameter() const {
    return m_estimatedDiameter;
  }
  bool isPotentiallyHazardous() const { return m_isPotentiallyHazardous; }
  bool isSentryObject() const { return m_isSentryObject; }
  const std::vector<CloseApproachData> &closeApproachData() const {
    return m_closeApproachData;
  }

  std::string selfLink() const { return m_selfLink; }

private:
  std::string m_id;
  std::string m_neoReferenceId;
  std::string m_name;
  std::string m_nasaJplUrl;
  double m_absoluteMagnitude = 0.0;
  EstimatedDiameter m_estimatedDiameter;
  bool m_isPotentiallyHazardous = false;
  bool m_isSentryObject = false;
  std::vector<CloseApproachData> m_closeApproachData;
  std::string m_selfLink;
};

} // namespace neows
