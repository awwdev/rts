#pragma once

#include "com/Types.hpp"
#include "com/Print.hpp"

///////////////////////////////////////////////////////////

namespace mini::com {

///////////////////////////////////////////////////////////

inline void Assert(bool expr, const char* msg)
{
    if (expr)
        return;

    com::PrintError(msg);

    #ifdef _WIN32
    __debugbreak();
    #endif
    #ifdef __linux__
    __builtin_trap();
    #endif
}

///////////////////////////////////////////////////////////

}//ns