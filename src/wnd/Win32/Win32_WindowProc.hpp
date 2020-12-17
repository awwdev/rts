#pragma once

#include "com/Windows.hpp"
#include "app/Time.hpp"
#include "com/Print.hpp"
#include "app/Inputs.hpp"

///////////////////////////////////////////////////////////

namespace rts::wnd {

///////////////////////////////////////////////////////////

static LRESULT WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    app::Input input {};

    switch(uMsg)
    {
        ///////////////////////////////////////////////////////////

        case WM_DESTROY:
        case WM_CLOSE:
        case WM_QUIT:
        input.type = app::Input::Window;
        break;

        ///////////////////////////////////////////////////////////

        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        input.type = app::Input::Keyboard;
        break;

        ///////////////////////////////////////////////////////////

        case WM_KEYUP:
        case WM_SYSKEYUP:
        input.type = app::Input::Keyboard;
        break;

        ///////////////////////////////////////////////////////////

        case WM_LBUTTONDOWN:
        input.type = app::Input::Mouse;
        break;

        ///////////////////////////////////////////////////////////

        case WM_LBUTTONUP:
        input.type = app::Input::Mouse;
        break;

        ///////////////////////////////////////////////////////////

        case WM_MOUSEMOVE:
        input.type = app::Input::Mouse;
        break;

        ///////////////////////////////////////////////////////////

        case WM_SIZE:
        input.type = app::Input::Window;
        switch(wParam)
        {
            case SIZE_MAXIMIZED:
            case SIZE_MINIMIZED:
            break;
            case SIZE_RESTORED:
            break;
            default: 
            break;
        }
        break;

        ///////////////////////////////////////////////////////////

        case WM_EXITSIZEMOVE:
        input.type = app::Input::Window;
        break;

        ///////////////////////////////////////////////////////////

        default: 
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

    app::Inputs::inputBuffer.Write(input);
    return 0;    
}

///////////////////////////////////////////////////////////

}//ns