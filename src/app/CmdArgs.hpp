#pragma once

#include <cstdlib>
#include "com/Print.hpp"
#include "com/Types.hpp"

///////////////////////////////////////////////////////////

namespace rts::app {

///////////////////////////////////////////////////////////

enum class CmdArgsEnum
{
    Path,
    WindowWidth,
    WindowHeight,
    WindowPosX,
    WindowPosY,
    LocalPort,
    RemotePort,
};

///////////////////////////////////////////////////////////

struct CmdArgs
{
    int argc;
    char** argv;

    auto GetWindowWidth(auto&) const;
    auto GetWindowHeight(auto&) const;
    auto GetWindowPosX(auto&) const;
    auto GetWindowPosY(auto&) const;

    auto GetLocalPort(auto&) const;
    auto GetRemotePort(auto&) const;

    void Print() const;
    bool HasArg(CmdArgsEnum) const;
};

///////////////////////////////////////////////////////////

bool CmdArgs::HasArg(CmdArgsEnum arg) const
{
    return argc > enum_cast(arg);
}

///////////////////////////////////////////////////////////

auto CmdArgs::GetLocalPort(auto& ref) const
{
    if (HasArg(CmdArgsEnum::LocalPort))
        ref = (u16) std::atoi(argv[enum_cast(CmdArgsEnum::LocalPort)]);
}

///////////////////////////////////////////////////////////

auto CmdArgs::GetRemotePort(auto& ref) const
{
    if (HasArg(CmdArgsEnum::RemotePort))
        ref = (u16) std::atoi(argv[enum_cast(CmdArgsEnum::RemotePort)]);
}

///////////////////////////////////////////////////////////

auto CmdArgs::GetWindowWidth(auto& ref) const
{
    if (HasArg(CmdArgsEnum::WindowWidth))
        ref = std::atoi(argv[enum_cast(CmdArgsEnum::WindowWidth)]);
}

///////////////////////////////////////////////////////////

auto CmdArgs::GetWindowHeight(auto& ref) const
{
    if (HasArg(CmdArgsEnum::WindowHeight))
        ref = std::atoi(argv[enum_cast(CmdArgsEnum::WindowHeight)]);
}

///////////////////////////////////////////////////////////

auto CmdArgs::GetWindowPosX(auto& ref) const
{
    if (HasArg(CmdArgsEnum::WindowPosX))
        ref = std::atoi(argv[enum_cast(CmdArgsEnum::WindowPosX)]);
}

///////////////////////////////////////////////////////////

auto CmdArgs::GetWindowPosY(auto& ref) const
{
    if (HasArg(CmdArgsEnum::WindowPosY))
        ref = std::atoi(argv[enum_cast(CmdArgsEnum::WindowPosY)]);
}

///////////////////////////////////////////////////////////

void CmdArgs::Print() const 
{
    for(int i = 0; i < argc; ++i)
        com::Print("cmd arg", i, argv[i]);    
}

///////////////////////////////////////////////////////////

}//ns