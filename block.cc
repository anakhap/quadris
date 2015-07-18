#include <iostream>
#include "block.h"
#include "board.h"

using namespace std;

AbstractBlock::~AbstractBlock(){}

void AbstractBlock::SetShape(Shapes block) {
    static const int coordsTable[8][4][2] = {
        {{0,3}, {0,3}, {0,3}, {0,3}},           //NoShape
        {{0,3}, {0,4}, {1,4}, {2,4}},           //JShape
        {{0,4}, {1,4}, {2,4}, {2,3}},           //LShape
        {{0,4}, {1,4}, {1,3}, {2,3}},           //SShape
        {{0,3}, {0,4}, {1,4}, {1,3}},           //OShape
        {{0,3}, {1,3}, {1,4}, {2,4}},           //ZShape
        {{0,3}, {1,3}, {2,3}, {1,4}},           //TShape
        {{0,3}, {1,3}, {2,3}, {3,3}}            //IShape
    };
    
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 2; j++) {
            coords[i][j] = coordsTable[block][i][j];
        }
    } 
    chosenpiece = block;
}


/* JBLOCK METHODS */

JBlock::JBlock(Board &b) {
  SetShape(Jshape);
  orient = 0;
/*  for(int i = 0; i < 4; i++) {
    b.ChangeCell(coords[i][1], coords[i][0], 'J');
  }*/
}

void JBlock::show(Board &b) {
  for (int i = 0; i < 4; i++){
    if (!(b.theBoard[coords[i][1]][coords[i][0]].getState() == ' ')) {
      cout << "Game over." << endl;
      b.Restart();
      break;
    }
  }

  for (int i = 0; i < 4; i++) {
    b.ChangeCell(coords[i][1], coords[i][0], 'J');
  }
}

void JBlock::counterclockwise(Board &b) {
  for (int i = 0; i < 4; i++){
    b.ChangeCell(coords[i][1], coords[i][0], ' ');
  }
  if (orient == 0){
    coords[0][1] += 1;
    coords[1][0] += 1;
    coords[2][1] -= 1;
    coords[3][0] -= 1;
    coords[3][1] -= 2;
    orient = 3;
  } else if (orient == 1){
    coords[0][0] -= 1;
    coords[0][1] += 1;
    coords[1][1] += 2;
    coords[2][0] += 1;
    coords[2][1] += 1;
    coords[3][0] += 2;
    orient = 0;
  } else if (orient == 2){
    coords[0][0] -= 1;
    coords[0][1] -= 2;
    coords[1][0] -= 2;
    coords[1][1] -= 1;
    coords[2][0] -= 1;
    coords[3][1] += 1;
    orient = 1;
  } else if (orient == 3){
    coords[0][0] += 2;
    coords[1][0] += 1;
    coords[1][1] -= 1;
    coords[3][0] -= 1;
    coords[3][1] += 1;
    orient = 2;
  }
  for (int j = 0; j < 4; j++){
    b.ChangeCell(coords[j][1], coords[j][0], 'J');
  }
}

void JBlock::clockwise(Board &b) {
  for (int i = 0; i < 4; i++){
    b.ChangeCell(coords[i][1], coords[i][0], ' ');
  }
  if (orient == 0){
    coords[0][0] += 1;
    coords[0][1] -= 1;
    coords[1][1] -= 2;
    coords[2][0] -= 1;
    coords[2][1] -= 1;
    coords[3][0] -= 2;
    orient = 1;
  } else if (orient == 1){
    coords[0][0] += 1;
    coords[0][1] += 2;
    coords[1][0] += 2;
    coords[1][1] += 1;
    coords[2][0] += 1;
    coords[3][1] -= 1;
    orient = 2;
  } else if (orient == 2){
    coords[0][0] -= 2;
    coords[1][0] -= 1;
    coords[1][1] += 1;
    coords[3][0] += 1;
    coords[3][1] -= 1;
    orient = 3;
  } else if (orient == 3){
    coords[0][1] -= 1;
    coords[1][0] -= 1;
    coords[2][1] += 1;
    coords[3][0] += 1;
    coords[3][1] += 2;
    orient = 0;
  }
  for (int j = 0; j < 4; j++){
    b.ChangeCell(coords[j][1], coords[j][0], 'J');
  }
}

void JBlock::right(Board &b) {
    bool indicator = 0;
    bool otherIndicator = 0;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if ((coords[i][0] + 1) == (coords[j][0]) && coords[i][1] == coords[j][1]) {
                indicator = 1;
            }
	}
	if(indicator == 0) {        
            if (!(b.theBoard[coords[i][1]][coords[i][0]+1].getState() == ' ')) {
                    otherIndicator = 1;
            }
        }
	indicator = 0;
    }
    for (int e = 0; e < 4; e++){
      if (coords[e][0] == 9){
        otherIndicator = 1;
      }
    }
    if(otherIndicator == 0) {
        for(int i = 0; i < 4; i++) {
            b.ChangeCell(coords[i][1], coords[i][0], ' ');
        }
        for(int i = 0; i < 4; i++) {
            coords[i][0] += 1;
        }
        for(int i = 0; i < 4; i++) {
            b.ChangeCell(coords[i][1], coords[i][0], 'J');
        }
    }    
}

