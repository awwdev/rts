#pragma once

#include "com/Types.hpp"
#include "com/Vec.hpp"
#include "ecs/ECS.hpp"
#include "com/Random.hpp"

///////////////////////////////////////////////////////////

namespace rts::cmd {

///////////////////////////////////////////////////////////

struct CmdMove 
{
    static constexpr auto MAX_SELECTION = 1'000;
    com::POD_Array<ecs::ID, MAX_SELECTION> entities;
    com::Vec2i pos;
    void Execute(ecs::ECS&);
};

///////////////////////////////////////////////////////////

void CmdMove::Execute(ecs::ECS& ecs)
{
    FOR_ARRAY(entities, i)
    {
        auto& entityID = entities[i];
        auto& mainComponent = ecs.arrays.mainComponents.GetComponent(entityID);
        com::Vec2i rnd { com::GetRandomNumber(-8, 8), com::GetRandomNumber(-8, 8) };
        mainComponent.transform.posTarget = pos + rnd;
        mainComponent.transform.CalculateDelta();       
    } 
}

///////////////////////////////////////////////////////////

}//ns