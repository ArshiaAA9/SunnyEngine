#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3_ttf/SDL_ttf.h>

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
    void addRenderPair(ObjectPtr, SDL_Color color);
    // removes a pair from the map
    void deleteRenderPair(ObjectPtr);
    // returns a contsant reference to renderMap
    const std::unordered_map<ObjectPtr, SDL_Color>& getRenderMap(); // stores objects with a corresponding color

    SDL_Window* getWindow() const;
    SDL_Renderer* getRenderer() const;
    int getWindowWidth() const;
    int getWindowHeight() const;
    TTF_Font* getFont() const;

private:
    // clears screen to white
    void clearScreen();

    // used to draw filled rects
    void drawColoredRect(const ObjectPtr object, SDL_Color color);

    // used to show the living objects count in the simulation
    void renderObjectCount(int count);

    // initializes everything and member vars
    bool initWindowAndRenderer();

    std::unordered_map<ObjectPtr, SDL_Color> m_renderMap; // stores objects with a corresponding color

    int m_windowWidth, m_windowHeight; // window width, height
    SDL_Window* m_window;              // window
    SDL_Renderer* m_renderer;          // renderer
    TTF_Font* m_font;                  // font
    SDL_Surface* m_text;               // font surface
    SDL_Color m_textColor;             // text color
    SDL_Texture* m_textTexture;        // text texture
};
