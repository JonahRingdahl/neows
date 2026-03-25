#include "engine.hpp"
#include "../Neos/neo.hpp"

#include <cstddef>
#include <memory>
#include <raylib.h>

Engine::Engine() {
  this->camera = {0};
  this->camera.position = {0.0f, 10.0f, 10.0f};
  this->camera.target = {0.0f, 0.0f, 0.0f};
  this->camera.up = {0.0f, 1.0f, 0.0f};
  this->camera.fovy = 45.0f;
  this->camera.projection = CAMERA_PERSPECTIVE;

  for (int i = 0; i < 10; i++) {
    this->neos.emplace_back(std::make_unique<neows::Neo>());
  }
}
Engine::~Engine() {}

void UpdateNeoPosition() {}

void Update() {}

void Draw() {
  BeginDrawing();

  EndDrawing();
}

void Engine::Run() {
  while (!WindowShouldClose()) {
    Update();
    Draw();
  }
}
