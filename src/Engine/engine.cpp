#include "engine.hpp"
#include <raylib.h>
#include <string>
#include <print>
#include <fstream>

#include "../Neo/NeosCurrier.hpp"
#include "../Menu/Menu.hpp"

void Engine::GetAPIKeys() {
    std::string outputstr;
    std::ifstream env_file(".env");
    if (env_file.is_open()) {
    env_file >> outputstr;
    }

    std::string delimiter = "=";
    this->key = outputstr.substr(0, outputstr.find(delimiter));
    this->value = outputstr.substr(outputstr.find(delimiter) + 1, outputstr.length());
}
void Engine::Update(float update_start_time) {
    // Update Cycle
      UpdateCamera(&camera, CAMERA_FREE);
      currier.UpdateNeosPosition(GetTime(), this->start_time, 0.5);
      currier.ChangeFocusAsteroid();
}

void DrawGridLines() {
    DrawLine3D((Vector3){0, 0, 0}, (Vector3){20, 0, 0}, RED);
    DrawLine3D((Vector3){0, 0, 0}, (Vector3){0, 20, 0}, GREEN);
    DrawLine3D((Vector3){0, 0, 0}, (Vector3){0, 0, 20}, BLUE);
    DrawGrid(20, 1.0f);
}


void Engine::Draw() {
    BeginDrawing();
      ClearBackground(BLACK);

      BeginMode3D(this->camera);

      DrawSphere(this->earth_position, 5, GREEN);
      this->currier.DrawNeos();
      this->currier.DrawSelectedNeoPointer();

      // DrawGridLines();

      EndMode3D();

      // Insert Menu Draw
      this->menu.DisplayMenu(currier.GetSelectedNeo());

      EndDrawing();
}

//Public Methods

Engine::Engine() {

    GetAPIKeys();
    InitWindow(this->default_screen_dimentions.x, this->default_screen_dimentions.y, "Neows Display");
    this->camera.position = (Vector3) { 20, 20, 20 };
    this->camera.target = (Vector3) { 0, 0, 0 };
    this->camera.up = (Vector3) { 0, 1, 0 };
    this->camera.fovy = 45;
    this->camera.projection = CAMERA_PERSPECTIVE;

    this->asteroid_model = LoadModel("assets/Asteroid.glb");

    std::println("Loading Neos");

    std::string demo("DEMO_KEY");

    DisableCursor();
    SetTargetFPS(60);
}

Engine::~Engine() {
    CloseWindow();
    UnloadModel(this->asteroid_model);
}

void Engine::Run() {
    while (!WindowShouldClose()) {
        Update(GetFrameTime());
        Run();
    }
}
