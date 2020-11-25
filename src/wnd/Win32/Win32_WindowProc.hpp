#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "wnd/Win32/Win32_Undef.hpp"
#include "app/Global.hpp"
#include "com/Time.hpp"
#include "com/Print.hpp"

///////////////////////////////////////////////////////////

namespace mini::wnd {

///////////////////////////////////////////////////////////

inline void WmClose();
inline void WmKeyDown(WPARAM);
inline void WmKeyUp(WPARAM);
inline void WmSize(LPARAM);
inline void WmSizeMoveExit();

///////////////////////////////////////////////////////////

static LRESULT WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_DESTROY:
        case WM_CLOSE:
        case WM_QUIT:
        WmClose();
        break;

        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        WmKeyDown(wParam);
        break;

        case WM_KEYUP:
        case WM_SYSKEYUP:
        WmKeyUp(wParam);
        break;

        case WM_SIZE:
        WmSize(lParam);
        break;

        case WM_EXITSIZEMOVE:
        WmSizeMoveExit();
        break;

        default: 
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0;    
}

///////////////////////////////////////////////////////////

inline void WmClose()
{
    app::glo::isAppRunning = false;  
}

///////////////////////////////////////////////////////////

inline void WmKeyDown(WPARAM wParam)
{
    app::EventEnum eventEnum;
    switch(wParam)
    {
        case VK_ESCAPE: eventEnum = app::EventEnum::KEY_DOWN_ESCAPE; break;
        default: break;
    };
    app::Event event {};
    event.eventEnum = eventEnum;
    app::glo::events.Append(event);
}

///////////////////////////////////////////////////////////

inline void WmKeyUp(WPARAM)
{

}

///////////////////////////////////////////////////////////

inline void WmSize(LPARAM lParam)
{
    app::glo::windowWidth  = LOWORD(lParam);
    app::glo::windowHeight = HIWORD(lParam);    
}

///////////////////////////////////////////////////////////

inline void WmSizeMoveExit()
{
    app::EventEnum eventEnum = app::EventEnum::WND_MOVE_SIZE;
    app::Event event {};
    event.eventEnum = eventEnum;
    event.width = app::glo::windowWidth;
    event.height = app::glo::windowHeight;
    app::glo::events.Append(event);

    com::dt::t1 = com::dt::clock_t::now();
}

///////////////////////////////////////////////////////////

}//ns