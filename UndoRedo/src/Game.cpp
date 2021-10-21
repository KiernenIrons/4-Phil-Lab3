#include "../include/game.h"

Game::Game()
{

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not be initialised. Error: " << SDL_GetError();
    }
    else
    {
        window = SDL_CreateWindow("SDL_Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        m_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        if(window == nullptr)
        {
            std::cout << "Failed to create window. Error: " << SDL_GetError();
        }
        else
        {
            screenSurface = SDL_GetWindowSurface(window);

        }
    }

    m_font = TTF_OpenFont("assets/fonts/04B_30__.TTF", 24);

    m_buttons.push_back(new Button(50, 50, m_font, "Lego Brick", new BuildLego(), m_renderer));
}

bool Game::isRunning()
{
    return run;
}

void Game::handleEvents()
{
    while(SDL_PollEvent(&e)){
        switch(e.type){
            case SDL_QUIT:
                run = false;
                break;
        }
    }
}

void Game::update()
{

}

void Game::render()
{
    SDL_RenderClear(m_renderer);
    SDL_SetRenderDrawColor(m_renderer, 0,0,0,255);
    for(Button* button : m_buttons)
    {
        button->draw();
    }
    SDL_SetRenderDrawColor(m_renderer, 0,0,0,255);
    SDL_RenderPresent(m_renderer);
}

void Game::cleanup()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}