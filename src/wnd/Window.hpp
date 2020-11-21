#pragma once

///////////////////////////////////////////////////////////

#ifdef _WIN32
#include "wnd/Win32/Win32_Window.hpp"
#include "wnd/Win32/Win32_Console.hpp"
namespace mini::wnd
{
    using Window  = Win32_Window;
    using Console = Win32_Console;
}
#endif

///////////////////////////////////////////////////////////

#ifdef __linux__
#include "wnd/Linux/X11_Window.hpp"
#include "wnd/Linux/X11_Console.hpp"
namespace mini::wnd 
{
    using Window = X11_Window;
}
#endif