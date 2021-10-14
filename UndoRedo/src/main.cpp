#include <iostream>

#include "../include/Game.h"
#include "../include/LegoFactory.h"
#include "../include/ClayFactory.h"
#include "../include/ConcreteFactory.h"

void drawBricks(Brick* m_brick)
{
    m_brick->draw();
}

void createBricks()
{
    Factory* factory = new LegoFactory();
    Brick* brick = factory->getBricks();
    drawBricks(brick);
    factory = new ClayFactory();
    brick = factory->getBricks();
    drawBricks(brick);
    factory = new ConcreteFactory();
    brick = factory->getBricks();
    drawBricks(brick);
}

int main(int argc, char** argv)
{
    createBricks();

    Game *game = new Game();

    while(game->isRunning())
    {
        game->handleEvents();
        game->update();
        game->render();
    }

    std::cin.get();
    return 0;
}