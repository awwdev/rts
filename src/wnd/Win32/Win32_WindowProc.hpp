#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "wnd/Win32/Win32_Undef.hpp"

///////////////////////////////////////////////////////////

namespace mini::wnd {

///////////////////////////////////////////////////////////

static LRESULT WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_ACTIVATEAPP:
        {            
        } break;

        case WM_DESTROY:
        case WM_CLOSE:
        case WM_QUIT:
        {            
        } break;

        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        {
        } break;

        case WM_KEYUP:
        case WM_SYSKEYUP:
        {
        } break;

        default: 
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0;    
}

///////////////////////////////////////////////////////////

}//ns