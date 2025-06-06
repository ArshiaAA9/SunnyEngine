# SunnyEngine

SunnyEngine is a simple personal 2D physics engine project, written in c++.

Currently only supports rigid and fully elastic bodies.

Only tested on arch linux so far so other operating systems might requier additional setup.

## Requirements 
Requires SDl3, sdl3-ttf, gcc and make to be installed. 

## Installation

Building and Installing
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
```bash
cmake --install build --prefix ~/.local #local installation (recommneded)
sudo cmake --install build #system-wide installtion
```

Run the Simulation:
```bash
cd ./bin/Simulation
```

## Controls
Move the main object: **W, A, S, D**

Stop the main object: **SPACE**

Delete all objects except the main object: **R**

Spawn a rectangle object: **LMB**

Spawn a circle object: **RMB**
