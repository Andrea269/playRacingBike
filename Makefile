# Project: playRacingBike

CPP  = g++
CC   = gcc
BIN  = playRacingBike

OBJ  = main.o Bike/bike.o Mesh/mesh.o Camera/camera.o Menu/menu.o Coin/coin.o Track/track.o
LINKOBJ  = main.o Bike/bike.o Mesh/mesh.o Camera/camera.o Menu/menu.o Coin/coin.o Track/track.o

# Library linking
OS := $(shell uname)
ifeq ($(OS),Darwin)
## caso Mac OS
$(info Mac OS detected)
FRMPATH=-F /Library/Frameworks
LIBS =  -framework OpenGL -framework SDL2 -lm
$(info SDL2 libraries must be in: $(FRMPATH))
else
ifeq ($(OS),MINGW32_NT-6.1)
## caso Windows MinGW
$(info Windows MinGW detected)
FRMPATH = -IC:\MinGW\include
LIBS = -LC:\MinGW\lib -lmingw32 -lSDL2main -lSDL2 -lopengl32 -lglu32 -lm
else
##caso Linux
$(info Linux detected)
#framework presenti solo nel caso MAC OS
FRMPATH =
LIBS = -lGL -lGLU -lSDL2 -lSDL2_image -lSDL2_ttf -lm
endif
endif

RM = rm -f

all: $(BIN)

clean:
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o $(BIN) $(FRMPATH) $(LIBS)

main.o: main.cpp
	$(CPP) -c -Wno-deprecated $(FRMPATH) main.cpp -o main.o

Bike/bike.o: Bike/bike.cpp
	$(CPP) -c -Wno-deprecated $(FRMPATH) Bike/bike.cpp -o Bike/bike.o

Mesh/mesh.o: Mesh/mesh.cpp
	$(CPP) -c -Wno-deprecated $(FRMPATH) Mesh/mesh.cpp -o Mesh/mesh.o

Camera/camera.o: Camera/camera.cpp
	$(CPP) -c -Wno-deprecated $(FRMPATH) Camera/camera.cpp -o Camera/camera.o

Menu/menu.o: Menu/menu.cpp
	$(CPP) -c -Wno-deprecated $(FRMPATH) Menu/menu.cpp -o Menu/menu.o

Coin/coin.o: Coin/coin.cpp
	$(CPP) -c -Wno-deprecated $(FRMPATH) Coin/coin.cpp -o Coin/coin.o

Track/track.o: Track/track.cpp
	$(CPP) -c -Wno-deprecated $(FRMPATH) Track/track.cpp -o Track/track.o