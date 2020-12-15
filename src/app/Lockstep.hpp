#pragma once

#include "com/Types.hpp"
#include "app/_Old/Global.hpp"

///////////////////////////////////////////////////////////

namespace rts::app {

///////////////////////////////////////////////////////////

struct Lockstep 
{
    double stepTime = 0;
    double stepTimeMax = 0.100;
    double stepTimePrev = 0;
    bool nextStep = false;

    bool Update();
};

///////////////////////////////////////////////////////////

bool Lockstep::Update()
{
    nextStep = false;
    stepTime += app::glo::dt;
    if (stepTime > stepTimeMax)
    {
        stepTimePrev = stepTime;
        stepTime = 0;
        nextStep = true;
        return true;
    }
    return false;
}

///////////////////////////////////////////////////////////

}//ns