void JBlock::left(Board &b) {
    bool indicator = 0;
    bool otherIndicator = 0;
    
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if ((coords[i][0] - 1) == (coords[j][0]) && coords[i][1] == coords[j][1]) {
                indicator = 1;
            }
	}
	if(indicator == 0) {        
            if (!(b.theBoard[coords[i][1]][(coords[i][0]-1)].getState() == ' ')) {
                    otherIndicator = 1;
            }
        }
	indicator = 0;
    }
    for (int e = 0; e < 4; e++){
      if (coords[e][0] == 0){
        otherIndicator = 1;
      }
    }
    if(otherIndicator == 0) {
        for(int i = 0; i < 4; i++) {
            b.ChangeCell(coords[i][1], coords[i][0], ' ');
        }
        for(int i = 0; i < 4; i++) {
            coords[i][0] -= 1;
        }
        for(int i = 0; i < 4; i++) {
            b.ChangeCell(coords[i][1], coords[i][0], 'J');
        }
    }
}

void JBlock::down(Board &b) {
    bool indicator = 0;
    bool otherIndicator = 0;
    
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if ((coords[i][1] + 1) == (coords[j][1]) && coords[i][0] == coords[j][0]) {
                indicator = 1;
            }
	}
	if(indicator == 0) {
            if ((b.theBoard[(coords[i][1]+1)][coords[i][0]].getState() != ' ')) {
                    otherIndicator = 1;
            }
        }
	if (coords[i][1] == 14){
	  otherIndicator = 1;
	}
	indicator = 0;
    }
    if(otherIndicator == 0) {
        for(int i = 0; i < 4; i++) {
            b.ChangeCell(coords[i][1], coords[i][0], ' ');
        }
        for(int i = 0; i < 4; i++) {
            coords[i][1] += 1;
        }
        for(int i = 0; i < 4; i++) {
            b.ChangeCell(coords[i][1], coords[i][0], 'J');
        }
    }
    
}

void JBlock::drop(Board &b) {
    for (int i = 0; i < 15; i++){
        this->down(b);
    }
}


/* L-BLOCK METHODS */

void LBlock::counterclockwise(Board &b) {
  for(int i = 0; i < 4; i++) {
     b.ChangeCell(coords[i][1], coords[i][0], ' ');
  }
  if(orient == 0) {
    coords[0][0] += 1;
    coords[1][1] -= 1;
    coords[2][0] -= 1;
    coords[2][1] -= 2;
    coords[3][0] -= 2;
    coords[3][1] -= 2;
    orient = 3;
  } else if(orient == 1) {
      coords[0][0] += 1;
      coords[0][1] -= 1;
      coords[2][0] -= 1;
      coords[2][1] += 1;
      coords[3][1] += 2;
      orient = 0;
  } else if(orient == 2) {
      coords[0][0] -= 2;
      coords[0][1] -= 1;
      coords[1][0] -= 1;
      coords[2][1] += 1;
      coords[3][0] += 1;
      orient = 1;
  } else if(orient == 3) {
      coords[0][1] += 2;
      coords[1][0] += 1;
      coords[1][1] += 1;
      coords[2][0] += 2;
      coords[3][0] += 1;
      coords[3][1] -= 1;
      orient = 2;
  }
  for(int j = 0; j < 4; j++) {
      b.ChangeCell(coords[j][1], coords[j][0], 'L');
  }
}

LBlock::LBlock(Board &b) {
  SetShape(Lshape);
  orient = 0;
/*  for(int i = 0; i < 4; i++) {
    b.ChangeCell(coords[i][1], coords[i][0], 'L');
  }*/
}

void LBlock::show(Board &b) {
  for (int i = 0; i < 4; i++) {
    b.ChangeCell(coords[i][1], coords[i][0], 'L');
  }
}

void LBlock::clockwise(Board &b) {
  for(int i = 0; i < 4; i++) {
    b.ChangeCell(coords[i][0], coords[i][1], ' '); 
  }
  if(orient == 0) {
    coords[0][1] -= 2;
    coords[1][0] -= 1;
    coords[1][1] -= 1;
    coords[2][0] -= 2;
    coords[3][0] -= 1;
    coords[3][1] += 1;
    orient = 1;
  } else if(orient == 1) {
      coords[0][0] += 2;
      coords[0][1] += 1;
      coords[1][0] += 1;
      coords[2][1] -= 1;
      coords[3][0] -= 1;
      orient = 2;
  } else if(orient == 2) {
     coords[0][0] += 1;
     coords[0][1] += 1;
     coords[2][0] += 1;
     coords[2][1] -= 1;
     coords[3][1] -= 2;
     orient = 3;
  } else if(orient == 3) {
     coords[0][0] -= 1;
     coords[1][1] += 1;
     coords[2][0] += 1;
     coords[2][1] += 2;
     coords[3][0] += 2;
     coords[3][1] += 1;
     orient = 0;
  }
  for(int j = 0; j < 4; j++) {
    b.ChangeCell(coords[j][1], coords[j][0], 'L');
  }
}

