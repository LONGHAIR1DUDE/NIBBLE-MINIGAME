FLAGS =-Wall -g
CC = g++ 
OBJS = ./obj/Terrain.o ./obj/Serpent.o  ./obj/Point.o ./obj/Jeu.o ./obj/TxtFenetre.o ./obj/TxtJeu.o ./obj/Bonus.o ./obj/Mur.o ./obj/mainTxt.o 
EXE1 = ./bin/afficheTerrain
EXE2 = ./bin/test
EXE3 = ./bin/nibble_txt

all: $(EXE1) $(EXE2) $(EXE3)

jeuTxt: $(EXE3)

$(EXE1): ./obj/Terrain.o ./obj/mainAffiche.o ./obj/Point.o
	$(CC) -g ./obj/mainAffiche.o ./obj/Point.o ./obj/Terrain.o -o $(EXE1)

$(EXE2): ./obj/Serpent.o ./obj/mainTestRegression.o ./obj/Point.o ./obj/Terrain.o
	$(CC) -g ./obj/Terrain.o ./obj/mainTestRegression.o ./obj/Point.o ./obj/Serpent.o -o $(EXE2)
	
$(EXE3): $(OBJS)
	$(CC) -g $(OBJS) -o $(EXE3)

./obj/Bonus.o: ./src/core/Bonus.cpp ./src/core/Bonus.h ./src/core/Serpent.h ./src/core/Point.h
	$(CC) $(FLAGS) -c $< -o $@

./obj/Serpent.o: ./src/core/Serpent.cpp ./src/core/Serpent.h ./src/core/Terrain.h ./src/core/Point.h
	$(CC) $(FLAGS) -c $< -o $@

./obj/Mur.o: ./src/core/Mur.cpp ./src/core/Mur.h ./src/core/Terrain.h ./src/core/Point.h
	$(CC) $(FLAGS) -c $< -o $@

./obj/Terrain.o: ./src/core/Terrain.cpp ./src/core/Terrain.h ./src/core/Point.h
	$(CC) $(FLAGS) -c $< -o $@

./obj/Point.o: ./src/core/Point.cpp ./src/core/Point.h 
	$(CC) $(FLAGS) -c $< -o $@

./obj/mainTestRegression.o: ./src/core/mainTestRegression.cpp ./src/core/Terrain.h ./src/core/Serpent.h 
	$(CC) $(FLAGS) -c $< -o $@	

./obj/mainAffiche.o: ./src/core/mainAffiche.cpp ./src/core/Terrain.h
	$(CC) $(FLAGS) -c $< -o $@

./obj/Jeu.o: ./src/core/Jeu.cpp ./src/core/Jeu.h ./src/core/Terrain.h ./src/core/Serpent.h ./src/core/Portail.h ./src/core/Mur.h ./src/core/Bonus.h
	$(CC) $(FLAGS) -c $< -o $@

./obj/TxtFenetre.o: ./src/txt/TxtFenetre.cpp ./src/txt/TxtFenetre.h
	$(CC) $(FLAGS) -c $< -o $@

./obj/TxtJeu.o: ./src/txt/TxtJeu.cpp ./src/txt/TxtJeu.h ./src/txt/TxtFenetre.h ./src/core/Jeu.h
	$(CC) $(FLAGS) -c $< -o $@

./obj/mainTxt.o: ./src/txt/mainTxt.cpp ./src/txt/TxtFenetre.cpp ./src/txt/TxtFenetre.h ./src/txt/TxtJeu.h
	$(CC) $(FLAGS) -c $< -o $@

docu: doc/nibble.doxy
	cd doc ; doxygen nibble.doxy

clean: 
	rm -rf ./obj/* ./bin/*





