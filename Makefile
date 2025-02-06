all: clean build run

build:
	g++ main.cpp -o PhysicsEngine

run:
	./PhysicsEngine

clean:
	rm -f PhysicsEngine