void LBlock::right(Board &b) {
    bool indicator = 0;
    bool otherIndicator = 0;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if ((coords[i][0] + 1) == (coords[j][0]) && coords[i][1] == coords[j][1]) {
                indicator = 1;
            }
	}
	if(indicator == 0) {        
            if (!(b.theBoard[coords[i][1]][coords[i][0]+1].getState() == ' ')) {
                    otherIndicator = 1;
            }
        }
	indicator = 0;
    }
    for (int e = 0; e < 4; e++){
      if (coords[e][0] == 9){
        otherIndicator = 1;
      }
    }
    if(otherIndicator == 0) {
        for(int i = 0; i < 4; i++) {
            b.ChangeCell(coords[i][1], coords[i][0], ' ');
        }
        for(int i = 0; i < 4; i++) {
            coords[i][0] += 1;
        }
        for(int i = 0; i < 4; i++) {
            b.ChangeCell(coords[i][1], coords[i][0], 'L');
        }
    }    
}

void LBlock::left(Board &b) {
    bool indicator = 0;
    bool otherIndicator = 0;
    
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if ((coords[i][0] - 1) == (coords[j][0]) && coords[i][1] == coords[j][1]) {
                indicator = 1;
            }
	}
	if(indicator == 0) {        
            if (!(b.theBoard[coords[i][1]][(coords[i][0]-1)].getState() == ' ')) {
                    otherIndicator = 1;
            }
        }
	indicator = 0;
    }
    for (int e = 0; e < 4; e++){
      if (coords[e][0] == 0){
        otherIndicator = 1;
      }
    }
    if(otherIndicator == 0) {
        for(int i = 0; i < 4; i++) {
            b.ChangeCell(coords[i][1], coords[i][0], ' ');
        }
        for(int i = 0; i < 4; i++) {
            coords[i][0] -= 1;
        }
        for(int i = 0; i < 4; i++) {
            b.ChangeCell(coords[i][1], coords[i][0], 'L');
        }
    }
}

void LBlock::down(Board &b) {
    bool indicator = 0;
    bool otherIndicator = 0;
    
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if ((coords[i][1] + 1) == (coords[j][1]) && coords[i][0] == coords[j][0]) {
                indicator = 1;
            }
	}
	if(indicator == 0) {
            if ((b.theBoard[(coords[i][1]+1)][coords[i][0]].getState() != ' ')) {
                    otherIndicator = 1;
            }
        }
	if (coords[i][1] == 14){
	  otherIndicator = 1;
	}
	indicator = 0;
    }
    if(otherIndicator == 0) {
        for(int i = 0; i < 4; i++) {
            b.ChangeCell(coords[i][1], coords[i][0], ' ');
        }
        for(int i = 0; i < 4; i++) {
            coords[i][1] += 1;
        }
        for(int i = 0; i < 4; i++) {
            b.ChangeCell(coords[i][1], coords[i][0], 'L');
        }
    }
    
}

void LBlock::drop(Board &b) {
    for (int i = 0; i < 15; i++){
        this->down(b);
    }
}

/* S-BLOCK METHODS */

SBlock::SBlock(Board &b) {
  SetShape(Sshape);
  orient = 0;
/*  for(int i = 0; i < 4; i++) {
    b.ChangeCell(coords[i][1], coords[i][0], 'S');
  }*/
}

void SBlock::show(Board &b) {
  for (int i = 0; i < 4; i++) {
    b.ChangeCell(coords[i][1], coords[i][0], 'S');
  }
}

void SBlock::counterclockwise(Board &b) {
   for(int i = 0; i < 4; i++) {
     b.ChangeCell(coords[i][1], coords[i][0], ' ');
   }
   if(orient == 0) {
     coords[0][0] += 1;
     coords[1][1] -= 1;
     coords[2][0] -= 1;
     coords[2][0] -= 1;
     coords[3][0] -= 2;
     coords[3][1] -= 1;
     orient = 3;
   } else if(orient == 1) {
       coords[0][0] += 1;
       coords[0][1] -= 1;   
       coords[2][0] += 1;
       coords[2][1] += 1;
       coords[3][1] += 2;
       orient = 0;
   } else if(orient == 2) {
       coords[0][0] -= 2;
       coords[0][1] -= 1;
       coords[1][0] -= 1;
       coords[2][1] -= 1; 
       coords[3][0] += 1;
       orient = 1;
   } else if(orient == 3) {
       coords[0][1] += 2;
       coords[1][0] += 1;
       coords[1][1] += 1;
       coords[3][0] += 1;
       coords[3][1] -= 1;
       orient = 2;
   }
   for(int j = 0; j < 4; j++) {
     b.ChangeCell(coords[j][1], coords[j][0], 'S');
   }
}

