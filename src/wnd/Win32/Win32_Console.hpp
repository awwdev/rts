#pragma once

#include "com/Windows.hpp"
#include "com/Types.hpp"
#include "com/Print.hpp"

///////////////////////////////////////////////////////////

namespace mini::wnd {

///////////////////////////////////////////////////////////

struct Win32_Console
{
    Win32_Console(i32, i32, i32, i32);
    ~Win32_Console();
};

////////////////////////////////////////////////////////////

Win32_Console::Win32_Console(i32 width, i32 height, i32 xpos, i32 ypos)
{
    com::WinAssert(AllocConsole());
    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    com::WinAssert(GetConsoleMode(hOut, &dwMode));
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    com::WinAssert(SetConsoleMode(hOut, dwMode));

    RECT rect = { xpos, ypos, xpos + width, ypos + height };
    HWND hWnd = GetConsoleWindow();
    com::WinAssert(MoveWindow(hWnd, rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top, true));
}

////////////////////////////////////////////////////////////

Win32_Console::~Win32_Console()
{
    com::WinAssert(FreeConsole());
}

////////////////////////////////////////////////////////////

}//ns