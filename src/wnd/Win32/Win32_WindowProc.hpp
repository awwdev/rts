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

static LRESULT WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_ACTIVATEAPP:
        {

        }
        break;

        case WM_DESTROY:
        case WM_CLOSE:
        case WM_QUIT:
        {
            app::glo::isAppRunning = false;  
        }
        break;

        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        {
            app::KeyboardEnum key;
            switch(wParam)
            {
                case VK_ESCAPE: key = app::KeyboardEnum::Escape; break;
                default: break;
            };

            app::Event event
            {
                .eventEnum = app::EventEnum::KeyDown,
                .keyboard = 
                {
                    .type = key
                }
            };
            app::glo::events.Append(event);
        }
        break;

        case WM_KEYUP:
        case WM_SYSKEYUP:
        {

        }
        break;

        case WM_SIZE:
        {
            app::glo::windowWidth  = LOWORD(lParam);
            app::glo::windowHeight = HIWORD(lParam);
        }
        break;

        case WM_EXITSIZEMOVE:
        {
            app::Event event
            {
                .eventEnum = app::EventEnum::ExitSizeMove,
                .window = 
                {
                    app::glo::windowWidth,
                    app::glo::windowHeight
                }
            };
            app::glo::events.Append(event);

            com::dt::t1 = com::dt::clock_t::now();
            //trigger swapchain recreation
        }
        break;

        default: 
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0;    
}

///////////////////////////////////////////////////////////

}//ns