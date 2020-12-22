#pragma once

#include "com/Types.hpp"
#include "com/Vec.hpp"
#include "ecs/ECS.hpp"

///////////////////////////////////////////////////////////

namespace rts::cmd {

///////////////////////////////////////////////////////////

struct CmdMove 
{
    com::POD_Array<ecs::ID, 10> entities;
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
        mainComponent.transform.posTarget = pos + com::Vec2i { -8 + rand() % 16, -8 + rand() % 16 }; //dont stack for testing
        mainComponent.transform.CalculateDelta();       
    } 
}

///////////////////////////////////////////////////////////

}//ns