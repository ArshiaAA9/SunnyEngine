#include "headers/Sdl.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

void Sdl::kill() {
    // quit
    SDL_Window* sdlWindow = renderer.getWindow();
    SDL_Renderer* sdlRenderer = renderer.getRenderer();
    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(sdlWindow);

    sdlWindow = nullptr;
    sdlRenderer = nullptr;

    SDL_Quit();
}
