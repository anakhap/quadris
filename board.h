#ifndef __BOARD_H__
#define __BOARD_H__

#include "cell.h"

class Board {
  int level;
  int score;
  int highScore;

 public:
  Cell theBoard[15][10];
  Board(int l);
  void Restart();
  void ChangeCell(int r, int c, char state);
  void SetLevel(int l);
  void Output();
  void CheckLines();
};

#endif
