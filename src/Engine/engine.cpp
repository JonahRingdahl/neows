#include "engine.hpp"
#include "../Neos/neo.hpp"

#include <memory>
#include <ranges>
#include <raylib.h>
#include <vector>

Engine::Engine() {
  this->camera = {0};
  this->camera.position = {0.0f, 10.0f, 10.0f};
  this->camera.target = {0.0f, 0.0f, 0.0f};
  this->camera.up = {0.0f, 1.0f, 0.0f};
  this->camera.fovy = 45.0f;
  this->camera.projection = CAMERA_PERSPECTIVE;

  for (int i = 0; i < 10; i++) {
    this->neos.emplace_back(std::make_unique<neows::Neo>("Err"));
  }
}

Engine::~Engine() {}

void Engine::update() {}

void Engine::draw() {
  BeginDrawing();

  EndDrawing();
}

void Engine::Run() {
  while (!WindowShouldClose()) {
    update();
    draw();
  }
}

void Engine::updateNeoPosition(double time, float start_time,
                               double angle_radians) {
  std::vector<double> angles;
  angles.reserve(this->neos.size());
  LineSpacing(angles, 0, 2 * PI);
}

void Engine::lineSpacing(std::vector<double> &angles, double start,
                         double end) {

  auto size = angles.size();

  if (size == 0) {
    return;
  }

  if (size == 1) {
    angles.emplace_back(start);
  }

  double delta = (end - start) / size;

  for (int i = 0; i < size; i++) {
    angles.emplace_back(start + delta * i);
  }
}

void Engine::addNeo() {}
void Engine::deleteSelectedNeo() {
  if (this->neos.size() == 0)
    return;

  auto eraser = this->neos.begin() + this->selected_neo_index;
  this->neos.erase(eraser);

  if (this->neos.size() == 0) {
    this->selected_neo_index = 0;
    return;
  }

  if (this->selected_neo_index >= static_cast<int>(this->neos.size())) {
    this->selected_neo_index = this->neos.size() - 1;
  }
}

void Engine::changeSelectedNeo() {
  if (this->neos.size() == 0)
    return;
  if (IsKeyPressed(KEY_J)) {
    if (this->selected_neo_index == 0) {
      this->selected_neo_index = this->neos.size() - 1;
    } else {
      this->selected_neo_index -= 1;
    }
  }
  if (IsKeyPressed(KEY_K)) {
    if (this->selected_neo_index == (int)this->neos.size() - 1) {
      this->selected_neo_index = 0;
    } else {
      this->selected_neo_index += 1;
    }
  }
  // if (IsKeyPressed(KEY_F)) {
  //   std::cout << "Try Deleting" << '\n';
  //   DeleteAllNeos();
  // }
}

void Engine::drawSelection() {
  Vector3 selected_neo_position =
      this->neos.at(this->selected_neo_index)->GetNeoPosition();

  Vector3 arrow_position =
      (Vector3){selected_neo_position.x, selected_neo_position.y + 10,
                selected_neo_position.z};
  Vector3 arrow_bottom =
      (Vector3){arrow_position.x, arrow_position.y - 3, arrow_position.z};

  DrawCylinderEx(arrow_bottom, arrow_position, 0.0f, 2.0, 100, RED);
}
