#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "wnd/Win32/Win32_Undef.hpp"
#include "app/Global.hpp"

///////////////////////////////////////////////////////////

namespace mini::wnd {

///////////////////////////////////////////////////////////

inline void WmClose()
{
    app::isAppRunning = false;  
}

////////////////////////////////////////////////////////////

inline void WmKeyDown(WPARAM wParam, LPARAM)
{
    if (wParam == VK_ESCAPE)
        app::isAppRunning = false;  
}

///////////////////////////////////////////////////////////

inline void WmKeyUp(WPARAM wParam, LPARAM)
{
    if (wParam == VK_ESCAPE)
        app::isAppRunning = false;  
}

///////////////////////////////////////////////////////////

inline void WmActivateApp()
{

}

///////////////////////////////////////////////////////////

static LRESULT WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_ACTIVATEAPP:
        WmActivateApp();
        break;

        case WM_DESTROY:
        case WM_CLOSE:
        case WM_QUIT:
        WmClose();
        break;

        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        WmKeyDown(wParam, lParam);
        break;

        case WM_KEYUP:
        case WM_SYSKEYUP:
        WmKeyUp(wParam, lParam);
        break;

        default: 
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0;    
}

///////////////////////////////////////////////////////////

}//ns