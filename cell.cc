#include "cell.h"

using namespace std;

Cell::Cell(){
  state = ' ';
}

char Cell::getState(){
  return state;
}

void Cell::setState(char newState){
  state = newState;
}
