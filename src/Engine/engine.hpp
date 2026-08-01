#pragma once

#include <raylib.h>
#include <string>

#include "../Menu/Menu.hpp"
#include "../Neo/NeosCurrier.hpp"

class Engine {
public:
  Engine();
  ~Engine();
  auto Run() -> void;

private:
  auto Update(float update_start_time) -> void;
  auto Draw() -> void;
  auto GetAPIKeys() -> void;

  std::string base_url = "http://api.nasa.gov";
  std::string path =
      "/neo/rest/v1/feed?start_date=2015-09-07&end_date=2015-09-08&api_key=";
  std::string key;
  std::string value;

  Camera3D camera = (Camera3D){0};
  const Vector2 default_screen_dimentions = (Vector2){1280, 720};

  const Vector3 earth_position = (Vector3){0, 0, 0};
  const double start_time = GetTime();
  Model asteroid_model;
  NeosCurrier currier;
  Menu menu;
};
