#pragma once
#include "Brick.h"
#include <vector>

class Factory
{
public:
    virtual Brick* getBricks() = 0;
};