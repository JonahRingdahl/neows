#pragma once

#include <cstdint>
#include <memory>
#include <raylib.h>
#include <vector>

#include "../Neos/neo.hpp"

class Engine {
public:
  Engine();
  ~Engine();

  void PullNeows();
  void Run();

private:
  void UpdateNeoPosition(double time, float startTime, double angleRadians);
  void LineSpacing(std::vector<double> &angles, double start, double end);
  void Update();
  void Draw();
  void DrawSelection();
  void AddNeo();
  void ChangeSelectedNeo();
  void DeleteSelectedNeo();

  Camera3D camera;
  std::vector<std::unique_ptr<neows::Neo>> neos;
  std::string base_url = "https://api.nasa.gov/neo/rest/v1";
  int32_t selected_neo_index = 0;
};
