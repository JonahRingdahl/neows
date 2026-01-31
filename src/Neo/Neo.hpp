#pragma once
#include <memory>
#include <raylib.h>
#include <raymath.h>
#include <string>
#include <vector>

#include "CloseApproach.hpp"
#include "Diameter.hpp"

class Neo {
public:
  Neo() = default;
  // getters setters //

  void SetLink(nlohmann::json &link_json);
  void SetID(nlohmann::json &id_json);
  void SetNeoID(nlohmann::json &neo_id_json);
  void SetName(nlohmann::json &name_json);
  void SetNasaJPLURL(nlohmann::json &nasa_jpl_url_json);
  void SetMagnitude(nlohmann::json &magnitude_json);
  void SetDiameter(nlohmann::json &diameter_json);
  void SetHazardous(nlohmann::json &hazardous_json);
  void SetCloseApproach(std::vector<nlohmann::json> &close_approach_json);
  void SetIsSentryObject(nlohmann::json &is_sentry_object_json);

  void SetRenderPosition(Vector3 position);
  void SetRenderRadius(float r);

  int64_t GetID();
  const std::string &GetNeoID();
  const std::string &GetName();
  const std::string &GetLink();
  float GetMagnitude();
  bool GetHazardous();
  const std::unique_ptr<Diameter> &GetDiameter();
  const Vector3 &GetRenderPosition();
  float GetRenderRadius();
  bool GetIsSentryObject();
  std::vector<std::unique_ptr<CloseApproach>> &GetCloseApproach();

  void Draw(Model *model);

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
  bool is_sentry_object;
};
