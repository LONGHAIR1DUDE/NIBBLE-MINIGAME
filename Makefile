FLAGS =-Wall -g
CC = g++ 
OBJTXT = ./obj/Terrain.o ./obj/Serpent.o  ./obj/Point.o ./obj/Jeu.o ./obj/TxtFenetre.o ./obj/TxtJeu.o ./obj/Bonus.o ./obj/Mur.o ./obj/mainTxt.o ./obj/Portail.o ./obj/Rect.o
OBJSDL2 = ./obj/Terrain.o ./obj/Serpent.o  ./obj/Point.o ./obj/Jeu.o ./obj/TxtFenetre.o ./obj/TxtJeu.o ./obj/Bonus.o ./obj/Mur.o ./obj/mainSdl2.o ./obj/Portail.o ./obj/Rect.o ./obj/SdlJeu.o
CORE = ./src/core
TXT = ./src/txt
SDL2 = ./src/sdl2

EXE1 = ./bin/afficheTerrain
EXE2 = ./bin/test
EXE3 = ./bin/nibble_txt
EXE4 = ./bin/nibble_sdl2

all: $(EXE1) $(EXE2) $(EXE3) $(EXE4)

jeuTxt: $(EXE3)

jeuSdl2: $(EXE4)

$(EXE1): ./obj/Terrain.o ./obj/mainAffiche.o ./obj/Point.o ./obj/Rect.o ./obj/Mur.o
	$(CC) -g $^ -o $@

$(EXE2): ./obj/Serpent.o ./obj/mainTestRegression.o ./obj/Point.o ./obj/Terrain.o ./obj/Rect.o ./obj/Mur.o
	$(CC) -g $^ -o $@
	
$(EXE3): $(OBJTXT)
	$(CC) -g $^ -o $@

$(EXE4): $(OBJSDL2) 
	$(CC) -g $^ -o $@ -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2

./obj/Bonus.o: $(CORE)/Bonus.cpp $(CORE)/Bonus.h $(CORE)/Serpent.h $(CORE)/Point.h
	$(CC) $(FLAGS) -c $< -o $@ 

./obj/Serpent.o: $(CORE)/Serpent.cpp $(CORE)/Serpent.h $(CORE)/Terrain.h $(CORE)/Point.h
	$(CC) $(FLAGS) -c $< -o $@

./obj/Mur.o: $(CORE)/Mur.cpp $(CORE)/Mur.h $(CORE)/Terrain.h $(CORE)/Point.h $(CORE)/Rect.h
	$(CC) $(FLAGS) -c $< -o $@

./obj/Terrain.o: $(CORE)/Terrain.cpp $(CORE)/Terrain.h $(CORE)/Point.h $(CORE)/Rect.h $(CORE)/Mur.h
	$(CC) $(FLAGS) -c $< -o $@

./obj/Point.o: $(CORE)/Point.cpp $(CORE)/Point.h 
	$(CC) $(FLAGS) -c $< -o $@

./obj/Rect.o: $(CORE)/Rect.cpp $(CORE)/Rect.h
	$(CC) $(FLAGS) -c $< -o $@

./obj/Portail.o: $(CORE)/Portail.cpp $(CORE)/Portail.h $(CORE)/Terrain.h
	$(CC) $(FLAGS) -c $< -o $@

./obj/mainTestRegression.o: $(CORE)/mainTestRegression.cpp $(CORE)/Terrain.h $(CORE)/Serpent.h $(CORE)/Bonus.h $(CORE)/Point.h $(CORE)/Rect.h $(CORE)/Portail.h $(CORE)/Mur.h $(CORE)/Jeu.h   
	$(CC) $(FLAGS) -c $< -o $@	

./obj/mainAffiche.o: $(CORE)/mainAffiche.cpp $(CORE)/Terrain.h
	$(CC) $(FLAGS) -c $< -o $@

./obj/Jeu.o: $(CORE)/Jeu.cpp $(CORE)/Jeu.h $(CORE)/Terrain.h $(CORE)/Serpent.h $(CORE)/Portail.h $(CORE)/Mur.h $(CORE)/Bonus.h
	$(CC) $(FLAGS) -c $< -o $@

./obj/TxtFenetre.o: $(TXT)/TxtFenetre.cpp $(TXT)/TxtFenetre.h
	$(CC) $(FLAGS) -c $< -o $@

./obj/TxtJeu.o: $(TXT)/TxtJeu.cpp $(TXT)/TxtJeu.h $(TXT)/TxtFenetre.h $(CORE)/Jeu.h
	$(CC) $(FLAGS) -c $< -o $@

./obj/mainTxt.o: $(TXT)/mainTxt.cpp $(TXT)/TxtFenetre.cpp $(TXT)/TxtJeu.h
	$(CC) $(FLAGS) -c $< -o $@

./obj/SdlJeu.o: $(SDL2)/SdlJeu.cpp $(SDL2)/SdlJeu.h $(CORE)/Jeu.h
	$(CC) $(FLAGS) -c $< -o $@

./obj/mainSdl2.o: $(SDL2)/mainSdl2.cpp $(SDL2)/SdlJeu.h
	$(CC) $(FLAGS) -c $< -o $@

docu: Doxyfile
	doxygen Doxyfile

clean: 
	rm -rf ./obj/* ./bin/*





