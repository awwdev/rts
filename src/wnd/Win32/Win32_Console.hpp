#pragma once

#include "com/Windows.hpp"
#include "com/Types.hpp"
#include "com/Print.hpp"
#include "app/CmdArgs.hpp"

///////////////////////////////////////////////////////////

namespace rts::wnd {

///////////////////////////////////////////////////////////

struct Win32_Console
{
    Win32_Console(app::CmdArgs const&);
    ~Win32_Console();
};

///////////////////////////////////////////////////////////

Win32_Console::Win32_Console(app::CmdArgs const& args)
{
    i32 width  = 600;
    i32 height = 400;
    i32 xpos   = 64;
    i32 ypos   = 64;
    args.GetWindowWidth(width);
    args.GetWindowHeight(height);
    args.GetWindowPosX(xpos);
    args.GetWindowPosY(ypos);
    ypos += height;

    WinCheck(AllocConsole());
    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    WinCheck(GetConsoleMode(hOut, &dwMode));
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    WinCheck(SetConsoleMode(hOut, dwMode));

    RECT rect = { xpos, ypos, xpos + width, ypos + height };
    HWND hWnd = GetConsoleWindow();
    WinCheck(MoveWindow(hWnd, rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top, true));
}

///////////////////////////////////////////////////////////

Win32_Console::~Win32_Console()
{
    WinCheck(FreeConsole());
}

///////////////////////////////////////////////////////////

}//ns