#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "com/WindowsUndef.hpp"
#include "com/Print.hpp"

///////////////////////////////////////////////////////////

namespace mini::com {

///////////////////////////////////////////////////////////

inline void WinAssert(auto expr)
{
    if (expr == 0)
    {
        auto err = GetLastError();
        com::PrintError("WinAssert failed", err);
    }
}

///////////////////////////////////////////////////////////

}//ns