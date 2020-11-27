#pragma once

#include "com/Types.hpp"
#include "com/Print.hpp"

///////////////////////////////////////////////////////////

namespace mini::com {

///////////////////////////////////////////////////////////

inline void Assert(bool expr, auto... args)
{
    if (expr)
        return;

    com::PrintError(args...);

    #ifdef _WIN32
    __debugbreak();
    #endif
    #ifdef __linux__
    __builtin_trap();
    #endif
}

///////////////////////////////////////////////////////////

}//ns