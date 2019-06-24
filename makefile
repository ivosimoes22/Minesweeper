CC = g++
CFLAGS = -g -Wall
LINKER_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lm
OBJ_NAME = game
SRC_DIR = ./src/
OBJ_DIR = ./bin/

$(OBJ_NAME): main.o game.o
	$(CC) $(CFLAGS) -o $(OBJ_NAME) main.o game.o $(LINKER_FLAGS)

main.o: $(SRC_DIR)main.cpp $(SRC_DIR)game.h
	$(CC) -c $(CFLAGS) $(SRC_DIR)main.cpp
	
game.o: $(SRC_DIR)game.cpp $(SRC_DIR)game.h
	$(CC) -c $(CFLAGS) $(SRC_DIR)game.cpp

clean::
	rm -f *.o core game *~