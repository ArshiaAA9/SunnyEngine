#include "headers/Events.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>

#include <cmath>
#include <iostream>

#include "headers/Game.h"
#include "headers/Renderer.h"

bool Events::loop() {
    while (SDL_PollEvent(&m_sdlEvent) != 0) {
        switch (m_sdlEvent.type) {
            case SDL_QUIT:
                return false;
                break;
            case SDL_KEYDOWN:
                // keyevents
                keydownEvents();
                break;
            case SDL_MOUSEBUTTONUP:
                mouseButtonUpEvents();
                break;
        }
    }
    return true;
}

// interfaces:
SDL_Event& Events::getEventVar() { return m_sdlEvent; }

void Events::keydownEvents() {
    ObjectPtr mainObj = m_game.getMainObject(); // Get main object once
    if (!mainObj) {
        std::cout << " mainObject hasnt been set ";
        return; // Early exit if no main object
    }
    switch (m_sdlEvent.key.keysym.sym) {
        case SDLK_w:
            m_game.moveObject(mainObj, Vector2(0, 1000));
            std::cout << "w pressed ";
            break;
        case SDLK_d:
            m_game.moveObject(mainObj, Vector2(1000, 0));
            std::cout << "d pressed ";
            break;
        case SDLK_a:
            m_game.moveObject(mainObj, Vector2(-1000, 0));
            std::cout << "a pressed ";
            break;
        case SDLK_s:
            m_game.moveObject(mainObj, Vector2(0, -1000));
            std::cout << "s pressed ";
            break;
        case SDLK_SPACE:
            m_game.stopObject(mainObj);
            std::cout << "space pressed ";
            break;
        case SDLK_r:
            m_game.moveObjectTo(mainObj, Vector2(500, 250));
            m_game.stopObject(mainObj);
            break;
        case SDLK_f:
            m_game.deleteAllObjects();
            break;
    }
}

void Events::mouseButtonUpEvents() {
    int mx = m_sdlEvent.button.x;
    int my = m_sdlEvent.button.y;
    SDL_Color color = {0, 0, 255, 1};
    switch (m_sdlEvent.button.button) {
        case SDL_BUTTON_LEFT:
            createRectOnMousePos(mx, my, 10, 50, 50, color);
            break;
        case SDL_BUTTON_RIGHT:
            createRectOnMousePos(mx, my, 2, 10, 10);
            break;
    }
}

void Events::createRectOnMousePos(int mx, int my, float m, float width, float height, SDL_Color color) {
    // doing this cause createRect does same thing to reverse the y axis
    my = m_sdl.renderer.getWindowHeight() - my;
    m_game.createRect(mx, my, m, width, height, color);
}
