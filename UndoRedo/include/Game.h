#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include "Globals.h"

class Game
{
public:
    Game();
    bool isRunning();
    void handleEvents();
    void update();
    void render();
    void cleanup();
private:

    SDL_Window* window = nullptr;
    SDL_Surface* screenSurface = nullptr;
    SDL_Event e;

    bool run = true;
};