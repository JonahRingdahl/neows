#pragma once

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
  Camera3D camera;
  std::vector<std::unique_ptr<neows::Neo>> neos;
  std::string base_url = "https://api.nasa.gov/neo/rest/v1";
};
