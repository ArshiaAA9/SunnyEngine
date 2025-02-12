all: clean build run

build:
	g++ src/main.cpp src/vector2.cpp -o bin/binary `sdl2-config --cflags --libs`

run:
	./bin/binary

clean:
	rm -f bin/binary