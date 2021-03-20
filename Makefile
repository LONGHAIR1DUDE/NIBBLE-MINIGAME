FLAGS =-Wall -g
CC = g++ 
EXE1 = ./bin/afficheTerrain
EXE2 = ./bin/test

all: $(EXE1) $(EXE2)

$(EXE1): Terrain.o mainAffiche.o
	$(CC) -g ./obj/mainAffiche.o ./obj/Terrain.o -o $(EXE1)

$(EXE2): Serpent.o mainTestRegression.o
	$(CC) -g ./obj/mainTestRegression.o ./obj/Serpent.o -o $(EXE2)
	
Terrain.o: ./src/Terrain.h ./src/Terrain.cpp ./src/Point.h
	$(CC) $(FLAGS) -c ./src/Terrain.cpp -o ./obj/Terrain.o

Serpent.o: ./src/Serpent.h ./src/Serpent.cpp ./src/Terrain.h ./src/Point.h
	$(CC) $(FLAGS) -c ./src/Serpent.cpp -o ./obj/Serpent.o

mainTestRegression.o: Terrain.o Serpent.o ./src/mainTestRegression.cpp
	$(CC) $(FLAGS) -c ./src/mainTestRegression.cpp -o ./obj/mainTestRegression.o	

mainAffiche.o: ./src/mainAffiche.cpp ./src/Terrain.cpp
	$(CC) $(FLAGS) -c ./src/mainAffiche.cpp -o ./obj/mainAffiche.o

clean: 
	rm -rf ./obj/* ./bin/*
