#include <iostream>
#include "board.h"
#include "cell.h"

using namespace std;

Board::Board(int l){
  score = 0;
  level = l;
  highScore = 0;
}

void Board::Restart(){
  score = 0;
  for (int i = 0; i < 15; i++){ //Loops through rows
    for (int j = 0; j < 10; j++){  //Loops through columns
      theBoard[i][j].setState(' ');
    }
  }
}

void Board::Output(){
  cout << "Level:       " << level << endl;
  cout << "Score:       " << score << endl;
  cout << "Hi Score:    " << highScore << endl;
  cout << "----------" << endl;
  for (int i = 0; i < 15; i++){
    for (int j = 0; j < 10; j++){
      cout << theBoard[i][j].getState();
    }
    cout << endl;
  }
  cout << "----------" << endl;
  cout << "Next:" << endl;
}

void Board::ChangeCell(int r, int c, char state){
  theBoard[r][c].setState(state);
}

void Board::SetLevel(int l){
  level = l;
}

void Board::CheckLines(){
  bool lineFull = 1;
  int points = 0;
  int linesCleared = 0;

  for (int i = 0; i < 15; i++){
    for (int j = 0; j < 10; j++){
      if (theBoard[i][j].getState() == ' '){
        lineFull = 0;
      }
    }
    if (lineFull == 1){
      linesCleared += 1;
      for (int r = i; r > 0; r--){
        for (int c = 0; c < 10; c++){
          theBoard[r][c].setState(theBoard[r-1][c].getState());
        }
      }
      for (int c = 0; c < 10; c++){
        theBoard[0][c].setState(' ');
      }
    }
    lineFull = 1;
  }

  points = (level + linesCleared) * (level + linesCleared);
  if (linesCleared > 0){
    score += points;
  }
  if (score > highScore){
    highScore = score;
  }
}
