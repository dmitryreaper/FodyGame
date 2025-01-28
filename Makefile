EXECUTABLE := game

SOURCE := main.cpp

CXXFLAGS := -Wall -Wextra -std=c++11

LIBS := -lSDL2 -lSDL2main

ifeq ($(shell uname), Darwin)
    SDL2_CONFIG := sdl2-config --cflags --libs
else 
    SDL2_CONFIG := sdl2-config --cflags --libs
endif

CXX := g++

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCE)
	$(CXX) $(CXXFLAGS) $^ -o $@ `$($(SDL2_CONFIG))` $(LIBS)

clean:
	rm -f $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

rebuild: clean all