void SBlock::clockwise(Board &b) {
  for(int i = 0; i < 4; i++) {
    b.ChangeCell(coords[i][1], coords[i][0], ' ');
  }
  if(orient == 0) {
    coords[0][1] -= 2;
    coords[1][0] -= 1;
    coords[1][1] -= 1;
    coords[3][0] -= 1;
    coords[3][1] += 1;
    orient = 1;
  } else if(orient == 1) {
      coords[0][0] += 2; 
      coords[0][1] += 1;
      coords[1][0] += 1;
      coords[2][1] += 1;
      coords[3][0] -= 1;
      orient = 2;
  } else if(orient == 2) {
      coords[0][0] -= 1;
      coords[0][1] += 1;
      coords[2][0] -= 1;
      coords[2][1] -= 1;
      coords[3][1] -= 2;
      orient = 3;
  } else if(orient == 3) {
      coords[0][0] -= 1;
      coords[1][1] += 1;
      coords[2][0] += 1;
      coords[3][0] += 2; 
      coords[3][1] += 1;
      orient = 0;
  } 
  for(int j = 0; j < 4; j++) {
     b.ChangeCell(coords[j][1], coords[j][0], 'S');
  }
}

void SBlock::right(Board &b) {
    bool indicator = 0;
    bool otherIndicator = 0;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if ((coords[i][0] + 1) == (coords[j][0]) && coords[i][1] == coords[j][1]) {
                indicator = 1;
            }
	}
	if(indicator == 0) {        
            if (!(b.theBoard[coords[i][1]][coords[i][0]+1].getState() == ' ')) {
                    otherIndicator = 1;
            }
        }
	indicator = 0;
    }
    for (int e = 0; e < 4; e++){
      if (coords[e][0] == 9){
        otherIndicator = 1;
      }
    }
    if(otherIndicator == 0) {
        for(int i = 0; i < 4; i++) {
            b.ChangeCell(coords[i][1], coords[i][0], ' ');
        }
        for(int i = 0; i < 4; i++) {
            coords[i][0] += 1;
        }
        for(int i = 0; i < 4; i++) {
            b.ChangeCell(coords[i][1], coords[i][0], 'S');
        }
    }    
}

void SBlock::left(Board &b) {
    bool indicator = 0;
    bool otherIndicator = 0;
    
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if ((coords[i][0] - 1) == (coords[j][0]) && coords[i][1] == coords[j][1]) {
                indicator = 1;
            }
	}
	if(indicator == 0) {        
            if (!(b.theBoard[coords[i][1]][(coords[i][0]-1)].getState() == ' ')) {
                    otherIndicator = 1;
            }
        }
	indicator = 0;
    }
    for (int e = 0; e < 4; e++){
      if (coords[e][0] == 0){
        otherIndicator = 1;
      }
    }
    if(otherIndicator == 0) {
        for(int i = 0; i < 4; i++) {
            b.ChangeCell(coords[i][1], coords[i][0], ' ');
        }
        for(int i = 0; i < 4; i++) {
            coords[i][0] -= 1;
        }
        for(int i = 0; i < 4; i++) {
            b.ChangeCell(coords[i][1], coords[i][0], 'S');
        }
    }
}

void SBlock::down(Board &b) {
    bool indicator = 0;
    bool otherIndicator = 0;
    
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if ((coords[i][1] + 1) == (coords[j][1]) && coords[i][0] == coords[j][0]) {
		indicator = 1;
            }
	}
	if(indicator == 0) {
            if ((b.theBoard[(coords[i][1]+1)][coords[i][0]].getState() != ' ')) {
                    otherIndicator = 1;
            }
        }
	if (coords[i][1] == 14){
	  otherIndicator = 1;
	}
	indicator = 0;
    }
    if(otherIndicator == 0) {
        for(int i = 0; i < 4; i++) {
            b.ChangeCell(coords[i][1], coords[i][0], ' ');
        }
        for(int i = 0; i < 4; i++) {
            coords[i][1] += 1;
        }
        for(int i = 0; i < 4; i++) {
            b.ChangeCell(coords[i][1], coords[i][0], 'S');
        }
    }
    
}

void SBlock::drop(Board &b) {
    for (int i = 0; i < 15; i++){
        this->down(b);
    }
}

/* O-BLOCK METHODS */

OBlock::OBlock(Board &b) {
  SetShape(Oshape);
/*  for(int i = 0; i < 4; i++) {
    b.ChangeCell(coords[i][1], coords[i][0], 'O');
  }*/
}

void OBlock::show(Board &b) {
  for (int i = 0; i < 4; i++) {
    b.ChangeCell(coords[i][1], coords[i][0], 'O');
  }
}

void OBlock::counterclockwise(Board &b) {
    return;
}

void OBlock::clockwise(Board &b) {
    return;
}

void OBlock::right(Board &b) {
    bool indicator = 0;
    bool otherIndicator = 0;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if ((coords[i][0] + 1) == (coords[j][0]) && coords[i][1] == coords[j][1]) {
                indicator = 1;
            }
	}
	if(indicator == 0) {        
            if (!(b.theBoard[coords[i][1]][coords[i][0]+1].getState() == ' ')) {
                    otherIndicator = 1;
            }
        }
	indicator = 0;
    }
    for (int e = 0; e < 4; e++){
      if (coords[e][0] == 9){
        otherIndicator = 1;
      }
    }
    if(otherIndicator == 0) {
        for(int i = 0; i < 4; i++) {
            b.ChangeCell(coords[i][1], coords[i][0], ' ');
        }
        for(int i = 0; i < 4; i++) {
            coords[i][0] += 1;
        }
        for(int i = 0; i < 4; i++) {
            b.ChangeCell(coords[i][1], coords[i][0], 'O');
        }
    }    
}

