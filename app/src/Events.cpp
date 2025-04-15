#include "headers/Events.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_video.h>

#include <cmath>
#include <iostream>

#include "headers/Game.h"
#include "headers/Renderer.h"

bool Events::loop() {
    while (SDL_PollEvent(&m_sdlEvent)) {
        switch (m_sdlEvent.type) {
            case SDL_EVENT_QUIT:
                return false;
                break;
            case SDL_EVENT_KEY_DOWN:
                // keyevents
                keydownEvents();
                break;
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
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
    switch (m_sdlEvent.key.key) {
        case SDLK_W:
            m_game.moveObject(mainObj, Vector2(0, 1000));
            break;
        case SDLK_D:
            m_game.moveObject(mainObj, Vector2(1000, 0));
            break;
        case SDLK_A:
            m_game.moveObject(mainObj, Vector2(-1000, 0));
            break;
        case SDLK_S:
            m_game.moveObject(mainObj, Vector2(0, -1000));
            break;
        case SDLK_SPACE:
            // stop button
            m_game.stopObject(mainObj);
            break;
        case SDLK_R:
            // reset button
            m_game.deleteAllObjects();
            m_game.moveObjectTo(mainObj, Vector2(500, 250));
            m_game.stopObject(mainObj);
            break;
        case SDLK_F:
            // rotate button
            m_game.rotateObject(mainObj, M_PI / 2);
            std::cout << "----------------------------------------------------------------------------\n";
            break;
    }
}

void Events::mouseButtonUpEvents() {
    float mx = m_sdlEvent.button.x;
    float my = m_sdlEvent.button.y;
    SDL_FColor color = {0, 0, 255, 1};
    switch (m_sdlEvent.button.button) {
        case SDL_BUTTON_LEFT:
            createRectOnMousePos(mx, my, 10, 50, 50, color);
            break;
        case SDL_BUTTON_RIGHT:
            createRectOnMousePos(mx, my, 2, 10, 10);
            break;
    }
}

void Events::createRectOnMousePos(float mx, float my, float m, float width, float height, SDL_FColor color) {
    // doing this cause createRect does same thing to reverse the y axis
    my = m_sdl.renderer.getWindowHeight() - my;
    m_game.createRect(mx, my, m, width, height, color, 0);
}
