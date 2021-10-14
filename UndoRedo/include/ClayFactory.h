#pragma once
#include <iostream>
#include "../include/Factory.h"
#include "../include/ClayBrick.h"

class ClayFactory : public Factory
{
    public:
    ClayFactory(){};
    ~ClayFactory(){};
    Brick* getBricks()
    {
        return new ClayBrick();
    };
};