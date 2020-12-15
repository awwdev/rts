#pragma once

#include "com/Windows.hpp"
#include "app/_Old/Global.hpp"
#include "app/Time.hpp"
#include "com/Print.hpp"


#include "app/_Old/_EventBuffer.hpp"


///////////////////////////////////////////////////////////

namespace rts::wnd {

///////////////////////////////////////////////////////////

static LRESULT WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    app::Event event {};
    app2::Event event2 {};
    
    switch(uMsg)
    {
        ///////////////////////////////////////////////////////////

        case WM_DESTROY:
        case WM_CLOSE:
        case WM_QUIT:
        event2.type = app2::EventType::WM_Quit;
        //TODO remove
        app::glo::isAppRunning = false; 
        break;

        ///////////////////////////////////////////////////////////

        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
    
        //TODO remove
        switch(wParam) 
        {
            case VK_ESCAPE: 
            event.eventEnum = app::EventEnum::KEY_DOWN_ESCAPE; break;
            default: break;
        };

        event2.type = app2::EventType::Keyboard;
        event2.key.asciiValue = wParam;
        event2.key.state = event2.key.Pressed;
        break;

        ///////////////////////////////////////////////////////////

        case WM_KEYUP:
        case WM_SYSKEYUP:
        event2.type = app2::EventType::Keyboard;
        event2.key.asciiValue = wParam;
        event2.key.state = event2.key.Released;
        break;

        ///////////////////////////////////////////////////////////

        case WM_LBUTTONDOWN:
        //TODO REMOVE
        event.eventEnum = app::EventEnum::MB_LEFT_DOWN;
        event.xpos = LOWORD(lParam);
        event.ypos = HIWORD(lParam);
        app::glo::atomic_mouse_state |= enum_cast(app::MouseState::LeftButtonDown);

        event2.button.state = event2.button.Pressed;
        event2.button.type = event2.button.Left;
        break;

        ///////////////////////////////////////////////////////////

        case WM_LBUTTONUP:
        //TODO REMOVE
        app::glo::atomic_mouse_state &= ~enum_cast(app::MouseState::LeftButtonDown);

        event2.button.state = event2.button.Released;
        event2.button.type = event2.button.Left;
        break;

        ///////////////////////////////////////////////////////////

        case WM_MOUSEMOVE:
        {
            auto xPos = GET_X_LPARAM(lParam); 
            auto yPos = GET_Y_LPARAM(lParam); 

            //TODO REMOVE
            app::glo::atomic_mouse_x.store(xPos, std::memory_order::relaxed);
            app::glo::atomic_mouse_y.store(yPos, std::memory_order::relaxed);
        }
        break;

        ///////////////////////////////////////////////////////////

        case WM_SIZE:
        app::glo::windowWidth  = LOWORD(lParam);
        app::glo::windowHeight = HIWORD(lParam);    

        event2.type = app2::EventType::WM_Size;
        event2.window.x = LOWORD(lParam);
        event2.window.y = HIWORD(lParam);
        event2.window.state = event2.window.Begin;

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

        ///////////////////////////////////////////////////////////

        //case WM_MOVE:
        //event2.type = app2::EventType::WM_Move;
        //event2.coord.x = LOWORD(lParam);
        //event2.coord.y = HIWORD(lParam);
        //break;

        ///////////////////////////////////////////////////////////

        case WM_EXITSIZEMOVE:
        //TODO REMOVE
        app::glo::isWndResized = false;
        event.eventEnum = app::EventEnum::WND_MOVESIZE_END;

        event2.type = app2::EventType::WM_Size;
        event2.window.state = event2.window.End;
        break;

        ///////////////////////////////////////////////////////////

        default: 
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

    app::glo::eventBuffer.Append(event);
    app2::EventBuffer::PushEvent(event2);
    return 0;    
}

///////////////////////////////////////////////////////////

}//ns