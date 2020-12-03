#pragma once

#include "com/Types.hpp"
#include "ecs/ECS.hpp"

///////////////////////////////////////////////////////////

namespace rts::cmd {

///////////////////////////////////////////////////////////

struct CmdMove 
{
    com::Array<ecs::ID, 10> entities;
    i32 xpos;
    i32 ypos;
    void Execute(ecs::ECS&);
};

///////////////////////////////////////////////////////////

void CmdMove::Execute(ecs::ECS& ecs)
{
    
}

///////////////////////////////////////////////////////////

}//ns