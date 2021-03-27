# FLAGS =-Wall -g
# CC = g++ 
# OBJS = ./obj/Terrain.o ./obj/Serpent.o  ./obj/Point.o ./obj/Jeu.o ./obj/TxtFenetre.o ./obj/TxtJeu.o #./obj/Bonus.o ./obj/Mur.o
# EXE1 = ./bin/afficheTerrain
# EXE2 = ./bin/test
# EXE3 = ./bin/jeuTxt


# all: $(EXE1) $(EXE2)

# jeuTxt: $(EXE3)

# $(EXE1): ./obj/Terrain.o ./obj/mainAffiche.o ./obj/Point.o
# 	$(CC) -g ./obj/mainAffiche.o ./obj/Point.o ./obj/Terrain.o -o $(EXE1)

# $(EXE2): ./obj/Serpent.o ./obj/mainTestRegression.o ./obj/Point.o ./obj/Terrain.o
# 	$(CC) -g ./obj/Terrain.o ./obj/mainTestRegression.o ./obj/Point.o ./obj/Serpent.o -o $(EXE2)
	
# $(EXE3): $(OBJS)
# 	$(CC) -g $(OBJS) -o $(EXE3)

# ./obj/Bonus.o: ./src/Bonus.h ./src/Bonus.cpp ./src/Serpent.h ./src/Point.h
# 	$(CC) $(FLAGS) -c ./src/Bonus.cpp -o ./obj/Bonus.o

# ./obj/Serpent.o: ./src/Serpent.h ./src/Serpent.cpp ./src/Terrain.h ./src/Point.h
# 	$(CC) $(FLAGS) -c ./src/Serpent.cpp -o ./obj/Serpent.o

# ./obj/Mur.o: ./src/Mur.h ./src/Mur.cpp ./src/Terrain.h ./src/Point.h
# 	$(CC) $(FLAGS) -c  ./src/Mur.cpp -o ./obj/Mur.o

# ./obj/Terrain.o: ./src/Terrain.h ./src/Terrain.cpp ./src/Point.h
# 	$(CC) $(FLAGS) -c ./src/Terrain.cpp -o ./obj/Terrain.o

# ./obj/Point.o: ./src/Point.h ./src/Point.cpp
# 	$(CC) $(FLAGS) -c ./src/Point.cpp -o ./obj/Point.o

# ./obj/mainTestRegression.o: ./src/Terrain.h ./src/Serpent.h ./src/mainTestRegression.cpp
# 	$(CC) $(FLAGS) -c ./src/mainTestRegression.cpp -o ./obj/mainTestRegression.o	

# ./obj/mainAffiche.o: ./src/mainAffiche.cpp ./src/Terrain.h
# 	$(CC) $(FLAGS) -c ./src/mainAffiche.cpp -o ./obj/mainAffiche.o

# ./obj/Jeu.o: ./src/Jeu.cpp ./src/Jeu.h ./src/Terrain.h ./src/Serpent.h ./src/Portail.h ./src/Mur.h ./src/Bonus.h
# 	$(CC) $(FLAGS) -c ./src/Jeu.cpp -o ./obj/Jeu.o

# ./obj/TxtFenetre.o: ./src/TxtFenetre.cpp ./src/TxtFenetre.h
# 	$(CC) $(FLAGS) -c ./src/TxtFenetre.cpp -o ./obj/TxtFenetre.o

# ./obj/TxtJeu.o: ./src/TxtJeu.h ./src/TxtJeu.cpp ./src/TxtFenetre.h ./src/Jeu.h
# 	$(CC) $(FLAGS) -c ./src/TxtJeu.cpp -o ./obj/TxtJeu.o

# clean: 
# 	rm -rf ./obj/* ./bin/*

CORE = src/Serpent.cpp src/Terrain.cpp src/Jeu.cpp 

SRCS_TXT = $(CORE) src/txtJeu.cpp src/TxtFenetre.cpp src/main_txt.cpp
FINAL_TARGET_TXT = pacman_txt
#DEFINE_TXT = -DJEU_TXT

