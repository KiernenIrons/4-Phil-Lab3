#pragma once
#include <iostream>
#include "../include/Brick.h"

class ConcreteBrick : public Brick
{
public:
    ConcreteBrick(){};
    virtual ~ConcreteBrick(){};
    virtual void draw(){ std::cout << "New Concrete Brick" << std::endl; };
};