#pragma once

#include "com/Types.hpp"
#include "com/Print.hpp"

///////////////////////////////////////////////////////////

namespace rts::com {

///////////////////////////////////////////////////////////

inline void Assert(bool expr, auto... args)
{
    if (expr)
        return;

    com::PrintError(args...);
     __builtin_trap();
}

///////////////////////////////////////////////////////////

}//ns