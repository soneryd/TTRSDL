
#include <SDL2/SDL.h>
#include <iostream>
#include "../include/Renderer.h"

int main() {
  SDL_Window* w = NULL;
  SDL_Renderer* r = NULL;
  Renderer renderer(w, r);
  renderer.loop();
  return 0;
}
