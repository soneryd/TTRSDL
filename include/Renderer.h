#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include "../include/Tetris.h"

const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 600;

class Renderer {
 private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  Tetris* tetris;
  int waitCount;
  
 public:
  Renderer(SDL_Window* window, SDL_Renderer* renderer);
  ~Renderer();
  bool init();
  void loop();
  void drawBoard();
  void drawNext(int x, int y, int boxDim);
  void drawSquare(int x, int y, int d, SDL_Color color);
  SDL_Color getColor(int type);
};
