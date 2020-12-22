#pragma once

#include "com/POD_Array.hpp"
#include "cmd/Command.hpp"
#include "ecs/ECS.hpp"

///////////////////////////////////////////////////////////

namespace rts::cmd {

///////////////////////////////////////////////////////////

constexpr auto STEPS_MAX = 1'000;
constexpr auto CMDS_PER_STEP_MAX = 5;
using CmdsPerStep = com::POD_Array<Command, CMDS_PER_STEP_MAX>;

///////////////////////////////////////////////////////////

struct Step
{
    CmdsPerStep cmds;
    f32 stepDuration;
};

///////////////////////////////////////////////////////////

struct Timeline 
{
    Step  steps [STEPS_MAX];
    idx_t stepIdx = 0;

    void Execute(ecs::ECS&);
    void Store(CmdsPerStep const&, f32, idx_t);
};

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
}

///////////////////////////////////////////////////////////

void Timeline::Store(CmdsPerStep const& cmds, f32 stepDuration, idx_t idx)
{
    steps[idx].cmds.AppendArray(cmds);
    steps[idx].stepDuration = stepDuration;
}

///////////////////////////////////////////////////////////

}//ns