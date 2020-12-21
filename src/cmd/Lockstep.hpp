#pragma once

#include "com/Types.hpp"
#include "app/Time.hpp"

///////////////////////////////////////////////////////////

namespace rts::cmd {

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
    stepTime += app::Time::dt;
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