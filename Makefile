EXECUTABLE := game

SOURCES := main.cpp Dot.cpp menu.cpp music.cpp Enemy.cpp

CXXFLAGS := -Wall -Wextra -std=c++11

LIBS := -lSDL2 -lSDL2main -lSDL2_mixer -lSDL2_ttf -lSDL2_image

ifeq ($(shell uname), Darwin)
    SDL2_CONFIG := sdl2-config --cflags --libs
else 
    SDL2_CONFIG := sdl2-config --cflags --libs 
endif

CXX := g++

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CXX) $(CXXFLAGS) $^ -o $@ `$($(SDL2_CONFIG))` $(LIBS)

clean:
	-rm -f $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

rebuild: clean all
