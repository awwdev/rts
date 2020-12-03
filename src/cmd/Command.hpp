#pragma once

#include "cmd/Cmds/CmdMove.hpp"

///////////////////////////////////////////////////////////

namespace rts::cmd {

///////////////////////////////////////////////////////////

enum class CmdEnum
{
    None,
    Move,
};

///////////////////////////////////////////////////////////

struct Command
{   
    CmdEnum type;
    union
    {
        CmdMove cmdMove;
    }
    cmdUnion {};

    void Execute(ecs::ECS&);
};

///////////////////////////////////////////////////////////

void Command::Execute(ecs::ECS& ecs)
{
    switch(type)
    {
        case CmdEnum::Move: cmdUnion.cmdMove.Execute(ecs); break;
        case CmdEnum::None: break;
        default: com::Assert(false, "cmd missing"); break;
    }    
}

///////////////////////////////////////////////////////////

}//ns