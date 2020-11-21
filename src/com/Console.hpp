#pragma once

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "UndefWin32.hpp"
#endif

///////////////////////////////////////////////////////////

namespace mini::com {

///////////////////////////////////////////////////////////

static void SetupConsole()
{
   #ifdef _WIN32
   HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
   DWORD dwMode = 0;
   GetConsoleMode(hOut, &dwMode);
   dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
   SetConsoleMode(hOut, dwMode);
   #endif
}

///////////////////////////////////////////////////////////

static void MoveConsole(int xpos, int ypos, int width, int height)
{
    #ifdef _WIN32
    RECT rect = { xpos, ypos, xpos + width, ypos + height };
    HWND hWnd = GetConsoleWindow();
    MoveWindow(hWnd, rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top, true);
    #endif
}

///////////////////////////////////////////////////////////

}//ns