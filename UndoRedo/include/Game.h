#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "Globals.h"
#include "Button.h"
#include "Command.h"

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
    SDL_Renderer* m_renderer = nullptr;
    SDL_Event e;

    std::vector<Button*> m_buttons;
    TTF_Font* m_font = nullptr;

    bool run = true;
};