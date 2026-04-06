#pragma once

#include <cstdint>
#include <memory>
#include <raylib.h>
#include <vector>

#include "../Neos/neo.hpp"

class Engine {
public:
  Engine(std::string model_path);
  ~Engine();

  void PullNeows();
  void Run();

private:
  void updateNeoPosition(double time, float start_time, double angle_radians);
  void lineSpacing(std::vector<double> &angles, double start, double end);
  void update();
  void draw();
  void drawSelection();
  void addNeo();
  void changeSelectedNeo();
  void deleteSelectedNeo();
  void deleteAllNeos();
  void drawNeos();

  Camera3D camera;
  std::vector<std::unique_ptr<neows::Neo>> neos;
  std::string base_url = "https://api.nasa.gov/neo/rest/v1";
  int32_t selected_neo_index = 0;
  Model asteroid_model;
};
