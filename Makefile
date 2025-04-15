CXX = g++
CXXFLAGS = -std=c++17 -Iapp/headers -Iengine/headers `pkg-config --cflags sdl3 sdl3-ttf`
LDFLAGS = `pkg-config --libs sdl3 sdl3-ttf`

SRC_APP = $(wildcard app/src/*.cpp)
SRC_ENGINE = $(wildcard engine/src/*.cpp)
ENGINE_OBJ = $(patsubst %.cpp, build/%.o, $(SRC_ENGINE))
ENGINE_LIB = build/libSunnyEngine.a
OBJ = $(patsubst %.cpp, build/%.o, $(SRC_APP) $(SRC_ENGINE))

TARGET = bin/physicsGame

$(ENGINE_LIB): $(ENGINE_OBJ)
	ar rcs $@ $^

all: build run

build: $(TARGET)

$(TARGET): $(OBJ)
	mkdir -p bin
	$(CXX) $^ -o $(TARGET) $(LDFLAGS)

build/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run:
	./$(TARGET)

clean:
	rm -rf build bin/physicsGame

.PHONY: all build run clean
