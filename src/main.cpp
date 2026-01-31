#include "Menu/Menu.hpp"
#include "Neo/NeosCurrier.hpp"

#include <fstream>
#include <iostream>
#include <memory>
#include <raylib.h>

#include <httplib.h>
#include <nlohmann/json.hpp>
#include <string>

void UpdateGame(Camera3D &camera, NeosCurrier &currier, Menu menu,
                float startTime);
void DrawGame(Camera3D camera, NeosCurrier &currier, Menu menu,
              Vector3 earthPosition);
void get_api_keys(std::string &k, std::string &v);

int main(void) {
  std::string base_url("https://api.nasa.gov");
  std::string path(
      "/neo/rest/v1/feed?start_date=2015-09-07&end_date=2015-09-08&api_key=");

  std::string key;
  std::string value;

  Vector2 screenDim = (Vector2){1280, 720};

  Menu menu = Menu(screenDim);

  get_api_keys(key, value);

  InitWindow(screenDim.x, screenDim.y, "NEOws Display");

  Camera3D camera = {0};
  camera.position = (Vector3){20.0f, 20.0f, 20.0f}; // Camera position
  camera.target = (Vector3){0.0f, 0.0f, 0.0f};      // Camera looking at point
  camera.up =
      (Vector3){0.0f, 1.0f, 0.0f}; // Camera up vector (rotation towards target)
  camera.fovy = 45.0f;             // Camera field-of-view Y
  camera.projection = CAMERA_PERSPECTIVE;
  Vector3 earthPosition = {0.0, 0.0, 0.0};
  float startTime = GetTime();

  // Some bug with loading the asteroid
  Model asteroidModel = LoadModel("assets/Asteroid.glb");

  if (asteroidModel.meshCount == 0) {
    std::cerr << "Failed to load asteroid model!" << std::endl;
    return -1;
  }

  std::cout << "load neos" << "\n";
  NeosCurrier currier(&asteroidModel);

#ifdef DEBUG
  path += "DEMO_KEY";
#endif // DEBUG
  path += value;

  // Hanging loading of program
  // currier->ReachAPI(base_url, path);

  DisableCursor();

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    UpdateGame(camera, currier, menu, startTime);
    DrawGame(camera, currier, menu, earthPosition);
  }

  CloseWindow();
  // UnloadModel(earthModel);
  UnloadModel(asteroidModel);
  return 0;
}

void UpdateGame(Camera3D &camera, NeosCurrier &currier, Menu menu,
                float startTime) {
  // Update Cycle
  UpdateCamera(&camera, CAMERA_FREE);
  currier.UpdateNeosPosition(GetTime(), startTime, 0.5);
  currier.ChangeFocusAsteroid();
}

void DrawGame(Camera3D camera, NeosCurrier &currier, Menu menu,
              Vector3 earthPosition) {
  // Draw Cycle
  BeginDrawing();
  ClearBackground(BLACK);

  BeginMode3D(camera);

  DrawSphere(earthPosition, 5, GREEN);
  currier.DrawNeos();
  currier.DrawSelectedNeoPointer();

  /*
  DrawLine3D((Vector3){0, 0, 0}, (Vector3){20, 0, 0}, RED);
  DrawLine3D((Vector3){0, 0, 0}, (Vector3){0, 20, 0}, GREEN);
  DrawLine3D((Vector3){0, 0, 0}, (Vector3){0, 0, 20}, BLUE);

  DrawGrid(20, 1.0f);

  */

  EndMode3D();

  // Insert Menu Draw
  if (currier.IsEmpty()) {
    EndDrawing();
    return;
  }

  if (currier.GetSelectedNeo().has_value()) {
    menu.DisplayMenu(currier.GetSelectedNeo().value());
  }

  EndDrawing();
}

void get_api_keys(std::string &k, std::string &v) {
  std::string outputstr;
  std::ifstream env_file(".env");
  if (env_file.is_open()) {
    env_file >> outputstr;
  }

  std::string delimiter = "=";
  k = outputstr.substr(0, outputstr.find(delimiter));
  v = outputstr.substr(outputstr.find(delimiter) + 1, outputstr.length());
}
