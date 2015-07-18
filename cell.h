#ifndef __CELL_H__
#define __CELL_H__

class Cell {
  char state; //can be any type of block (j, l, s, z, o, t, i) or blank ( )

 public:
  Cell();
  char getState();
  void setState(char newState);
};

#endif
