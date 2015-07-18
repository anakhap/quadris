main6: main6.o board.o block.o cell.o
	g++ main6.o board.o block.o cell.o -o quadris

board.o: board.cc board.h cell.h
	g++ -c board.cc

block.o: block.cc block.h board.h cell.h
	g++ -c block.cc

cell.o: cell.cc cell.h
	g++ -c cell.cc

main6.o: main6.cc board.h block.h cell.h
	g++ -c main6.cc

.PHONY: clean

clean:
	rm *.o main
