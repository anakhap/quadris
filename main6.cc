#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include "block.h"
#include "board.h"

using namespace std;

char getPiece(int l){                   //function to choose a random letter based on level
  char c;

  if (l == 1){
    int x = rand() % 12;
    
    if(x == 0) {
	return 'S';			// 1/12 chance
    } else if(x == 1) {
	return 'Z';			// 1/12 chacnce
    } else if(x == 2 || x == 3) {
	return 'I';			// 1/6 chance
    } else if(x == 4 || x == 5) {
	return 'L';			// 1/6 chance
    } else if(x == 6 || x == 7) {
	return 'O';			// 1/6 chance
    } else if(x == 8 || x == 9) {
	return 'T';			// 1/6 change
    } else if(x == 10 || x == 11) {
	return 'J';			// 1/6 chance
    } 
  } else if (l == 2) {
    int x = rand() % 7;			// 1/7 chance for all
    
    if(x == 0) {
	return 'S';
    } else if(x == 1) {
	return 'Z';
    } else if(x == 2) {
	return 'I';
    } else if(x == 3) {
	return 'L';
    } else if(x == 4) {
	return 'O';
    } else if(x == 5) {
	return 'T';
    } else if(x == 6) {
	return 'J';
    } 

  } else if (l == 3) {
    int x = rand() %9;
    
    if(x == 0 || x == 1) {
	return 'S';			// 2/9 chance
    } else if(x == 2 || x == 3) {
	return 'Z';			// 2/9 chance
    } else if(x == 4) {
	return 'I';			// 1/9 chance
    } else if(x == 5) {
	return 'L';			// 1/9 chance
    } else if(x == 6) {
	return 'O';
    } else if(x == 7) {
	return 'T';
    } else if(x == 8) {
	return 'J';
    } 

  }
}

int main() {
//    ifstream ifs("sequence.txt");
    int level = 1;
    Board newboard(level);
    char curr;
    char next;
    JBlock jb(newboard);
    LBlock lb(newboard);
    IBlock ib(newboard);
    SBlock sb(newboard);
    TBlock tb(newboard);
    ZBlock zb(newboard);
    OBlock ob(newboard);

    JBlock basejb(newboard);
    LBlock baselb(newboard);
    IBlock baseib(newboard);
    SBlock basesb(newboard);
    TBlock basetb(newboard);
    ZBlock basezb(newboard);
    OBlock baseob(newboard);

    AbstractBlock *currblock;
    AbstractBlock *nextblock;
//    if (level = 0) {
//      ifs >> curr;
//      ifs >> next;
//    } else {
      curr = getPiece(level);
      next = getPiece(level);
//    }

    if (curr == 'I'){
      currblock = &ib;
    } else if (curr == 'J'){
      currblock = &jb;
    } else if (curr == 'L'){
      currblock = &lb;
    } else if (curr == 'O'){
      currblock = &ob;
    } else if (curr == 'S'){
      currblock = &sb;
    } else if (curr == 'Z'){
      currblock = &zb;
    } else if (curr == 'T'){
      currblock = &tb;
    }
    if (next == 'I'){
      nextblock = &ib;
    } else if (next == 'J'){
      nextblock = &jb;
    } else if (next == 'L'){
      nextblock = &lb;
    } else if (next == 'O'){
      nextblock = &ob;
    } else if (next == 'S'){
      nextblock = &sb;
    } else if (next == 'Z'){
      nextblock = &zb;
    } else if (next == 'T'){
      nextblock = &tb;
    }
      
        currblock->show(newboard);
        newboard.Output();
       
        string input;
        while(cin >> input) {
            if(input == "left") {
                currblock->left(newboard);
		newboard.Output();
            } else if(input == "right") {
                currblock->right(newboard);
		newboard.Output();
            }  else if(input == "clockwise") {
                currblock->clockwise(newboard);
		newboard.Output();
            } else if(input == "counterclockwise") {
                currblock->counterclockwise(newboard);
		newboard.Output();
            } else if(input == "levelup") {
                if (level < 3)
		  level++;
                newboard.SetLevel(level);
		newboard.Output();
            } else if(input == "leveldown") {
                if (level > 0)
		  level--;
                newboard.SetLevel(level);
 		newboard.Output();
            } else if(input == "restart") {
                newboard.Restart(); // restart method in board.cc
		newboard.Output();
            }
            else if(input == "down") {
                currblock->down(newboard);
		bool indicator = 0;
    		bool otherIndicator = 0;
    
    		for(int i = 0; i < 4; i++) {
        		for(int j = 0; j < 4; j++) {
            			if((currblock->coords[i][1] + 1) == (currblock->coords[j][1]) && currblock->coords[i][0] == currblock->coords[j][0]) {
                			indicator = 1;
            			} else if(indicator == 0) {
                			if(!(newboard.theBoard[(currblock->coords[i][1]-1)][currblock->coords[i][0]].getState() == (' '))) {
                    				otherIndicator = 1; 
                			}
            			}
        		}
			indicator = 0;	
    		}
/*		if(otherIndicator == 1) {
		  currblock->drop(newboard);
		  newboard.CheckLines();
		  ob = baseob;
		  jb = basejb;
		  lb = baselb;
		  tb = basetb;
		  sb = basesb;
		  zb = basezb;
		  ib = baseib;

		  if (level == 0){
		    ifs >> next;
		  } else {
		    next = getPiece(level);
		  }
		  if (next == 'I'){
  		    nextblock = &ib;
		  } else if (next == 'J'){
		    nextblock = &jb;
		  } else if (next == 'L'){
		    nextblock = &lb;
		  } else if (next == 'O'){
		    nextblock = &ob;
		  } else if (next == 'S'){
		    nextblock = &sb;
		  } else if (next == 'Z'){
		    nextblock = &zb;
		  } else if (next == 'T'){
		    nextblock = &tb;
		  }

                  currblock = nextblock;
		  currblock->show(newboard);
		}*/
		newboard.Output();
                
            } else if(input == "drop") {
		currblock->drop(newboard);
		newboard.CheckLines();
		ob = baseob;
		jb = basejb;
		lb = baselb;
		tb = basetb;
		sb = basesb;
		zb = basezb;
		ib = baseib;

//		if (level == 0){
//		  ifs >> next;
//		} else {
		  next = getPiece(level);
//		}
		if (next == 'I'){
  		  nextblock = &ib;
		} else if (next == 'J'){
		  nextblock = &jb;
		} else if (next == 'L'){
		  nextblock = &lb;
		} else if (next == 'O'){
		  nextblock = &ob;
		} else if (next == 'S'){
		  nextblock = &sb;
		} else if (next == 'Z'){
		  nextblock = &zb;
		} else if (next == 'T'){
		  nextblock = &tb;
		}

                currblock = nextblock;
		currblock->show(newboard);
		newboard.Output();
	}
    }
//    ifs.close();
}
