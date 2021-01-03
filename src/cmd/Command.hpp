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
        CmdMove cmdMove {};
    }
    cmdUnion;

    void Execute(ecs::ECS&);

    template<typename T>
    static Command InitUnion();
};

//constexpr auto b = std::is_trivially_copyable_v<Command>;
//Underlying bytes can be copied by std::memcpy or std::memmove, as long as no living volatile object is accessed. 

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

template<typename T>
Command Command::InitUnion()
{
    if constexpr (std::is_same_v<T, CmdMove>)
    {
        return
        {
            .type = CmdEnum::Move,
            .cmdUnion { .cmdMove {} }, 
        };
    }
}

///////////////////////////////////////////////////////////

//TODO using enum

///////////////////////////////////////////////////////////

}//ns