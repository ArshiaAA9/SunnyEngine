SOURCES = $(wildcard src/*.cpp)
INCLUDES = src/headers/

all: clean build run

build:
	g++ src/main.cpp $(SOURCES) -I $(INCLUDES) -o bin/binary `sdl2-config --cflags --libs`

run:
	./bin/binary

clean:
	rm -f bin/binary