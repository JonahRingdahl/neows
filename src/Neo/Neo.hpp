#pragma once
#include <memory>
#include <raylib.h>
#include <raymath.h>
#include <string>
#include <vector>

#include "CloseApproach.hpp"
#include "Diameter.hpp"

struct NeoData {
  std::string link;
  int64_t id;
  std::string neo_ref_id;
  std::string name;
  std::string nasa_jpl_url;
  float absolute_magnitude_h;
  std::unique_ptr<Diameter> diameter;
  bool is_potentially_hazardous_asteroid;
  std::vector<std::unique_ptr<CloseApproach>> close_approach;
  bool is_sentry_oject;
};

class Neo {
public:
  Neo() = default;
  Neo(NeoData& neo_data);
  Neo(nlohmann::json neo_json);

  // getters setters //
  auto SetLink(nlohmann::json &link_json) -> void;
  auto SetID(nlohmann::json &id_json) -> void;
  auto SetNeoID(nlohmann::json &neo_id_json) -> void;
  auto SetName(nlohmann::json &name_json) -> void;
  auto SetNasaJPLURL(nlohmann::json &nasa_jps_url_json) -> void;
  auto SetMagnitude(nlohmann::json &magnitude_json) -> void;
  auto SetDiameter(nlohmann::json &diameter_json) -> void;
  auto SetHazardous(nlohmann::json &hazardous_json) -> void;
  auto SetCloseApproach(std::vector<nlohmann::json> &close_approach_json)
      -> void;
  auto SetIsSentryObject(nlohmann::json &is_sentry_object_json) -> void;
  auto SetRenderPosition(Vector3 position) -> void;
  auto SetRenderRadius(float r) -> void;

  auto GetID() -> const int64_t;
  auto GetNeoID() -> const std::string;
  auto GetName() -> const std::string;
  auto GetLink() -> const std::string;
  auto GetMagnitude() -> const float;
  auto GetHazardous() -> const bool;
  auto GetDiameter() -> const std::unique_ptr<Diameter> &;
  auto GetRenderPosition() -> const Vector3;
  auto GetRenderRadius() -> const float;
  auto GetIsSentryObject() -> const bool;
  auto GetCloseApproach()
      -> const std::vector<std::unique_ptr<CloseApproach>> &;

  auto Draw(Model *model) -> void;

private:
  Vector3 position;
  float render_radius;

  std::string link;
  int64_t id;
  std::string neo_ref_id;
  std::string name;
  std::string nasa_jpl_url;
  float absolute_magnitude_h;
  std::unique_ptr<Diameter> diameter;
  bool is_potentially_hazardous_asteroid;
  std::vector<std::unique_ptr<CloseApproach>> close_approach;
  bool is_sentry_oject;
};
