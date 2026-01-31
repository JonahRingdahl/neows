#pragma once

#include <memory>
#include <string>

#include <raylib.h>

#include "../Neo/Neo.hpp"

enum MenuState { MINIMAL = 0, FULL = 1 };

class Menu {
private:
  Rectangle apiInputBox;
  std::string textInputBoxBuffer;
  Vector2 windowSize;
  MenuState state;

public:
  Menu(const Menu &) = default;
  Menu(Menu &&) = delete;
  Menu &operator=(const Menu &) = default;
  Menu &operator=(Menu &&) = delete;
  Menu(Vector2 windowSize);
  ~Menu();

  std::string GetTextBuffer();

  const void DisplayMinimalMenu(const Neo &currentNeo);
  void DisplayFullMenu(const Neo &currentNeo);

  void DisplayMenu(const Neo &currentNeo);
  const void DisplayAsteroidInfo(Neo &currentNeo);
  void ClickIntoApiTextBox(Vector2 mousePos);
  void ApiButton(Vector2 mousePos);
};
