FLAGS =-Wall -g
CC = g++ 
OBJS = ./obj/Terrain.o ./obj/Serpent.o  ./obj/Point.o ./obj/Jeu.o ./obj/TxtFenetre.o ./obj/TxtJeu.o #./obj/Bonus.o ./obj/Mur.o
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

./obj/Bonus.o: ./src/core/Bonus.h ./src/core/Bonus.cpp ./src/core/Serpent.h ./src/core/Point.h
	$(CC) $(FLAGS) -c ./src/core/Bonus.cpp -o ./obj/Bonus.o

./obj/Serpent.o: ./src/core/Serpent.h ./src/core/Serpent.cpp ./src/core/Terrain.h ./src/core/Point.h
	$(CC) $(FLAGS) -c ./src/core/Serpent.cpp -o ./obj/Serpent.o

./obj/Mur.o: ./src/core/Mur.h ./src/core/Mur.cpp ./src/core/Terrain.h ./src/core/Point.h
	$(CC) $(FLAGS) -c  ./src/core/Mur.cpp -o ./obj/Mur.o

./obj/Terrain.o: ./src/core/Terrain.h ./src/core/Terrain.cpp ./src/core/Point.h
	$(CC) $(FLAGS) -c ./src/core/Terrain.cpp -o ./obj/Terrain.o

./obj/Point.o: ./src/core/Point.h ./src/core/Point.cpp
	$(CC) $(FLAGS) -c ./src/core/Point.cpp -o ./obj/Point.o

./obj/mainTestRegression.o: ./src/core/Terrain.h ./src/core/Serpent.h ./src/core/mainTestRegression.cpp
	$(CC) $(FLAGS) -c ./src/core/mainTestRegression.cpp -o ./obj/mainTestRegression.o	

./obj/mainAffiche.o: ./src/core/mainAffiche.cpp ./src/core/Terrain.h
	$(CC) $(FLAGS) -c ./src/core/mainAffiche.cpp -o ./obj/mainAffiche.o

./obj/Jeu.o: ./src/Jeu.cpp ./src/core/Jeu.h ./src/core/Terrain.h ./src/core/Serpent.h ./src/core/Portail.h ./src/core/Mur.h ./src/core/Bonus.h
	$(CC) $(FLAGS) -c ./src/core/Jeu.cpp -o ./obj/Jeu.o

./obj/TxtFenetre.o: ./src/txt/TxtFenetre.cpp ./src/txt/TxtFenetre.h
	$(CC) $(FLAGS) -c ./src/txt/TxtFenetre.cpp -o ./obj/TxtFenetre.o

./obj/TxtJeu.o: ./src/txt/TxtJeu.h ./src/txt/TxtJeu.cpp ./src/txt/TxtFenetre.h ./src/core/Jeu.h
	$(CC) $(FLAGS) -c ./src/txt/TxtJeu.cpp -o ./obj/TxtJeu.o

./obj/mainTxt.o: ./src/txt/mainTxt.cpp ./src/txt/TxtFenetre.h ./src/txt/TxtJeu.h
	$(CC) $(FLAGS) -c ./src/txt/mainTxt.cpp -o ./obj/mainTxt.o

clean: 
	rm -rf ./obj/* ./bin/*

