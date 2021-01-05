#pragma once

#include "com/Windows.hpp"
#include "app/Time.hpp"
#include "com/Print.hpp"
#include "app/Input/Inputs.hpp"

///////////////////////////////////////////////////////////

namespace rts::wnd {

///////////////////////////////////////////////////////////

static LRESULT WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    using namespace app;
    Input input {};

    switch(uMsg)
    {
        ///////////////////////////////////////////////////////////

        case WM_DESTROY:
        case WM_CLOSE:
        case WM_QUIT:
        input.type = Input::Window;
        input.window.shouldClose = true;
        break;

        ///////////////////////////////////////////////////////////

        case WM_SIZE:
        static bool sizing;
        sizing = true;
        input.type = Input::Window;
        input.window.sizeState = InputWindow::Continued;
        input.window.width = LOWORD(lParam);
        input.window.height = HIWORD(lParam);
        switch(wParam)
        {
            case SIZE_MAXIMIZED:
            case SIZE_MINIMIZED:
            static bool minmax;
            minmax = true;
            input.window.sizeState = InputWindow::End;
            break;
            case SIZE_RESTORED:
            if (minmax)
            {
                input.window.sizeState = InputWindow::End;
                minmax = false;
            }
            break;
            default: 
            break;
        }
        break;

        ///////////////////////////////////////////////////////////

        case WM_EXITSIZEMOVE:
        input.type = Input::Window;
        if (sizing)
        {
            input.window.sizeState = InputWindow::End;
            sizing = false;
            RECT rect;
            WinCheck(GetClientRect(hWnd, &rect));
            input.window.width  = rect.right;
            input.window.height = rect.bottom;
        }
        break;

        ///////////////////////////////////////////////////////////

        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        input.type = Input::Keyboard;
        input.key.state = InputKey::Down;
        input.key.value = wParam;
        break;

        ///////////////////////////////////////////////////////////

        case WM_KEYUP:
        case WM_SYSKEYUP:
        input.type = Input::Keyboard;
        input.key.state = InputKey::Up;
        input.key.value = wParam;
        break;

        ///////////////////////////////////////////////////////////

        case WM_LBUTTONDOWN:
        input.type = Input::Mouse;
        input.mouse.pos.x = GET_X_LPARAM(lParam); 
        input.mouse.pos.y = GET_Y_LPARAM(lParam); 
        input.mouse.buttons[InputMouse::Left] = InputMouse::Pressed;
        break;

        ///////////////////////////////////////////////////////////

        case WM_LBUTTONUP:
        input.type = Input::Mouse;
        input.mouse.pos.x = GET_X_LPARAM(lParam); 
        input.mouse.pos.y = GET_Y_LPARAM(lParam); 
        input.mouse.buttons[InputMouse::Left] = InputMouse::Released;
        break;

        ///////////////////////////////////////////////////////////

        case WM_MOUSEMOVE:
        input.type = Input::Mouse;
        input.mouse.pos.x = GET_X_LPARAM(lParam); 
        input.mouse.pos.y = GET_Y_LPARAM(lParam); 
        break;

        ///////////////////////////////////////////////////////////

        default: 
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

    Inputs::inputBuffer.Write(input);
    return 0;    
}

///////////////////////////////////////////////////////////

}//ns