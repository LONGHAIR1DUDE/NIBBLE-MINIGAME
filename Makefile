FLAGS =-Wall -g
CC = g++ 
EXE1 = ./bin/afficheTerrain

all: $(EXE1)

$(EXE1): Terrain.o mainAffiche.o
	$(CC) -g ./obj/mainAffiche.o ./obj/Terrain.o -o $(EXE1)
	
Terrain.o: ./src/Terrain.h ./src/Terrain.cpp ./src/Point.h
	$(CC) $(FLAGS) -c ./src/Terrain.cpp -o ./obj/Terrain.o

mainAffiche.o: ./src/mainAffiche.cpp ./src/Terrain.cpp
	$(CC) $(FLAGS) -c ./src/mainAffiche.cpp -o ./obj/mainAffiche.o

clean: 
	rm -rf ./obj/* ./bin/*