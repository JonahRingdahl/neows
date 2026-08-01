#pragma once
#include "Neo.hpp"
#include <ctime>
#include <memory>
#include <raylib.h>
#include <vector>

class NeosCurrier {
public:
  NeosCurrier(Model *asteroidModel);

  auto SetLink(nlohmann::json &link_json) -> void;
  auto SetPages(nlohmann::json &pages_json) -> void;

  auto GetSelectedNeo() -> std::unique_ptr<Neo> &;

  auto AddNeo(std::unique_ptr<Neo> neo) -> void;

  auto DeleteAllNeos() -> void;
  auto DeleteSelectedNeo() -> void;

  auto DrawNeos() -> void;
  auto DrawSelectedNeoPointer() -> void;

  auto UpdateNeosPosition(double time, float startTime, double angleRadians)
      -> void;

  auto ChangeFocusAsteroid() -> void;

private:
  auto CalculateLineSpace(double start, double end, int num)
      -> std::vector<double>;

  std::string links;
  std::string pages;
  std::tuple<std::time_t, std::time_t> timespan;
  std::vector<std::unique_ptr<Neo>> neos;
  bool offline;
  int radius = 15;
  int number_elements;
  int number_pages;
  int render_index = 0;

  Model *asteroidModel;
};
