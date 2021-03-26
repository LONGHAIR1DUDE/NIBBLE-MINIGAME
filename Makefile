FLAGS =-Wall -g
CC = g++ 
OBJS = ./obj/Terrain.o ./obj/Serpent.o ./obj/Mur.o ./obj/Point.o ./obj/Bonus.o ./obj/Jeu.o ./obj/TxtFenetre.o ./obj/TxtJeu.o
EXE1 = ./bin/afficheTerrain
EXE2 = ./bin/test
EXE3 = ./bin/jeuTxt


all: $(EXE1) $(EXE2)

jeuTxt: $(EXE3)

$(EXE1): ./obj/Terrain.o ./obj/mainAffiche.o ./obj/Point.o
	$(CC) -g ./obj/mainAffiche.o ./obj/Point.o ./obj/Terrain.o -o $(EXE1)

$(EXE2): ./obj/Serpent.o ./obj/mainTestRegression.o ./obj/Point.o ./obj/Terrain.o
	$(CC) -g ./obj/Terrain.o ./obj/mainTestRegression.o ./obj/Point.o ./obj/Serpent.o -o $(EXE2)
	
$(EXE3): $(OBJS)
	$(CC) -g $(OBJS) -o $(EXE3)

./obj/Bonus.o: ./src/Bonus.h ./src/Bonus.cpp ./src/Serpent.h ./src/Point.h
	$(CC) $(FLAGS) -c ./src/Bonus.cpp -o ./obj/Bonus.o

./obj/Serpent.o: ./src/Serpent.h ./src/Serpent.cpp ./src/Terrain.h ./src/Point.h
	$(CC) $(FLAGS) -c ./src/Serpent.cpp -o ./obj/Serpent.o

./obj/Mur.o: ./src/Mur.h ./src/Mur.cpp ./src/Terrain.h ./src/Point.h
	$(CC) $(FLAGS) -c  ./src/Mur.cpp -o ./obj/Mur.o

./obj/Terrain.o: ./src/Terrain.h ./src/Terrain.cpp ./src/Point.h
	$(CC) $(FLAGS) -c ./src/Terrain.cpp -o ./obj/Terrain.o

./obj/Point.o: ./src/Point.h ./src/Point.cpp
	$(CC) $(FLAGS) -c ./src/Point.cpp -o ./obj/Point.o

./obj/mainTestRegression.o: ./src/Terrain.h ./src/Serpent.h ./src/mainTestRegression.cpp
	$(CC) $(FLAGS) -c ./src/mainTestRegression.cpp -o ./obj/mainTestRegression.o	

./obj/mainAffiche.o: ./src/mainAffiche.cpp ./src/Terrain.h
	$(CC) $(FLAGS) -c ./src/mainAffiche.cpp -o ./obj/mainAffiche.o

./obj/Jeu.o: ./src/Jeu.cpp ./src/Jeu.h ./src/Terrain.h ./src/Serpent.h ./src/Portail.h ./src/Mur.h ./src/Bonus.h
	$(CC) $(FLAGS) -c ./src/Jeu.cpp -o ./obj/Jeu.o

./obj/TxtFenetre.o: ./src/TxtFenetre.cpp ./src/TxtFenetre.h
	$(CC) $(FLAGS) -c ./src/TxtFenetre.cpp -o ./obj/TxtFenetre.o

./obj/TxtJeu.o: ./src/TxtJeu.h ./src/TxtJeu.cpp ./src/TxtFenetre.h ./src/Jeu.h
	$(CC) $(FLAGS) -c ./src/TxtJeu.cpp -o ./src/TxtJeu.o

clean: 
	rm -rf ./obj/* ./bin/*
