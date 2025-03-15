#include "headers/Events.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_video.h>

#include <iostream>

bool Events::loop() {
    while (SDL_PollEvent(&m_sdlEvent) != 0) {
        switch (m_sdlEvent.type) {
        case SDL_QUIT:
            return false;
        case SDL_KEYDOWN:
            switch (m_sdlEvent.key.keysym.sym) {
            case SDLK_w:
                std::cout << "w was pressed";
                break;
            case SDLK_e:
                std::cout << "e was pressed ";
                break;
            }
            // keyevents
        }
    }
    return true;
}

// interfaces:
SDL_Event& Events::getEventVar() { return m_sdlEvent; }
