#pragma once
#include <iostream>
#include "../include/Factory.h"
#include "../include/ConcreteBrick.h"

class ConcreteFactory : public Factory
{
    public:
    ConcreteFactory(){};
    ~ConcreteFactory(){};
    Brick* getBricks()
    {
        return new ConcreteBrick();
    };
};