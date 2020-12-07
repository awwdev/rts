#pragma once

#include "com/Windows.hpp"
#include "app/Global.hpp"
#include "app/Time.hpp"
#include "com/Print.hpp"

///////////////////////////////////////////////////////////

namespace rts::wnd {

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
        app::glo::isAppRunning = false;  
        break;

        ///////////////////////////////////////////////////////////

        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        
        switch(wParam)
        {
            case VK_ESCAPE: 
            event.eventEnum = app::EventEnum::KEY_DOWN_ESCAPE; break;
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
        app::glo::windowWidth  = LOWORD(lParam);
        app::glo::windowHeight = HIWORD(lParam);    
        switch(wParam)
        {
            case SIZE_MAXIMIZED:
            case SIZE_MINIMIZED:
            com::Print("minmax");
            event.eventEnum = app::EventEnum::WND_MOVESIZE_END;
            app::glo::isWndResized = false;
            break;

            default: 
            com::Print("restore");
            app::glo::isWndResized = true;
            event.eventEnum = app::EventEnum::WND_MOVESIZE;
            break;
        }
        break;

        case WM_EXITSIZEMOVE:
        app::glo::isWndResized = false;
        event.eventEnum = app::EventEnum::WND_MOVESIZE_END;
        break;

        ///////////////////////////////////////////////////////////

        default: 
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

    app::glo::eventBuffer.Append(event);
    return 0;    
}

///////////////////////////////////////////////////////////

}//ns