void OBlock::left(Board &b) {
    bool indicator = 0;
    bool otherIndicator = 0;
    
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if ((coords[i][0] - 1) == (coords[j][0]) && coords[i][1] == coords[j][1]) {
                indicator = 1;
            }
	}
	if(indicator == 0) {        
            if (!(b.theBoard[coords[i][1]][(coords[i][0]-1)].getState() == ' ')) {
                    otherIndicator = 1;
            }
        }
	indicator = 0;
    }
    for (int e = 0; e < 4; e++){
      if (coords[e][0] == 0){
        otherIndicator = 1;
      }
    }
    if(otherIndicator == 0) {
        for(int i = 0; i < 4; i++) {
            b.ChangeCell(coords[i][1], coords[i][0], ' ');
        }
        for(int i = 0; i < 4; i++) {
            coords[i][0] -= 1;
        }
        for(int i = 0; i < 4; i++) {
            b.ChangeCell(coords[i][1], coords[i][0], 'O');
        }
    }
}

void OBlock::down(Board &b) {
    bool indicator = 0;
    bool otherIndicator = 0;
    
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if ((coords[i][1] + 1) == (coords[j][1]) && coords[i][0] == coords[j][0]) {
                indicator = 1;
            }
	}
	if(indicator == 0) {
            if ((b.theBoard[(coords[i][1]+1)][coords[i][0]].getState() != ' ')) {
                    otherIndicator = 1;
            }
        }
	if (coords[i][1] == 14){
	  otherIndicator = 1;
	}
	indicator = 0;
    }
    if(otherIndicator == 0) {
        for(int i = 0; i < 4; i++) {
            b.ChangeCell(coords[i][1], coords[i][0], ' ');
        }
        for(int i = 0; i < 4; i++) {
            coords[i][1] += 1;
        }
        for(int i = 0; i < 4; i++) {
            b.ChangeCell(coords[i][1], coords[i][0], 'O');
        }
    }
    
}

void OBlock::drop(Board &b) {
    for (int i = 0; i < 15; i++){
        this->down(b);
    }
}

/* Z-BLOCK METHODS */

ZBlock::ZBlock(Board &b) {
  SetShape(Zshape);
  orient = 0;
/*  for(int i = 0; i < 4; i++) {
    b.ChangeCell(coords[i][1], coords[i][0], 'Z');
  }*/
}

void ZBlock::show(Board &b) {
  for (int i = 0; i < 4; i++) {
    b.ChangeCell(coords[i][1], coords[i][0], 'Z');
  }
}

void ZBlock::counterclockwise(Board &b) {
  for(int i = 0; i < 4; i++) {
    b.ChangeCell(coords[i][1], coords[i][0], ' '); 
  }
  if(orient == 0) {
    coords[0][1] += 1;
    coords[1][0] -= 1;
    coords[2][1] -= 1;
    coords[2][0] -= 1;
    coords[2][1] -= 2;
    orient = 3;
  } else if(orient == 1) {
     coords[0][0] += 2;
     coords[1][0] += 1;
     coords[1][1] += 1;
     coords[3][0] -= 1;
     coords[3][1] += 1;
     orient = 0;
  } else if(orient == 2) {
     coords[0][1] += 1;
     coords[1][0] -= 1;
     coords[2][1] -= 1;
     coords[3][0] -= 1;
     coords[3][1] -= 2;
     orient = 1; 
  } else if(orient == 3) { 
     coords[0][0] += 2;
     coords[0][1] -= 1;
     coords[1][0] += 1;
     coords[1][1] += 1;
     coords[3][0] -= 1;
     coords[3][1] += 1;
     orient = 2; 
  } 
  for(int j = 0; j < 4; j++) {
    b.ChangeCell(coords[j][1], coords[j][0], 'Z');
  }
}

void ZBlock::clockwise(Board &b) {
  for(int i = 0; i < 4; i++) {
    b.ChangeCell(coords[i][1], coords[i][0], ' ');
  }
  if(orient == 0) {
    coords[0][0] += 1;
    coords[0][1] -= 1;
    coords[2][0] -= 1;
    coords[2][1] -= 1;
    coords[3][0] -= 2;
    orient = 1;
  } else if(orient == 1) {
      coords[0][0] += 1;
      coords[0][1] += 2;
      coords[1][1] += 1;
      coords[2][0] += 1;
      coords[3][1] -= 1;
      orient = 2;
  } else if(orient == 2) {
      coords[0][0] -= 2;
      coords[1][0] -= 1;
      coords[1][1] -= 1;
      coords[3][0] += 1;
      coords[3][1] -= 1;
      orient = 3;
  } else if(orient == 3) {
      coords[0][1] -= 1;
      coords[1][0] += 1;
      coords[2][1] += 1;
      coords[3][0] += 1;
      coords[3][1] += 2;
      orient = 0;
  } 
  for(int j = 0; j < 4; j++) {
    b.ChangeCell(coords[j][1], coords[j][0], 'Z');
  }
}

