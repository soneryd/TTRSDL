#pragma once

#include <vector>
#include "time.h"
#include "stdlib.h"

enum tetromino_type {
  TT_I, TT_J, TT_L, TT_Z, TT_S, TT_E, TT_O
};

struct position {
  int x;
  int y;
};

class Tetromino {
 private:
  int type;
  int orientation;
  std::vector<std::vector<int>> blocks;
  position pos;
  std::vector<std::vector<int>> makeBlocks();
  
 public:
  Tetromino();
  void mvOrientation(bool inc);
  void mvPosX(bool inc);  
  void mvPosY(bool inc);
  int getType();
  std::vector<position> getPositions();
};
