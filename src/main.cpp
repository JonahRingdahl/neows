#include "Engine/engine.hpp"
#include <raylib.h>

int main(void) {
  Model model = LoadModel("../assets/Asteroid.glb");
  Engine engine(model);
  UnloadModel(model);

  return 0;
}
