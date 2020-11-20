#pragma once
#include "com/Types.hpp"
#include "com/Print.hpp"

namespace min::com {

inline void Assert(bool expr, const char* msg)
{
    if (expr)
        return;

    com::PrintError(msg);
    __debugbreak();
}

}//ns