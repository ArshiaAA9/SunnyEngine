#include "headers/Events.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>

#include <iostream>

#include "headers/Game.h"

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

void Events::keydownEvents() {
    switch (m_sdlEvent.key.keysym.sym) {
    case SDLK_w:
        std::cout << "w was pressed";
        break;
    case SDLK_e:
        std::cout << "e was pressed ";
        break;
    }
}

void Events::mouseButtonUpEvents() {
    int mx = m_sdlEvent.button.x;
    int my = m_sdlEvent.button.y;
    switch (m_sdlEvent.button.button) {
    case SDL_BUTTON_LEFT:

        createRectOnMousePos(mx, my, 10, 50, 50);
        std::cout << " left button pressed ";
        break;
    case SDL_BUTTON_RIGHT:
        createRectOnMousePos(mx, my, 2, 10, 10);
        std::cout << " mouse cord: " << mx << ',' << my << '\n';
        break;
    }
}

void Events::createRectOnMousePos(int mx, int my, float m, float width, float height) {
    // doing this cause createRect does same thing to reverse the y axis
    my = m_sdl.renderer.getWindowHeight() - my;
    SDL_Color color = {255, 0, 0, 1};
    m_game.createRect(mx, my, m, width, height, color);
}

// interfaces:
SDL_Event& Events::getEventVar() { return m_sdlEvent; }
