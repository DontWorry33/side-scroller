CC=g++
LIBS= -std=c++0x -lsfml-graphics -lsfml-window -lsfml-system

all:
	$(CC) -o ufogame ufogame2.cpp $(LIBS)
	
