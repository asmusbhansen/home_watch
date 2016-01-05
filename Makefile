CC = g++
SRC = *.cpp
EXE = main



all:
	$(CC) -std=c++0x -g -lpthread -o $(EXE) $(SRC)
