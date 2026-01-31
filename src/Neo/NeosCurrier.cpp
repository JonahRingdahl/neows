#include "NeosCurrier.hpp"
#include "Neo.hpp"
#include <cmath>
#include <iostream>
#include <memory>
#include <optional>
#include <vector>

#include <httplib.h>
#include <nlohmann/json.hpp>
#include <raylib.h>

NeosCurrier::NeosCurrier(Model *asteroidModel) {
  this->asteroidModel.reset(asteroidModel);
}

std::optional<Neo &> NeosCurrier::GetSelectedNeo() {
  return *this->neos.at(this->render_index);
}
void NeosCurrier::DrawNeos() {
  for (auto &neo : this->neos)
    neo->Draw(this->asteroidModel.get());
}

void NeosCurrier::DrawSelectedNeoPointer() {
  // Triangle above the position of the selected neo
  Vector3 selected_neo_position =
      this->neos.at(this->render_index)->GetRenderPosition();
  Vector3 arrow_position =
      (Vector3){selected_neo_position.x, selected_neo_position.y + 10,
                selected_neo_position.z};
  Vector3 arrow_bottom =
      (Vector3){arrow_position.x, arrow_position.y - 3, arrow_position.z};

  DrawCylinderEx(arrow_bottom, arrow_position, 0.0, 2.0, 100, RED);
}

void NeosCurrier::UpdateNeosPosition(double time, float startTime,
                                     double angleRadians) {
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

    this->neos.at(i)->SetRenderPosition((Vector3){x, y, z});
  }
}

std::vector<double> NeosCurrier::CalculateLineSpace(double start, double end,
                                                    int num) {
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

void NeosCurrier::AddNeo(std::unique_ptr<Neo> neo) {
  this->neos.push_back(std::move(neo));
}

void NeosCurrier::DeleteAllNeos() { this->neos.clear(); }

void NeosCurrier::DeleteSelectedNeo() {
  if (this->neos.empty())
    return;

  auto eraser = this->neos.begin() + this->render_index;
  this->neos.erase(eraser);

  if (this->neos.empty()) {
    this->render_index = 0;
  }

  if (this->render_index >= static_cast<int>(this->neos.size())) {
    this->render_index = this->neos.size() - 1;
  }
}

void NeosCurrier::ChangeFocusAsteroid() {
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
