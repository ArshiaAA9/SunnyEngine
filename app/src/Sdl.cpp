#include "headers/Sdl.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>

void Sdl::kill() {
    // quit
    SDL_Window* sdlWindow = renderer.getWindow();
    SDL_Renderer* sdlRenderer = renderer.getRenderer();
    TTF_Font* sdlFont = renderer.getFont();
    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(sdlWindow);
    TTF_CloseFont(sdlFont);

    sdlWindow = nullptr;
    sdlRenderer = nullptr;
    sdlFont = nullptr;

    SDL_Quit();
}
