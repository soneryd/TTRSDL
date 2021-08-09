#include "../include/Tetris.h"
#include <iostream>
Tetris::Tetris(dimensions dim) {
  gameover = false;
  clearedLines = speed = 0;
  tetromino = new Tetromino();
  nextTetromino = new Tetromino();
  this->dim = dim;
  for (int i = 0; i < dim.height-2; i++) {
    std::vector<int> tmpV;
    board.push_back(tmpV);
    for (int j = 0; j < dim.width-2; j++) {
      board[i].push_back(0);
    }
  }
}

int Tetris::valAtPos(position pos) {
  if(pos.y < board.size() && pos.x < board[pos.y].size() &&
     pos.y >= 0 && pos.x >= 0) {
    return board[pos.y][pos.x];
  } else {
    return 0;
  }
}

bool Tetris::validPos() {
  for (auto e : tetromino->getPositions()) {
    if (e.x < 0 || e.x > dim.width - 3 || e.y > dim.height - 3) {
      return false;
    }
    if (board[e.y][e.x] > 0) {
      return false;
    }
  }
  return true;
}

void Tetris::finalPos() {
  for (auto e : tetromino->getPositions()) {
    board[e.y][e.x] = tetromino->getType()+1;
  }

  std::vector<int> itemsToRemove;
  for (int y = 0; y < board.size(); y++) {
    bool fullLine = true;
    for (int x = 0; x < board[y].size(); x++) {
      if (board[y][x] == 0) {
        fullLine = false;
        x = board.size();
      }
    }
    if (fullLine) {
      itemsToRemove.push_back(y);
    }
  }

  clearedLines += itemsToRemove.size();
  if ((clearedLines+1) % 6 == 0) {
    std::cout << "SPEED:" << speed << std::endl;
    speed++;
  }
  // Flip vector so that we always remove higher higher val first
  std::reverse(itemsToRemove.begin(), itemsToRemove.end());
  
  for (auto e : itemsToRemove) {
    board.erase(board.begin()+e);
  }

  for (int i = 0; i < itemsToRemove.size(); i++) {
    std::vector<int> tmp(dim.width-2);
    board.insert(board.begin(), tmp);
  }

  resetTetromino();
}

bool Tetris::getGameover() {
  return gameover;
}

int Tetris::getSpeed() {
  return speed;
}

void Tetris::resetTetromino() {
  //tetromino = new Tetromino();
  tetromino = nextTetromino;
  nextTetromino = new Tetromino();
  if (!validPos()) {
    gameover = true;
  }
}

Tetromino* Tetris::getTetromino() {
  return tetromino;
}

Tetromino* Tetris::getNextTetromino() {
  return nextTetromino;
}
