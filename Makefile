FLAGS =-Wall -g
CC = g++ 
EXE1 = ./bin/afficheTerrain

all: $(EXE1)

$(EXE1): Terrain.o mainAffiche.o Point.o
	$(CC) -g ./obj/mainAffiche.o ./obj/Point.o ./obj/Terrain.o -o $(EXE1)
	
Serpent.o: ./src/Serpent.h ./src/Serpent.cpp ./src/Terrain.h ./src/Point.h
	$(CC) $(FLAGS) -c ./src/Serpent.cpp -o ./obj/Serpent.o

Mur.o: ./src/Mur.h ./src/Mur.cpp ./src/Terrain.h ./src/Point.h
	$(CC) $(FLAGS) -c ./src/Mur.cpp -o ./obj/Mur.o

Terrain.o: ./src/Terrain.h ./src/Terrain.cpp ./src/Point.h
	$(CC) $(FLAGS) -c ./src/Terrain.cpp -o ./obj/Terrain.o

Point.o: ./src/Point.h ./src/Point.cpp
	$(CC) $(FLAGS) -c ./src/Point.cpp -o ./obj/Point.o

mainAffiche.o: ./src/mainAffiche.cpp ./src/Terrain.cpp
	$(CC) $(FLAGS) -c ./src/mainAffiche.cpp -o ./obj/mainAffiche.o

clean: 
	rm -rf ./obj/* ./bin/*
