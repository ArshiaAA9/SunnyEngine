#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>

#include <iostream>
#include <unordered_map>

#include "../../../engine/src/headers/Physics.h"

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

    void update(PhysicsWorld& world);

    // interfaces:
    // adds pairs to a map {const object*: SDL_Color}
    void addRenderPair(const Object*, SDL_Color color);

    SDL_Window* getWindow() const;
    SDL_Renderer* getRenderer() const;
    int getWindowWidth() const;
    int getWindowHeight() const;

private:
    // clears screen to white
    void clearScreen();

    // used to draw filled rects
    void drawColoredRect(const Object* object, SDL_Color color);

    // initializes everything and creates window and renderer
    bool initWindowAndRenderer();

    std::unordered_map<const Object*, SDL_Color> m_renderMap;
    int m_windowWidth, m_windowHeight;
    SDL_Renderer* m_renderer;
    SDL_Window* m_window;
};
