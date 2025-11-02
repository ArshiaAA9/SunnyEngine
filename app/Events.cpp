#include "Events.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_video.h>

#include <iostream>

#include "Game.h"
#include "Physics.h"
#include "Renderer.h"

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
        std::cout << " mainObject has not been set ";
        return; // Early exit if no main object
    }
    int forceAmount = 1000;
    switch (m_sdlEvent.key.key) {
        case SDLK_W:
            m_game.moveObject(mainObj, Vector2(0, forceAmount));
            break;
        case SDLK_D:
            m_game.moveObject(mainObj, Vector2(forceAmount, 0));
            break;
        case SDLK_A:
            m_game.moveObject(mainObj, Vector2(-forceAmount, 0));
            break;
        case SDLK_S:
            m_game.moveObject(mainObj, Vector2(0, -forceAmount));
            break;
        case SDLK_SPACE:
            // stop button
            m_game.stopObject(mainObj);
            break;
        case SDLK_R:
            m_game.spinObject(mainObj, M_PI);
            break;
        case SDLK_F:
            // rotate button
            m_game.rotateObject(mainObj, M_PI / 4);
            break;
    }
}

void Events::mouseButtonUpEvents() {
    float mx = m_sdlEvent.button.x;
    float my = m_sdlEvent.button.y;
    SDL_FColor rColor = {0, 0, 255, 255};
    SDL_FColor cColor = {255, 0, 0, 255};
    switch (m_sdlEvent.button.button) {
        case SDL_BUTTON_LEFT:
            createRectOnMousePos(mx, my, 3, 50, 50, rColor);
            break;
        case SDL_BUTTON_RIGHT:
            my = m_sdl.renderer.getWindowHeight() - my;
            m_game.createCircle(mx, my, 1, 20, cColor, 0, 1);
            break;
    }
}

void Events::createRectOnMousePos(float mx, float my, float m, float width, float height, SDL_FColor color) {
    // reversing the y axis
    my = m_sdl.renderer.getWindowHeight() - my;
    m_game.createRect(mx, my, m, width, height, color, 0, 1.0f);
}
