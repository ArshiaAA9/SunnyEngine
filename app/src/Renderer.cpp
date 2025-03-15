#include "headers/Renderer.h"

#include <SDL2/SDL_render.h>

#include <iostream>

// public:
void Renderer::clearScreen() {
    // Clear the screen at the beginning of the frame
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255); // White background
    SDL_RenderClear(m_renderer);
}

void Renderer::drawColoredRect(const Object& object, int r, int g, int b, float a) {
    SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
    // sdl_rect takes position as topleft point of rect
    float width = object.getDimensions().x;
    float height = object.getDimensions().y;
    Vector2 pos = object.transform.position;
    SDL_Rect rect;
    rect.x = pos.x - width / 2;
    rect.y = m_windowHeight - pos.y - height / 2;
    rect.w = width;
    rect.h = height;
    SDL_RenderFillRect(m_renderer, &rect);
}

void Renderer::update() { SDL_RenderPresent(m_renderer); }

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
        "Physics Simulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_windowWidth,
        m_windowHeight, SDL_WINDOW_SHOWN);
    if (!m_window) {
        std::cerr << "Error creating window: " << SDL_GetError() << std::endl;
        return false;
    }

    // create renderer
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if (!m_renderer) {
        std::cerr << "Error creating renderer: " << SDL_GetError() << std::endl;
        return false;
    }
    // set renderer color and clear window
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_RenderClear(m_renderer);
    return true;
}
