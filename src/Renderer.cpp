#include "../include/Renderer.h"

Renderer::Renderer(SDL_Window* widow, SDL_Renderer* renderer) {
  
}

Renderer::~Renderer() {

}

bool Renderer::init() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
    return false;
  }

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
  window = SDL_CreateWindow("Sudoku", 
			    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			    SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
    return false;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    std::cout << "Failed to create renderer: " << SDL_GetError() << std::endl;
    return false;
  }
  
  return true;
}
