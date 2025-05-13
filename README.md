# SunnyEngine

SunnyEngine is a simple personal 2D physics engine project, written in c++ with sdl.

Currently only supports rigid and fully elastic bodies.

## Requirements 
Requires SDl3, sdl3-ttf, gcc and make to be installed. 

## Installation

###Building and Installing
clone the repo:
```bash
git clone https://github.com/ArshiaAA9/SunnyEngine.git
cd SunnyEngine
```
Build the project:
```bash
cmake -B build
cmake --build build --parallel $(nproc)
```
Do one of the following:
User-local installation (recommended):
```bash
cmake --install build --prefix ~/.local
```
system-wide installation:
```bash
sudo cmake --install build
```
###Running the Simulation

```bash
cd ./bin/Simulation
```

## Controls
Move the main object: **W, A, S, D**

Stop the main object: **SPACE**

Delete all objects except the main object: **R**

Spawn a rectangle object: **LMB**

Spawn a circle object: **RMB**
