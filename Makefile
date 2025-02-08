all: clean build run

build:
	g++ main.cpp -o binary `sdl2-config --cflags --libs`

run:
	./binary

clean:
	rm -f binary