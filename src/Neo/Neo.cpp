#include "Neo.hpp"
#include "Diameter.hpp"
#include "raylib.h"

#include <cstdint>
#include <limits>
#include <memory>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <vector>

Neo::Neo(NeoData& neo_data) {
  this->link = neo_data.link;
  this->id = neo_data.id;
  this->neo_ref_id = neo_data.neo_ref_id;
  this->name = neo_data.name;
  this->nasa_jpl_url = neo_data.nasa_jpl_url;
  this->absolute_magnitude_h = neo_data.absolute_magnitude_h;
  this->diameter = std::make_unique<Diameter>(*neo_data.diameter);
  this->is_potentially_hazardous_asteroid =
      neo_data.is_potentially_hazardous_asteroid;
  for (auto &ca : neo_data.close_approach) {
    this->close_approach.push_back(std::move(ca));
  }
  this->is_sentry_oject = neo_data.is_sentry_oject;
}

Neo::Neo(nlohmann::json neo_json) {
  this->link = neo_json["links"]["self"].get<std::string>();
  this->id = std::stoll(neo_json["id"].get<std::string>());
  this->neo_ref_id = neo_json["neo_reference_id"].get<std::string>();
  this->name = neo_json["name"].get<std::string>();
  this->nasa_jpl_url = neo_json["nasa_jpl_url"].get<std::string>();
  this->absolute_magnitude_h = neo_json["absolute_magnitude_h"].get<float>();
  
  if (!neo_json["estimated_diameter"].is_null()) {
    this->diameter = std::make_unique<Diameter>(neo_json["estimated_diameter"]);
  }

  this->is_potentially_hazardous_asteroid = neo_json["is_potentially_hazardous_asteroid"].get<bool>();
  
  for (auto& ca : neo_json["close_approach_data"]) {
    this->close_approach.push_back(std::make_unique<CloseApproach>(ca));
  }

  this->is_sentry_oject = neo_json["is_sentry_object"].get<bool>();
}

auto Neo::SetLink(nlohmann::json &link_json) -> void {
  this->link = link_json.get<std::string>();
}

auto Neo::SetID(nlohmann::json &id_json) -> void {
  using integer = nlohmann::json::number_integer_t;
  auto ivalue = id_json.get<integer>();
  if (!(ivalue < std::numeric_limits<int>::min() ||
        ivalue > std::numeric_limits<int>::max())) {
    this->id = id_json.get<int64_t>();
    return;
  }

  throw std::runtime_error("ID is out of range");
}

auto Neo::SetNeoID(nlohmann::json &neo_id_json) -> void {
  this->neo_ref_id = neo_id_json.get<std::string>();
}

auto Neo::SetName(nlohmann::json &name_json) -> void {
  this->name = name_json.get<std::string>();
}

auto Neo::SetNasaJPLURL(nlohmann::json &nasa_jps_url_json) -> void {
  this->nasa_jpl_url = nasa_jps_url_json.get<std::string>();
}

auto Neo::SetMagnitude(nlohmann::json &magnitude_json) -> void {
  this->absolute_magnitude_h = magnitude_json.get<float>();
}

auto Neo::SetDiameter(nlohmann::json &diameter_json) -> void {
  if (!diameter_json.is_null()) {
    this->diameter = std::make_unique<Diameter>(Diameter(diameter_json));
  }
}

auto Neo::SetHazardous(nlohmann::json &hazardous_json) -> void {
  this->is_potentially_hazardous_asteroid = hazardous_json.get<bool>();
}

auto Neo::SetCloseApproach(std::vector<nlohmann::json> &close_approach_json)
    -> void {
  for (const auto &ca : close_approach_json) {
    this->close_approach.push_back(
        std::make_unique<CloseApproach>(CloseApproach(ca)));
  }
}

auto Neo::SetIsSentryObject(nlohmann::json &is_sentry_object_json) -> void {
  this->is_sentry_oject = is_sentry_object_json.get<bool>();
}

auto Neo::SetRenderPosition(Vector3 position) -> void {
  this->position = position;
}
auto Neo::SetRenderRadius(float r) -> void { this->render_radius = r; }

auto Neo::GetID() -> const int64_t { return id; }
auto Neo::GetNeoID() -> const std::string { return neo_ref_id; }
auto Neo::GetName() -> const std::string { return name; }
auto Neo::GetLink() -> const std::string { return link; }
auto Neo::GetMagnitude() -> const float { return absolute_magnitude_h; }
auto Neo::GetHazardous() -> const bool {
  return is_potentially_hazardous_asteroid;
}
auto Neo::GetDiameter() -> const std::unique_ptr<Diameter> & {
  return this->diameter;
}

auto Neo::GetRenderPosition() -> const Vector3 { return this->position; }
auto Neo::GetRenderRadius() -> const float { return this->render_radius; }
auto Neo::GetIsSentryObject() -> const bool { return this->is_sentry_oject; }

auto Neo::GetCloseApproach()
    -> const std::vector<std::unique_ptr<CloseApproach>> & {
  return this->close_approach;
}

void Neo::Draw(Model *model) { DrawModel(*model, this->position, 1, BROWN); }
