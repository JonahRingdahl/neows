#include "Menu.hpp"
#include "../Neo/Neo.hpp"

#include <iostream>
#include <memory>
#include <raylib.h>
#include <string>
#include <vector>

Menu::Menu(Vector2 windowSize) {
  std::cout << "Menu Created" << '\n';
  this->apiInputBox = (Rectangle){500, 500, 30, 30};
  this->windowSize = windowSize;
}

Menu::~Menu() {}

std::string Menu::GetTextBuffer() { return this->textInputBoxBuffer; }

// go through all parts of the menu
void Menu::DisplayMenu(const Neo &currentNeo) {
  if (IsKeyDown(KeyboardKey::KEY_F)) {
    this->state = this->state ? MenuState::FULL : MenuState::MINIMAL;
  }

  if (this->state) {
    this->DisplayMinimalMenu(currentNeo);
  } else {
    this->DisplayFullMenu(currentNeo);
  }
}

const void Menu::DisplayMinimalMenu(const Neo &n) {
  if (!n.GetDiameter()) {
    return;
  }

  std::string kilo_max;
  try {
    kilo_max = std::to_string(std::get<1>(n.GetDiameter()->kilometer_min_max));
  } catch (...) {
    kilo_max = "Error";
  }

  std::string meter_max;
  try {
    meter_max = std::to_string(std::get<1>(n.GetDiameter()->meter_min_max));
  } catch (...) {
    meter_max = "Error";
  }
  std::string miles_max;

  try {
    miles_max = std::to_string(std::get<1>(n.GetDiameter()->miles_min_max));
  } catch (...) {
    miles_max = "Error";
  }

  std::string feet_max;
  try {
    feet_max = std::to_string(std::get<1>(n.GetDiameter()->feet_min_max));
  } catch (...) {
    feet_max = "Error";
  }
  std::string id;
  try {
    id = std::to_string(n.GetID());
  } catch (...) {
    id = "Error";
  }

  std::string ref_id;
  try {
    ref_id = n.GetNeoID();
  } catch (...) {
    ref_id = "Error";
  }

  std::string ids = "Neo Id: " + id + " Ref Id: " + ref_id;
  std::string size = "Size (KM) " + kilo_max + " Size (M): " + meter_max;
  std::string altSize = "Size (Mi) " + miles_max + " Size (ft): " + feet_max;
  // std::string approach = "Approach Distance (KM) " + n->

  DrawRectangle(10, 10, 320, 93, Fade(SKYBLUE, 0.5f));
  DrawRectangleLines(10, 10, 320, 93, BLUE);

  DrawText("Asteroid Info", 20, 20, 10, BLACK);
  DrawText(ids.c_str(), 40, 40, 10, WHITE);
  DrawText(size.c_str(), 40, 60, 10, WHITE);
}

void Menu::DisplayFullMenu(const Neo &neo) {
  std::string kilo_max =
      std::to_string(std::get<1>(neo.GetDiameter()->kilometer_min_max));
  std::string meter_max =
      std::to_string(std::get<1>(neo.GetDiameter()->meter_min_max));
  std::string miles_max =
      std::to_string(std::get<1>(neo.GetDiameter()->miles_min_max));
  std::string feet_max =
      std::to_string(std::get<1>(neo.GetDiameter()->feet_min_max));

  std::string neo_name = neo.GetName();

  std::string neo_hazard = std::to_string(neo.GetHazardous());

  std::vector<std::unique_ptr<CloseApproach>> &neo_approach =
      neo.GetCloseApproach();

  std::string id = std::to_string(neo.GetID());
  std::string ref_id = neo.GetNeoID();
  std::string ids = "Neo Id: " + id + " Ref Id: " + ref_id;
  std::string name = "Name: " + neo_name;

  std::string hazardous = "Hazardous: " + neo_hazard;
  std::string size = "Size (KM) " + kilo_max + " Size (M): " + meter_max;
  std::string altSize = "Size (Mi) " + miles_max + " Size (ft): " + feet_max;

  std::string kps = "First Approach KPH: " + neo_approach[0]->relative_vel_kph +
                    " KPS: " + neo_approach[0]->relative_vel_kps;
  std::string mps = "First Approach MPH: " + neo_approach[0]->relative_vel_mph;
  std::string miss_miles =
      "First Approach Miss KM: " + neo_approach[0]->miss_dist_kilometer +
      "Approach Miss Mi: " + neo_approach[0]->miss_dist_miles;

  DrawRectangle(10, 10, 320, 210, Fade(SKYBLUE, 0.5f));
  DrawRectangleLines(10, 10, 320, 210, BLUE);

  DrawText("Asteroid Info", 20, 20, 10, BLACK);
  DrawText(ids.c_str(), 40, 40, 10, WHITE);
  DrawText(name.c_str(), 40, 60, 10, WHITE);
  DrawText(size.c_str(), 40, 80, 10, WHITE);
  DrawText(altSize.c_str(), 40, 100, 10, WHITE);
  DrawText(kps.c_str(), 40, 140, 10, WHITE);
  DrawText(mps.c_str(), 40, 160, 10, WHITE);
  DrawText(miss_miles.c_str(), 40, 180, 10, WHITE);
}

void Menu::ClickIntoApiTextBox(Vector2 mousePos) {
  // Change color of menu if mouse hover
  if (CheckCollisionPointRec(mousePos, this->apiInputBox)) {
    return;
  }
}

void Menu::ApiButton(Vector2 mousePos) {
  // Button not clicked
  if (!IsKeyDown(MOUSE_BUTTON_LEFT) &&
      CheckCollisionPointRec(mousePos, this->apiInputBox))
    return;
}
