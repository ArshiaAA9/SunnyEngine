#pragma once

#include <SDL2/SDL.h>

#include <iostream>

#include "../../../engine/src/headers/Objects.h"

class Sdl;

class Renderer {
public:
    Renderer(int windowWidth, int windowHeight)
        : m_windowWidth(windowWidth)
        , m_windowHeight(windowHeight)
        , m_window(nullptr)
        , m_renderer(nullptr) {
        if (!initWindowAndRenderer()) std::cerr << "Failed to initalize everything";
    }

    void clearScreen();

    void drawColoredRect(const Object& object, int r, int g, int b, float a);

    void update();

    // interfaces:
    SDL_Window* getWindow();
    SDL_Renderer* getRenderer();

private:
    // initializes everything and creates window and renderer
    bool initWindowAndRenderer();

    int m_windowWidth, m_windowHeight;
    SDL_Renderer* m_renderer;
    SDL_Window* m_window;
};
