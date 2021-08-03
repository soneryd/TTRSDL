#pragma once

#include <SDL2/SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

class Renderer {
 private:
  SDL_Window* window;
  SDL_Renderer* renderer;

 public:
  Renderer(SDL_Window* window, SDL_Renderer* renderer);
  ~Renderer();

  bool init();

};
