#pragma once

#include "com/Windows.hpp"
#include "app/Global.hpp"
#include "app/Time.hpp"
#include "com/Print.hpp"


#include "app/_EventBuffer.hpp"
rts::app2::EventBuffer buf;

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

        app::glo::atomic_mouse_state |= enum_cast(app::MouseState::LeftButtonDown);
        break;

        ///////////////////////////////////////////////////////////

        case WM_LBUTTONUP:
        app::glo::atomic_mouse_state &= ~enum_cast(app::MouseState::LeftButtonDown);
        break;

        ///////////////////////////////////////////////////////////

        case WM_KEYUP:
        case WM_SYSKEYUP:
        break;

        ///////////////////////////////////////////////////////////

        case WM_MOUSEMOVE:
        {
            auto xPos = GET_X_LPARAM(lParam); 
            auto yPos = GET_Y_LPARAM(lParam); 
            app::glo::atomic_mouse_x.store(xPos, std::memory_order::relaxed);
            app::glo::atomic_mouse_y.store(yPos, std::memory_order::relaxed);
        }
        break;

        ///////////////////////////////////////////////////////////

        case WM_SIZE:
        app::glo::windowWidth  = LOWORD(lParam);
        app::glo::windowHeight = HIWORD(lParam);    
        switch(wParam)
        {
            case SIZE_MAXIMIZED:
            case SIZE_MINIMIZED:
            event.eventEnum = app::EventEnum::WND_MOVESIZE_END;
            app::glo::isWndResized = false;
            app::glo::isWndMinMax = true;
            break;

            case SIZE_RESTORED:
            if (app::glo::isWndMinMax)
            {
                event.eventEnum = app::EventEnum::WND_MOVESIZE_END;
                app::glo::isWndResized = false;
                app::glo::isWndMinMax = false;
            }
            else
            {
                app::glo::isWndResized = true;
                event.eventEnum = app::EventEnum::WND_MOVESIZE;
            }
            break;
            
            default: 
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