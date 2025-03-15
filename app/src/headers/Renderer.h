#pragma once

#include <SDL2/SDL.h>

#include <iostream>

class Sdl;

class Renderer {
public:
    Renderer(int windowWidth, int windowHeight)
        : windowWidth(windowWidth)
        , windowHeight(windowHeight)
        , m_window(nullptr)
        , m_renderer(nullptr) {
        if (!initWindowAndRenderer()) std::cerr << "Failed to initalize everything";
    }

    // interfaces:
    SDL_Window* getWindow();
    SDL_Renderer* getRenderer();

private:
    // initializes everything and creates window and renderer
    bool initWindowAndRenderer();

    int windowWidth, windowHeight;
    SDL_Renderer* m_renderer;
    SDL_Window* m_window;
};
