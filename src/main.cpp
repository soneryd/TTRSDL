#include <SDL2/SDL.h>
#include <iostream>
#include "../include/Renderer.h"

int main() {
  SDL_Window* window = NULL;
  SDL_Renderer* renderer = NULL;  
  Renderer renderer(window, renderer);
  return 0;
}
