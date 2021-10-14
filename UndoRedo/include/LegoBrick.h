#pragma once
#include <iostream>
#include "../include/Brick.h"

class LegoBrick : public Brick
{
public:
    LegoBrick(){};
    virtual ~LegoBrick(){};
    virtual void draw(){ std::cout << "New Lego Brick" << std::endl; };
};