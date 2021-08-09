#include "../include/Tetromino.h"
#include <iostream>

Tetromino::Tetromino() {
  type = rand()%7;
  blocks = makeBlocks();
  orientation = 0;
  pos.x = 3;
  pos.y = 0;
}

void Tetromino::mvPosX(bool inc) {
  inc ? pos.x++ : pos.x--;
}

void Tetromino::mvPosY(bool inc) {
  inc ? pos.y++ : pos.y--;
}

void Tetromino::mvOrientation(bool inc) {
  int rotations = 0;
  if (type == TT_I || type == TT_Z || type == TT_S) {
    rotations = 2;
  } else if (type == TT_L || type || TT_J || type == TT_E) {
    rotations = 4;
  }
  inc ? orientation = (orientation+1)%rotations
    : orientation = (orientation+3)%rotations;
}

int Tetromino::getType() {
  return type;
}

std::vector<position> Tetromino::getPositions() {
  std::vector<position> positions;
  for (int y = 0; y < blocks.size(); y++) {
    for (int x = 0; x < blocks[y].size(); x++) {
      if(orientation==0) {
	if (blocks[y][x] == 1) {
	  position blockPos = {x + pos.x, y + pos.y};
	  positions.push_back(blockPos);
	}
      } else if (orientation == 1) {
        if (blocks[blocks.size() - 1 - x][y] == 1) {
          position blockPos = {x + pos.x, y + pos.y};
          positions.push_back(blockPos);	  
        }
      } else if (orientation == 2) {
        if (blocks[blocks.size()-1-y][blocks.size()-1-x] == 1) {
          position blockPos = {x + pos.x, y + pos.y};
          positions.push_back(blockPos);
        }
      } else if (orientation == 3) {
        if (blocks[x][blocks.size()-1-y] == 1) {
          position blockPos = {x + pos.x, y + pos.y};
          positions.push_back(blockPos);
        }
      }
    }
  }
  return positions;
}

std::vector<std::vector<int>> Tetromino::makeBlocks() {
  std::vector<std::vector<int>> tmpBlocks;  
  if(type==TT_I) {
    std::vector<int> r1 = {0,0,1,0};
    std::vector<int> r2 = {0,0,1,0};
    std::vector<int> r3 = {0,0,1,0};
    std::vector<int> r4 = {0,0,1,0};
    tmpBlocks.push_back(r1);
    tmpBlocks.push_back(r2);
    tmpBlocks.push_back(r3);
    tmpBlocks.push_back(r4);
  } else if (type == TT_J) {
    std::vector<int> r1 = {0,1,1};
    std::vector<int> r2 = {0,1,0};
    std::vector<int> r3 = {0,1,0};
    tmpBlocks.push_back(r1);
    tmpBlocks.push_back(r2);
    tmpBlocks.push_back(r3);    
  } else if (type == TT_L) {
    std::vector<int> r1 = {1,1,0};
    std::vector<int> r2 = {0,1,0};
    std::vector<int> r3 = {0,1,0};
    tmpBlocks.push_back(r1);
    tmpBlocks.push_back(r2);
    tmpBlocks.push_back(r3);    
  } else if (type == TT_Z) {
    std::vector<int> r1 = {1,1,0};
    std::vector<int> r2 = {0,1,1};
    std::vector<int> r3 = {0,0,0};
    tmpBlocks.push_back(r1);
    tmpBlocks.push_back(r2);
    tmpBlocks.push_back(r3);
  } else if (type == TT_S) {
    std::vector<int> r1 = {0,1,1};
    std::vector<int> r2 = {1,1,0};
    std::vector<int> r3 = {0,0,0};
    tmpBlocks.push_back(r1);
    tmpBlocks.push_back(r2);
    tmpBlocks.push_back(r3);
  } else if (type == TT_E) {
    std::vector<int> r1 = {0,1,0};
    std::vector<int> r2 = {0,1,1};
    std::vector<int> r3 = {0,1,0};    
    tmpBlocks.push_back(r1);
    tmpBlocks.push_back(r2);
    tmpBlocks.push_back(r3);    
  } else if (type == TT_O) {
    std::vector<int> r1 = {1,1};
    std::vector<int> r2 = {1,1};
    tmpBlocks.push_back(r1);
    tmpBlocks.push_back(r2);
  }
  
  return tmpBlocks;
}