void ZBlock::right(Board &b) {
    bool indicator = 0;
    bool otherIndicator = 0;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if ((coords[i][0] + 1) == (coords[j][0]) && coords[i][1] == coords[j][1]) {
                indicator = 1;
            }
	}
	if(indicator == 0) {        
            if (!(b.theBoard[coords[i][1]][coords[i][0]+1].getState() == ' ')) {
                    otherIndicator = 1;
            }
        }
 	indicator = 0;
   }
    for (int e = 0; e < 4; e++){
      if (coords[e][0] == 9){
        otherIndicator = 1;
      }
    }
    if(otherIndicator == 0) {
        for(int i = 0; i < 4; i++) {
            b.ChangeCell(coords[i][1], coords[i][0], ' ');
        }
        for(int i = 0; i < 4; i++) {
            coords[i][0] += 1;
        }
        for(int i = 0; i < 4; i++) {
            b.ChangeCell(coords[i][1], coords[i][0], 'Z');
        }
    }    
}

void ZBlock::left(Board &b) {
    bool indicator = 0;
    bool otherIndicator = 0;
    
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if ((coords[i][0] - 1) == (coords[j][0]) && coords[i][1] == coords[j][1]) {
                indicator = 1;
            }
	}
	if(indicator == 0) {        
            if (!(b.theBoard[coords[i][1]][(coords[i][0]-1)].getState() == ' ')) {
                    otherIndicator = 1;
            }
        }
 	indicator = 0;
   }
    for (int e = 0; e < 4; e++){
      if (coords[e][0] == 0){
        otherIndicator = 1;
      }
    }
    if(otherIndicator == 0) {
        for(int i = 0; i < 4; i++) {
            b.ChangeCell(coords[i][1], coords[i][0], ' ');
        }
        for(int i = 0; i < 4; i++) {
            coords[i][0] -= 1;
        }
        for(int i = 0; i < 4; i++) {
            b.ChangeCell(coords[i][1], coords[i][0], 'Z');
        }
    }
}

void ZBlock::down(Board &b) {
    bool indicator = 0;
    bool otherIndicator = 0;
    
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if ((coords[i][1] + 1) == (coords[j][1]) && coords[i][0] == coords[j][0]) {
                indicator = 1;
            }
	}
	if(indicator == 0) {
            if ((b.theBoard[(coords[i][1]+1)][coords[i][0]].getState() != ' ')) {
                    otherIndicator = 1;
            }
        }
	if (coords[i][1] == 14){
	  otherIndicator = 1;
	}
	indicator = 0;
    }
    if(otherIndicator == 0) {
        for(int i = 0; i < 4; i++) {
            b.ChangeCell(coords[i][1], coords[i][0], ' ');
        }
        for(int i = 0; i < 4; i++) {
            coords[i][1] += 1;
        }
        for(int i = 0; i < 4; i++) {
            b.ChangeCell(coords[i][1], coords[i][0], 'Z');
        }
    }
    
}

void ZBlock::drop(Board &b) {
    for (int i = 0; i < 15; i++){
        this->down(b);
    }
}

/* T-BLOCK METHODS */

TBlock::TBlock(Board &b) {
  SetShape(Tshape);
  orient = 0;
/*  for(int i = 0; i < 4; i++) {
    b.ChangeCell(coords[i][1], coords[i][0], 'T');
  }*/
}

void TBlock::show(Board &b) {
  for (int i = 0; i < 4; i++) {
    b.ChangeCell(coords[i][1], coords[i][0], 'T');
  }
}

void TBlock::counterclockwise(Board &b) {
  for(int i = 0; i < 4; i++) {
     b.ChangeCell(coords[i][1], coords[i][0], ' ');
  }
  if(orient == 0) {
    coords[0][1] += 1;
    coords[1][0] -= 1;
    coords[2][0] -= 2;
    coords[2][1] -= 1;
    coords[2][1] -= 1;
    orient = 3;
  } else if(orient == 1) {
      coords[0][0] += 2;
      coords[1][0] += 1;
      coords[1][1] += 1;
      coords[2][1] += 2;
      coords[3][0] -= 1;
      orient = 0;
  } else if(orient == 2) {
      coords[0][0] -= 1;
      coords[0][1] -= 2;
      coords[1][1] -= 1;
      coords[2][0] += 1;
      coords[3][0] -= 1;
      orient = 1;
  } else if(orient == 3) {
      coords[0][0] -= 1;
      coords[0][1] += 1;
      coords[2][0] += 1;
      coords[2][1] -= 1;
      coords[3][0] += 1;
      coords[3][1] += 1;
      orient = 2;
  } 
  for(int j = 0; j < 4; j++) {
    b.ChangeCell(coords[j][1], coords[j][0], 'T');
  }
}

