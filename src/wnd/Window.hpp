#pragma once

///////////////////////////////////////////////////////////

#ifdef _WIN32
#include "Win32\Win32_Window.hpp"
#include "Win32\Win32_Console.hpp"
namespace mini::wnd {
using Window  = Win32_Window;
using Console = Win32_Console;
}//ns
#endif

///////////////////////////////////////////////////////////

#ifdef __linux__
#include "Linux\X11_Window.hpp"
#include "Linux\X11_Console.hpp"
namespace mini::wnd {
using Window  = X11_Window;
using Console = X11_Console;
}//ns
#endif

///////////////////////////////////////////////////////////