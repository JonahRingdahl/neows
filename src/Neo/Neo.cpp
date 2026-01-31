
#include <cstdint>
#include <limits>
#include <memory>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <vector>

#include <raylib.h>

#include "Diameter.hpp"
#include "Neo.hpp"

void Neo::SetLink(nlohmann::json &link_json) {
  this->link = link_json.get<std::string>();
}

void Neo::SetID(nlohmann::json &id_json) {
  using integer = nlohmann::json::number_integer_t;
  auto ivalue = id_json.get<integer>();
  if (ivalue < std::numeric_limits<int>::min() ||
      ivalue > std::numeric_limits<int>::max()) {
    throw std::runtime_error("ID is out of range");
  }

  this->id = id_json.get<int64_t>();
}

void Neo::SetNeoID(nlohmann::json &neo_id_json) {
  this->neo_ref_id = neo_id_json.get<std::string>();
}

void Neo::SetName(nlohmann::json &name_json) {
  this->name = name_json.get<std::string>();
}

void Neo::SetNasaJPLURL(nlohmann::json &nasa_jps_url_json) {
  this->nasa_jpl_url = nasa_jps_url_json.get<std::string>();
}

void Neo::SetMagnitude(nlohmann::json &magnitude_json) {
  this->absolute_magnitude_h = magnitude_json.get<float>();
}

void Neo::SetDiameter(nlohmann::json &diameter_json) {
  if (diameter_json.is_null()) {
    this->diameter = std::make_unique<Diameter>(Diameter(diameter_json));
  }
}

void Neo::SetHazardous(nlohmann::json &hazardous_json) {
  this->is_potentially_hazardous_asteroid = hazardous_json.get<bool>();
}

void Neo::SetCloseApproach(std::vector<nlohmann::json> &close_approach_json) {
  for (const auto &ca : close_approach_json) {
    this->close_approach.push_back(
        std::make_unique<CloseApproach>(CloseApproach(ca)));
  }
}

void Neo::SetIsSentryObject(nlohmann::json &is_sentry_object_json) {
  this->is_sentry_object = is_sentry_object_json.get<bool>();
}

void Neo::SetRenderPosition(Vector3 position) { this->position = position; }
void Neo::SetRenderRadius(float r) { this->render_radius = r; }

int64_t Neo::GetID() { return id; }
const std::string &Neo::GetNeoID() { return neo_ref_id; }
const std::string &Neo::GetName() { return name; }
const std::string &Neo::GetLink() { return link; }
float Neo::GetMagnitude() { return absolute_magnitude_h; }
bool Neo::GetHazardous() { return is_potentially_hazardous_asteroid; }
const std::unique_ptr<Diameter> &Neo::GetDiameter() { return this->diameter; }
bool Neo::GetIsSentryObject() { return this->is_sentry_object; }

float Neo::GetRenderRadius() { return this->render_radius; }
const Vector3 &Neo::GetRenderPosition() { return this->position; }

std::vector<std::unique_ptr<CloseApproach>> &Neo::GetCloseApproach() {
  return this->close_approach;
}

void Neo::Draw(Model *model) { DrawModel(*model, this->position, 1, BROWN); }