void TBlock::clockwise(Board &b) {
  for(int i = 0; i < 4; i++) {
    b.ChangeCell(coords[i][1], coords[i][0], ' ');
  }
  if(orient == 0) {
    coords[0][0] += 1;
    coords[0][1] -= 1;
    coords[2][0] -= 1;
    coords[2][1] += 1;
    coords[3][0] -= 1;
    coords[3][1] -= 1;
    orient = 1;
  } else if(orient == 1) {
     coords[0][0] += 1;
     coords[0][1] += 2;
     coords[1][1] += 1;
     coords[2][0] -= 1;
     coords[3][0] += 1;
     orient = 2;
  } else if(orient == 2) {
     coords[0][0] -= 2;
     coords[1][0] -= 1;
     coords[1][1] -= 1;
     coords[2][1] -= 2;
     orient = 3;
  } else if(orient == 3) {
     coords[0][1] -= 1;
     coords[1][0] += 1;
     coords[2][0] += 2;
     coords[2][1] += 1;
     coords[3][1] += 1;
     orient = 0;
  } 
  for(int j = 0; j < 4; j++) {
    b.ChangeCell(coords[j][1], coords[j][0], 'T');
  }
}

void TBlock::right(Board &b) {
    bool indicator = 0;
    bool otherIndicator = 0;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if ((coords[i][0] + 1) == (coords[j][0]) && coords[i][1] == coords[j][1]) {
                indicator = 1;
            }
	}
	if(indicator == 0) {        
            if (!(b.theBoard[coords[i][1]][coords[i][0]+1].getState() == ' ')) {
                    otherIndicator = 1;
            }
        }
 	indicator = 0;
   }
    for (int e = 0; e < 4; e++){
      if (coords[e][0] == 9){
        otherIndicator = 1;
      }
    }
    if(otherIndicator == 0) {
        for(int i = 0; i < 4; i++) {
            b.ChangeCell(coords[i][1], coords[i][0], ' ');
        }
        for(int i = 0; i < 4; i++) {
            coords[i][0] += 1;
        }
        for(int i = 0; i < 4; i++) {
            b.ChangeCell(coords[i][1], coords[i][0], 'T');
        }
    }    
}

void TBlock::left(Board &b) {
    bool indicator = 0;
    bool otherIndicator = 0;
    
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if ((coords[i][0] - 1) == (coords[j][0]) && coords[i][1] == coords[j][1]) {
		indicator = 1;
            }
	}
	if(indicator == 0) {        
            if (!(b.theBoard[coords[i][1]][(coords[i][0]-1)].getState() == ' ')) {
                    otherIndicator = 1;
            }
        }
	indicator = 0;
    }
    for (int e = 0; e < 4; e++){
      if (coords[e][0] == 0){
        otherIndicator = 1;
      }
    }
    if(otherIndicator == 0) {
        for(int i = 0; i < 4; i++) {
            b.ChangeCell(coords[i][1], coords[i][0], ' ');
        }
        for(int i = 0; i < 4; i++) {
            coords[i][0] -= 1;
        }
        for(int i = 0; i < 4; i++) {
            b.ChangeCell(coords[i][1], coords[i][0], 'T');
        }
    }
}

void TBlock::down(Board &b) {
    bool indicator = 0;
    bool otherIndicator = 0;
    
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if ((coords[i][1] + 1) == (coords[j][1]) && coords[i][0] == coords[j][0]) {
                indicator = 1;
            }
	}
	if(indicator == 0) {
            if ((b.theBoard[(coords[i][1]+1)][coords[i][0]].getState() != ' ')) {
                    otherIndicator = 1;
            }
        }
	if (coords[i][1] == 14){
	  otherIndicator = 1;
	}
	indicator = 0;
    }
    if(otherIndicator == 0) {
        for(int i = 0; i < 4; i++) {
            b.ChangeCell(coords[i][1], coords[i][0], ' ');
        }
        for(int i = 0; i < 4; i++) {
            coords[i][1] += 1;
        }
        for(int i = 0; i < 4; i++) {
            b.ChangeCell(coords[i][1], coords[i][0], 'T');
        }
    }
    
}

void TBlock::drop(Board &b) {
    for (int i = 0; i < 15; i++){
        this->down(b);
    }
}

/* I-BLOCK METHODS */

IBlock::IBlock(Board &b) {
  SetShape(Ishape);
  orient = 0;
/*  for(int i = 0; i < 4; i++) {
    b.ChangeCell(coords[i][1], coords[i][0], 'I');
  }*/
}

void IBlock::show(Board &b) {
  for (int i = 0; i < 4; i++) {
    b.ChangeCell(coords[i][1], coords[i][0], 'I');
  }
}

