#pragma once

#include "com/Windows.hpp"
#include "app/Global.hpp"
#include "com/Time.hpp"
#include "com/Print.hpp"

///////////////////////////////////////////////////////////

namespace mini::wnd {

///////////////////////////////////////////////////////////

inline void WmClose();
inline void WmKeyDown(WPARAM);
inline void WmKeyUp(WPARAM);
inline void WmSize(WPARAM, LPARAM);
inline void WmSizeMoveExit();
inline void WmButtonDown();

///////////////////////////////////////////////////////////

static LRESULT WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    app::Event event {};

    switch(uMsg)
    {
        ///////////////////////////////////////////////////////////

        case WM_DESTROY:
        case WM_CLOSE:
        case WM_QUIT:
        app::isAppRunning = false;  
        return 0;

        ///////////////////////////////////////////////////////////

        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:

        switch(wParam)
        {
            case VK_ESCAPE: event.eventEnum = app::EventEnum::KEY_DOWN_ESCAPE; break;
            default: break;
        };

        break;

        ///////////////////////////////////////////////////////////

        case WM_LBUTTONDOWN:
        event.eventEnum = app::EventEnum::MB_LEFT_DOWN;
        event.xpos = LOWORD(lParam);
        event.ypos = HIWORD(lParam);
        break;

        ///////////////////////////////////////////////////////////

        case WM_KEYUP:
        case WM_SYSKEYUP:
        break;

        ///////////////////////////////////////////////////////////

        case WM_SIZE:
        app::windowWidth  = LOWORD(lParam);
        app::windowHeight = HIWORD(lParam);    
        event.eventEnum = app::EventEnum::WND_MOVE_SIZE;
        com::dt::t1 = com::dt::clock_t::now();
        break;

        ///////////////////////////////////////////////////////////

        default: 
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

    if (app::events.Contains(event) == nullptr)    
        app::events.Append(event);

    return 0;    
}

///////////////////////////////////////////////////////////

}//ns