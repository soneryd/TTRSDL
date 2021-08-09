#pragma once

#include <algorithm>
#include "Tetromino.h"

struct dimensions {
  int width;
  int height;
};

class Tetris {
 private:
  Tetromino* tetromino;
  Tetromino* nextTetromino;
  dimensions dim;  
  std::vector<std::vector<int>> board;
  bool gameover;
  int clearedLines;
  int speed;
 public:
  Tetris(dimensions dim = {12, 22});
  dimensions getDims() { return dim; }
  bool getGameover();
  int getSpeed();
  int valAtPos(position pos);
  bool validPos();
  void finalPos();
  void resetTetromino();
  Tetromino* getTetromino();
  Tetromino* getNextTetromino();
};
