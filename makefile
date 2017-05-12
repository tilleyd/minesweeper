FLAGS = -Wall -std=c++11
LIB = -lncurses

minesweeper: bin/main.o bin/cell.o bin/field.o
	g++ $(FLAGS) -o minesweeper bin/main.o bin/cell.o bin/field.o $(LIB)

bin/main.o: src/main.cpp
	g++ $(FLAGS) -o bin/main.o -c src/main.cpp

bin/cell.o: src/cell.cpp src/cell.h
	g++ $(FLAGS) -o bin/cell.o -c src/cell.cpp

bin/field.o: src/field.cpp src/field.h
	g++ $(FLAGS) -o bin/field.o -c src/field.cpp
