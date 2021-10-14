#pragma once
#include <iostream>
#include "../include/Brick.h"

class ClayBrick : public Brick
{
public:
    ClayBrick(){};
    virtual ~ClayBrick(){};
    virtual void draw(){ std::cout << "New Clay Brick" << std::endl; };
};