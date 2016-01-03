CC = g++
SRC = *.cpp
EXE = main



all:
	$(CC) -g -lpthread -o $(EXE) $(SRC)
