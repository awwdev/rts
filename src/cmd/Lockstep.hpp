#pragma once

#include "com/Types.hpp"
#include "app/Time.hpp"

///////////////////////////////////////////////////////////

namespace rts::cmd {

///////////////////////////////////////////////////////////

struct Lockstep 
{
    f32 stepTime = 0;
    f32 stepTimeMax = 0.100;
    f32 stepTimePrev = 0;
    bool nextStep = false;
    bool Update();
    f32 StepLerpProgress() const { return stepTime / stepTimeMax; };
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