SRCS_SDL = $(CORE) sdl2/sdlJeu.cpp sdl2/main_sdl.cpp
FINAL_TARGET_SDL = pacman_sdl
#DEFINE_SDL = -DJEU_SDL

ifeq ($(OS),Windows_NT)
	INCLUDE_DIR_SDL = 	-Iextern/SDL2_mingw-cb20/SDL2-2.0.12/x86_64-w64-mingw32/include/SDL2 \
						-Iextern/SDL2_mingw-cb20/SDL2_ttf-2.0.15/x86_64-w64-mingw32/include/SDL2 \
						-Iextern/SDL2_mingw-cb20/SDL2_image-2.0.5/x86_64-w64-mingw32/include/SDL2 \
						-Iextern/SDL2_mingw-cb20/SDL2_mixer-2.0.4/x86_64-w64-mingw32/include/SDL2

	LIBS_SDL = -Lextern \
			-Lextern/SDL2_mingw-cb20/SDL2-2.0.12/x86_64-w64-mingw32/lib \
			-Lextern/SDL2_mingw-cb20/SDL2_ttf-2.0.15/x86_64-w64-mingw32/lib \
			-Lextern/SDL2_mingw-cb20/SDL2_image-2.0.5/x86_64-w64-mingw32/lib \
			-Lextern/SDL2_mingw-cb20/SDL2_mixer-2.0.4/x86_64-w64-mingw32/lib \
			-lmingw32 -lSDL2main -lSDL2.dll -lSDL2_ttf.dll -lSDL2_image.dll -lSDL2_mixer.dll

else
	INCLUDE_DIR_SDL = -I/usr/include/SDL2
	LIBS_SDL = -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer
endif

CC					= g++
LD 					= g++
LDFLAGS  			=
CPPFLAGS 			= -Wall -ggdb   #-O2   # pour optimiser
OBJ_DIR 			= obj
SRC_DIR 			= src
BIN_DIR 			= bin
INCLUDE_DIR			= -Isrc -Isrc/core -Isrc/sdl2 -Itxt

default: make_dir $(BIN_DIR)/$(FINAL_TARGET_TXT) $(BIN_DIR)/$(FINAL_TARGET_SDL)

make_dir:
ifeq ($(OS),Windows_NT)
	if not exist $(OBJ_DIR) mkdir $(OBJ_DIR) $(OBJ_DIR)\txt $(OBJ_DIR)\sdl2 $(OBJ_DIR)\core $(OBJ_DIR)\qt
else
	test -d $(OBJ_DIR) || mkdir -p $(OBJ_DIR) $(OBJ_DIR)/txt $(OBJ_DIR)/sdl2 $(OBJ_DIR)/core
endif

$(BIN_DIR)/$(FINAL_TARGET_TXT): $(SRCS_TXT:%.cpp=$(OBJ_DIR)/%.o)
	$(LD) $+ -o $@ $(LDFLAGS)

$(BIN_DIR)/$(FINAL_TARGET_SDL): $(SRCS_SDL:%.cpp=$(OBJ_DIR)/%.o)
	$(LD) $+ -o $@ $(LDFLAGS) $(LIBS_SDL)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -c $(CPPFLAGS) $(INCLUDE_DIR_SDL) $(INCLUDE_DIR) $< -o $@

docu: doc/pacman.doxy
	cd doc ; doxygen pacman.doxy

clean:
ifeq ($(OS),Windows_NT)
	del /f $(OBJ_DIR)\txt\*.o $(OBJ_DIR)\sdl2\*.o $(OBJ_DIR)\core\*.o $(BIN_DIR)\$(FINAL_TARGET_TXT).exe $(BIN_DIR)\$(FINAL_TARGET_SDL).exe
else
	rm -rf $(OBJ_DIR) $(BIN_DIR)/$(FINAL_TARGET_TXT) $(BIN_DIR)/$(FINAL_TARGET_SDL) doc/html
endif

