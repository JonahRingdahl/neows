#pragma once
#include "Neo.hpp"
#include <ctime>
#include <memory>
#include <raylib.h>
#include <vector>

class NeosCurrier {
public:
  NeosCurrier(Model *asteroidModel);

  void SetLink(nlohmann::json &link_json);
  void SetPages(nlohmann::json &pages_json);

  std::vector<std::unique_ptr<Neo>> GetNeoCollection();
  std::optional<Neo &> GetSelectedNeo();

  bool IsEmpty() { return this->neos.empty(); }

  void AddNeo(std::unique_ptr<Neo> neo);

  void DeleteAllNeos();
  void DeleteSelectedNeo();

  void DrawNeos();
  void DrawSelectedNeoPointer();

  void UpdateNeosPosition(double time, float startTime, double angleRadians);
  std::vector<double> CalculateLineSpace(double start, double end, int num);

  void ChangeFocusAsteroid();

private:
  std::string links;
  std::string pages;
  std::tuple<std::time_t, std::time_t> timespan;
  std::vector<std::unique_ptr<Neo>> neos;
  bool offline;
  int radius = 15;
  int number_elements;
  int number_pages;
  int render_index = 0;

  std::unique_ptr<Model> asteroidModel;
};
