#pragma once

#include "../Neo/Neo.hpp"

#include <memory>
#include <raylib.h>
#include <string>

#include "clay.h"

enum MenuState { Minimal = 0, Full = 1 };

class Menu {
private:
  Rectangle apiInputBox;
  std::string textInputBoxBuffer;
  Vector2 windowSize;
  MenuState state;
  Clay_Arena clayMemory;
  Font font;

public:
  Menu(const Menu &) = default;
  Menu(Menu &&) = delete;
  Menu &operator=(const Menu &) = default;
  Menu &operator=(Menu &&) = delete;
  Menu(Vector2 windowSize);
  ~Menu();

  std::string GetTextBuffer();

  void DisplayMinimalMenu(const std::unique_ptr<Neo>& currentNeo);
  void DisplayFullMenu(std::unique_ptr<Neo>& currentNeo);

  void DisplayMenu(std::unique_ptr<Neo>& currentNeo);
  void DisplayAsteroidInfo(const std::unique_ptr<Neo>& currentNeo);
  void ClickIntoApiTextBox(Vector2 mousePos);
  void ApiButton(Vector2 mousePos);
};
