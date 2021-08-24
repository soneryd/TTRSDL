#include "../include/Renderer.h"

Renderer::Renderer(SDL_Window* widow, SDL_Renderer* renderer) {
  waitCount = 0;
  this->window = window;
  this->renderer = renderer;
  this->tetris = new Tetris();
  init();
}

Renderer::~Renderer() {
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
}

void Renderer::loop() {
  bool quit = false;
  bool paused = false;
  SDL_Event e;
  while (!quit) {
    while (tetris->getGameover()) {
      while(SDL_PollEvent(&e) != 0)
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_n) {
          tetris = new Tetris();
        }
    }
    while (SDL_PollEvent(&e) != 0) {
      // Input
      if (e.type == SDL_QUIT) {
        quit = true;
      } else if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {

	case SDLK_UP:
	  tetris->getTetromino()->mvOrientation(true);
          if (!tetris->validPos()) {
            tetris->getTetromino()->mvOrientation(false);
          }
          break;

	case SDLK_LEFT:
	  tetris->getTetromino()->mvPosX(false);
	  if(!tetris->validPos())
	    tetris->getTetromino()->mvPosX(true);
	  break;

	case SDLK_RIGHT:
	  tetris->getTetromino()->mvPosX(true);
	  if(!tetris->validPos())
	    tetris->getTetromino()->mvPosX(false);	  
	  break;

	case SDLK_DOWN:
	  tetris->getTetromino()->mvPosY(true);	  
          if (!tetris->validPos()) {
            tetris->getTetromino()->mvPosY(false);
	    tetris->finalPos();
          }
          break;

	case SDLK_SPACE:
          while (tetris->validPos()) {
            tetris->getTetromino()->mvPosY(true);
          }
          tetris->getTetromino()->mvPosY(false);
          tetris->finalPos();
          break;

	case SDLK_p:
	  paused = true;
          while (paused) {
	    while(SDL_PollEvent(&e) != 0)
	      if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_p) {
		paused = false;
	      } 
          }
	  break;
        }
      }
    }

    // Sleep
    SDL_Delay(10);
    waitCount++;
    if (waitCount >= 50-tetris->getSpeed()) {
      tetris->getTetromino()->mvPosY(true);
      if (!tetris->validPos()) {
        tetris->getTetromino()->mvPosY(false);
        tetris->finalPos();
      }
      waitCount = 0;
    }

    // Render
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    drawBoard();
    SDL_RenderPresent(renderer);
  }
}

bool Renderer::init() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
    return false;
  }

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
  window = SDL_CreateWindow("TTRSDL", 
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

void Renderer::drawBoard() {
  SDL_RenderClear(renderer);
  /* Draw board */
  int height = SCREEN_HEIGHT - 100;
  int boxDim = height/tetris->getDims().height;  
  for (int py = 0; py < tetris->getDims().height; py++) {
    for (int px = 0; px < tetris->getDims().width; px++) {
      int boardVal = tetris->valAtPos({px-1, py-1});
      if (py == 0 || py == tetris->getDims().height - 1 || px == 0 ||
          px == tetris->getDims().width - 1 || boardVal > 0)
        drawSquare(50 + (px * boxDim), 50 + (py * boxDim), boxDim,
		   getColor(boardVal));
    }
  }

  for (auto e : tetris->getTetromino()->getPositions()) {
    drawSquare(50+((1+e.x)*boxDim), 50+((1+e.y)*boxDim), boxDim,
	       getColor(tetris->getTetromino()->getType()+1));
  }

  drawNext(SCREEN_WIDTH-150, 50, boxDim);
}

void Renderer::drawNext(int x, int y, int boxDim) {
  for (int py = 0; py < 6; py++) {
    for (int px = 0; px < 6; px++) {
      if (py == 0 || py == 5 || px == 0 || px == 5) {
        drawSquare(x + (px * boxDim), y + (py * boxDim), boxDim, getColor(0));
      }
    }
  }

  for (auto e : tetris->getNextTetromino()->getPositions()) {
    drawSquare(x-(boxDim*2)+((e.x)*boxDim), y+((1+e.y)*boxDim), boxDim,
	       getColor(tetris->getNextTetromino()->getType()+1));
  }
}

void Renderer::drawSquare(int x, int y, int d, SDL_Color color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_Rect box = { x, y, d, d};
  SDL_RenderFillRect(renderer, &box);

  SDL_SetRenderDrawColor(renderer, color.r-20, color.g-20, color.b-20,
			 color.a);  
  SDL_Rect box2 = {x+(d/5), y+(d/5), d-(d/5), d-(d/5)};
  SDL_RenderFillRect(renderer, &box2);  
  
  SDL_SetRenderDrawColor(renderer, color.r-10, color.g-10, color.b-10,
			 color.a);  
  SDL_Rect box3 = {x+(d/5), y+(d/5), d-(d/5)*2, d-(d/5)*2};
  SDL_RenderFillRect(renderer, &box3);  
}

SDL_Color Renderer::getColor(int type) {
  type--;
  if(type==TT_I) {
    return {100, 200, 200, 0};
  } else if (type == TT_J) {
    return {100, 100, 200, 0};    
  } else if (type == TT_L) {
    return {100, 200, 100, 0};    
  } else if (type == TT_Z) {
    return {200, 100, 100, 0};    
  } else if (type == TT_S) {
    return {200, 100, 200, 0};    
  } else if (type == TT_E) {
    return {200, 200, 100, 0};    
  } else if (type == TT_O) {
    return {100, 200, 200, 0};
  } else {
    return {80, 80, 80, 0};
  }
}
