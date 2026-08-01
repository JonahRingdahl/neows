#include "NeosCurrier.hpp"
#include "Neo.hpp"
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

#include <httplib.h>
#include <nlohmann/json.hpp>
#include <raylib.h>

NeosCurrier::NeosCurrier(Model *asteroidModel) {
  this->asteroidModel = asteroidModel;
}

auto NeosCurrier::GetSelectedNeo() -> std::unique_ptr<Neo> & {
  if (this->neos.empty()) {
    static std::unique_ptr<Neo> empty_neo = nullptr;
    return empty_neo;
  }
  return this->neos[this->render_index];
}

auto NeosCurrier::DrawNeos() -> void {
  for (const auto &neo : this->neos)
    neo->Draw(this->asteroidModel);
}

auto NeosCurrier::SetLink(nlohmann::json &link_json) -> void {
  this->links = link_json.dump();
}

auto NeosCurrier::DrawSelectedNeoPointer() -> void {
  if (this->neos.empty()) return;
  // Triangle above the position of the selected neo
  Vector3 selected_neo_position =
      this->neos[this->render_index]->GetRenderPosition();
  Vector3 arrow_position =
      (Vector3){selected_neo_position.x, selected_neo_position.y + 10,
                selected_neo_position.z};
  Vector3 arrow_bottom =
      (Vector3){arrow_position.x, arrow_position.y - 3, arrow_position.z};

  DrawCylinderEx(arrow_bottom, arrow_position, 0.0, 2.0, 100, RED);
}

auto NeosCurrier::SetPages(nlohmann::json &pages_json) -> void {
  this->pages = pages_json.dump();
}

auto NeosCurrier::UpdateNeosPosition(double time, float startTime,
                                     double angleRadians) -> void {
  int numObjects = this->neos.size();
  std::vector<double> angles = CalculateLineSpace(0, 2 * PI, numObjects);

  for (int i = 0; i < numObjects; i++) {
    float x = radius;
    float z = radius;

    // rotation
    x = x * cos(angles[i] + angleRadians * time) -
        z * sin(angles[i] + angleRadians * time);
    z = z * sin(angles[i] + angleRadians * time) +
        z * cos(angles[i] + angleRadians * time);
    float y = sin(time) * (z + x) / 2;

    this->neos[i]->SetRenderPosition((Vector3){x, y, z});
  }
}

auto NeosCurrier::CalculateLineSpace(double start, double end, int num)
    -> std::vector<double> {
  std::vector<double> linespace;
  if (num == 0)
    return linespace;
  if (num == 1) {
    linespace.push_back(start);
    return linespace;
  }

  double delta = (end - start) / (num);
  for (int i = 0; i < num; i++) {
    linespace.emplace_back(start + delta * i);
  }

  return linespace;
}

auto NeosCurrier::AddNeo(std::unique_ptr<Neo> neo) -> void {
  this->neos.emplace_back(std::move(neo));
}

auto NeosCurrier::DeleteAllNeos() -> void { this->neos.clear(); }

auto NeosCurrier::DeleteSelectedNeo() -> void {
  this->neos.erase(this->neos.begin() + this->render_index);
}

auto NeosCurrier::ChangeFocusAsteroid() -> void {
  // Move up the list
  if (this->neos.size() == 0)
    return;
  if (IsKeyPressed(KEY_J)) {
    if (this->render_index == 0) {
      this->render_index = this->neos.size() - 1;
    } else {
      this->render_index -= 1;
    }
  }
  if (IsKeyPressed(KEY_K)) {
    if (this->render_index == (int)this->neos.size() - 1) {
      this->render_index = 0;
    } else {
      this->render_index += 1;
    }
  }
  if (IsKeyPressed(KEY_F)) {
    std::cout << "Try Deleting" << '\n';
    DeleteAllNeos();
  }
}
