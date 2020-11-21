#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "wnd/Win32/Win32_Undef.hpp"
#include "wnd/Win32/Win32_WinAssert.hpp"
#include "com/Types.hpp"
#include "com/Print.hpp"

///////////////////////////////////////////////////////////

namespace mini::wnd {
struct Win32_Console {

////////////////////////////////////////////////////////////

Win32_Console(i32 width, i32 height, i32 xpos, i32 ypos)
{
    WinAssert(AllocConsole());
    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    WinAssert(GetConsoleMode(hOut, &dwMode));
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    WinAssert(SetConsoleMode(hOut, dwMode));

    RECT rect = { xpos, ypos, xpos + width, ypos + height };
    HWND hWnd = GetConsoleWindow();
    WinAssert(MoveWindow(hWnd, rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top, true));
}

////////////////////////////////////////////////////////////

~Win32_Console()
{
    WinAssert(FreeConsole());
}

////////////////////////////////////////////////////////////

};
}//ns