void IBlock::counterclockwise(Board &b) {
   for(int i = 0; i < 4; i++) {
     b.ChangeCell(coords[i][1], coords[i][0], ' ');
  }
  if(orient == 0) {
     coords[1][0] -= 1;
     coords[1][1] -= 1;
     coords[2][0] -= 2;
     coords[2][1] -= 1;
     coords[3][0] -= 3;
     coords[3][1] -= 2;
     orient = 3;
  } else if(orient == 1) {
     coords[0][0] += 3;
     coords[1][0] += 2;
     coords[1][1] += 1;
     coords[2][0] += 1;
     coords[2][1] += 2;
     coords[3][1] += 3;
     orient = 0;
  } else if(orient == 2) {
     coords[0][0] -= 3;
     coords[0][1] -= 3;
     coords[1][0] -= 2;
     coords[1][1] -= 2;
     coords[2][0] -= 1;
     coords[2][1] -= 1;
     orient = 1;
  } else if(orient == 3) {
     coords[0][0] -= 3;
     coords[0][1] -= 3;
     coords[1][0] -= 2;
     coords[1][1] -= 2;
     coords[2][0] -= 1;
     coords[2][1] -= 1;
     orient = 2;
  } 
  for(int j = 0; j < 4; j++) {
    b.ChangeCell(coords[j][1], coords[j][0], 'I');
  }
}

void IBlock::clockwise(Board &b) {

  for(int i = 0; i < 4; i++) {
     b.ChangeCell(coords[i][1], coords[i][0], ' ');
  }
  if(orient == 0) {
     coords[0][1] -= 3;
     coords[1][0] -= 1;
     coords[1][1] -= 2;
     coords[2][0] -= 2;
     coords[2][1] -= 1;
     coords[3][0] -= 3;
     orient = 1;
  }

  else if(orient == 1) {
    coords[1][0] += 1;
    coords[1][1] += 1;
    coords[2][0] += 2;
    coords[2][1] += 2; 
    coords[3][0] += 3;
    coords[3][1] += 3;
    orient = 2;
  } else if(orient == 2) {
     coords[0][0] -= 3;
     coords[1][0] -= 3;
     coords[1][1] -= 1;
     coords[2][0] -= 1;
     coords[2][1] -= 2;
     coords[3][1] -= 3;
     orient = 3;
  } else if(orient == 3) {
     coords[1][0] += 1;
     coords[1][1] += 1;
     coords[2][0] += 2;
     coords[2][1] += 2;
     coords[3][0] += 3;
     coords[3][1] += 3;
     orient = 0;
  }
  for(int j = 0; j < 4; j++) {
    b.ChangeCell(coords[j][1], coords[j][0], 'I');
  }

} void IBlock::right(Board &b) {
    bool indicator = 0;
    bool otherIndicator = 0;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if ((coords[i][0] + 1) == (coords[j][0]) && coords[i][1] == coords[j][1]) {
                indicator = 1;
            }
	}
	if(indicator == 0) {        
            if (!(b.theBoard[coords[i][1]][coords[i][0]+1].getState() == ' ')) {
                    otherIndicator = 1;
            }
        }
 	indicator = 0;
   }
    for (int e = 0; e < 4; e++){
      if (coords[e][0] == 9){
        otherIndicator = 1;
      }
    }
    if(otherIndicator == 0) {
        for(int i = 0; i < 4; i++) {
            b.ChangeCell(coords[i][1], coords[i][0], ' ');
        }
        for(int i = 0; i < 4; i++) {
            coords[i][0] += 1;
        }
        for(int i = 0; i < 4; i++) {
            b.ChangeCell(coords[i][1], coords[i][0], 'I');
        }
    }    
}

void IBlock::left(Board &b) {
    bool indicator = 0;
    bool otherIndicator = 0;
    
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if ((coords[i][0] - 1) == (coords[j][0]) && coords[i][1] == coords[j][1]) {
                indicator = 1;
            }
	}
	if(indicator == 0) {        
            if (!(b.theBoard[coords[i][1]][(coords[i][0]-1)].getState() == ' ')) {
                    otherIndicator = 1;
            }
        }
 	indicator = 0;
   }
    for (int e = 0; e < 4; e++){
      if (coords[e][0] == 0){
        otherIndicator = 1;
      }
    }
    if(otherIndicator == 0) {
        for(int i = 0; i < 4; i++) {
            b.ChangeCell(coords[i][1], coords[i][0], ' ');
        }
        for(int i = 0; i < 4; i++) {
            coords[i][0] -= 1;
        }
        for(int i = 0; i < 4; i++) {
            b.ChangeCell(coords[i][1], coords[i][0], 'I');
        }
    }
}

void IBlock::down(Board &b) {
    bool indicator = 0;
    bool otherIndicator = 0;
    
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if ((coords[i][1] + 1) == (coords[j][1]) && coords[i][0] == coords[j][0]) {
                indicator = 1;
            }
	}
	if(indicator == 0) {
            if ((b.theBoard[(coords[i][1]+1)][coords[i][0]].getState() != ' ')) {
                    otherIndicator = 1;
            }
        }
	if (coords[i][1] == 14){
	  otherIndicator = 1;
	}
	indicator = 0;
    }
    if(otherIndicator == 0) {
        for(int i = 0; i < 4; i++) {
            b.ChangeCell(coords[i][1], coords[i][0], ' ');
        }
        for(int i = 0; i < 4; i++) {
            coords[i][1] += 1;
        }
        for(int i = 0; i < 4; i++) {
            b.ChangeCell(coords[i][1], coords[i][0], 'I');
        }
    }
    
}

void IBlock::drop(Board &b) {
    for (int i = 0; i < 15; i++){
        this->down(b);
    }
}
