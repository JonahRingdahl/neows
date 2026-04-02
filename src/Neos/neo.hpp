#pragma once

#include <nlohmann/json.hpp>
#include <optional>
#include <raylib.h>
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

  std::string Id() const { return m_id; }
  std::string NeoReferenceId() const { return m_neoReferenceId; }
  std::string Name() const { return m_name; }
  std::string NasaJplUrl() const { return m_nasaJplUrl; }
  double AbsoluteMagnitude() const { return m_absoluteMagnitude; }
  const EstimatedDiameter &EstimatedDiameter() const {
    return m_estimatedDiameter;
  }
  bool IsPotentiallyHazardous() const { return m_isPotentiallyHazardous; }
  bool IsSentryObject() const { return m_isSentryObject; }
  const std::vector<CloseApproachData> &CloseApproachData() const {
    return m_closeApproachData;
  }

  std::string SelfLink() const { return m_selfLink; }

  const Vector3 GetNeoPosition() const { return position; }
  void UpdateNeoPosition(Vector3 new_position) { position = new_position; }

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

  Vector3 position;
};

} // namespace neows
