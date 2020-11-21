#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "wnd/Win32/Win32_Undef.hpp"
#include "com/Print.hpp"

///////////////////////////////////////////////////////////

namespace mini::wnd {

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