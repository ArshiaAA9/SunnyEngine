#include "headers/Renderer.h"

#include <SDL2/SDL_render.h>

#include <iostream>

// public:

SDL_Window* Renderer::getWindow() { return m_window; }

SDL_Renderer* Renderer::getRenderer() { return m_renderer; }

// private:
bool Renderer::initWindowAndRenderer() {
    // initializing everything
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "Error initializing SDL " << SDL_GetError() << std::endl;
        return false;
    }

    // create window
    m_window = SDL_CreateWindow(
        "Physics Simulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight,
        SDL_WINDOW_SHOWN);
    if (!m_window) {
        std::cout << "Error creating window: " << SDL_GetError() << std::endl;
        return false;
    }

    // create renderer
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if (!m_renderer) {
        std::cout << "Error creating renderer: " << SDL_GetError() << std::endl;
        return false;
    }
    // set renderer color and clear window
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_RenderClear(m_renderer);
    return true;
}
