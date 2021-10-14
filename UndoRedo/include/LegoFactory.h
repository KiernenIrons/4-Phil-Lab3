#pragma once
#include <iostream>
#include "../include/Factory.h"
#include "../include/LegoBrick.h"

class LegoFactory : public Factory
{
    public:
    LegoFactory(){};
    ~LegoFactory(){};
    
    Brick* getBricks()
    {
        return new LegoBrick();
    };
};