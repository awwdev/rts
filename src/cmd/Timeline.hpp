#pragma once

#include "com/Array.hpp"
#include "cmd/Command.hpp"
#include "ecs/ECS.hpp"
#include "cmd/Lockstep.hpp"

///////////////////////////////////////////////////////////

namespace rts::cmd {

///////////////////////////////////////////////////////////

using CmdsPerStep = com::Array<Command, CMDS_PER_STEP_MAX>;

///////////////////////////////////////////////////////////

struct Step
{
    CmdsPerStep cmds;
    f32 stepDuration;
};

///////////////////////////////////////////////////////////

struct Timeline 
{
    Step steps [STEPS_MAX];
    idx_t stepIdx = 0;

    f32 stepTime = 0;
    f32 stepTimePrev = 0;
    auto StepTimePrevLerp() const { return stepTimePrev / STEP_TIME_SEC; }
    //TODO store actual prev step time 

    bool Update();
    void Execute(ecs::ECS&);
    void Store(Command const&, idx_t);
};

///////////////////////////////////////////////////////////

bool Timeline::Update()
{
    stepTimePrev += app::Time::dt; //used for interpolation
    stepTimePrev = com::Clamp(stepTimePrev, 0.f, STEP_TIME_SEC);

    stepTime += app::Time::dt;
    if (stepTime > STEP_TIME_SEC)
    {
        stepTime = 0;
        stepTimePrev = 0;
        return true;
    }
    return false;
}

///////////////////////////////////////////////////////////

void Timeline::Execute(ecs::ECS& ecs)
{
    auto& step = steps[stepIdx];
    FOR_ARRAY(step.cmds, i)
    {
        auto& cmd = step.cmds[i];
        cmd.Execute(ecs);
    }
    stepIdx += 1;
    com::Assert(stepIdx < STEPS_MAX, "steps array exhausted");
}

///////////////////////////////////////////////////////////

void Timeline::Store(Command const& cmd, idx_t idx)
{
    steps[idx].cmds.Append(cmd);
}

///////////////////////////////////////////////////////////

}//ns