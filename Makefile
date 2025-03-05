# Compiler.
CC= g++

# Libraries and includes.
LINKDIR= -L./dragonfly/lib # path to dragonfly library
INCDIR= -I./dragonfly/include # path to dragonfly includes
SFML_VERSION= 3.0.0

### Uncomment and update below if using local SFML installation.
# LOCALSFML= $(HOME)/src/SFML-$(SFML_VERSION)
# LINKDIR:= $(LINKDIR) -L $(LOCALSFML)/lib
# INCDIR:= $(INCDIR) -I$(LOCALSFML)/include

CFLAGS= -std=c++17

### Uncomment either 1) or 2) below! ###

## 1) For Linux:
#ENG= dragonfly-x64-linux
#CFLAGS:= $(CFLAGS) -Wall
#LINKLIB= -l$(ENG) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lrt

## 2) For Mac:
ENG= dragonfly-arm64-mac
#Note, below is typical directory for homebrew:
LOCALSFML= /opt/homebrew/Cellar/sfml/$(SFML_VERSION)
CFLAGS+= -MD # generate depenency files
LINKLIB= -l$(ENG) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio 
LINKDIR:= $(LINKDIR) -L $(LOCALSFML)/lib
INCDIR:= $(INCDIR) -I$(LOCALSFML)/include
######

GAMESRC= \
        GroundTile.cpp \
        GameStart.cpp \
        Runner.cpp \
        Points.cpp \
        Boulder.cpp \
        Panther.cpp \
        GameOver.cpp \
        Spawning.cpp \
        Vulture.cpp \
        Reticle.cpp \
        Bullet.cpp \
        Tree.cpp \
        Sun.cpp \



GAME= game.cpp
EXECUTABLE= game
OBJECTS= $(GAMESRC:.cpp=.o)

.PHONY: all clean

all: $(EXECUTABLE) Makefile

$(EXECUTABLE): $(OBJECTS) $(GAME) $(GAMESRC) 
	$(CC) $(CFLAGS) $(GAME) $(OBJECTS) -o $@ $(INCDIR) $(LINKDIR) $(LINKLIB) 

.cpp.o: 
	$(CC) $(CFLAGS) -c $< -o $@ $(INCDIR)

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) core dragonfly.log Makefile.bak *~
# DO NOT DELETE
