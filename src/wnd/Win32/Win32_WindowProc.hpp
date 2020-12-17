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
        input.window.shouldClose = true;
        break;

        ///////////////////////////////////////////////////////////

        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        break;

        ///////////////////////////////////////////////////////////

        case WM_KEYUP:
        case WM_SYSKEYUP:
        break;

        ///////////////////////////////////////////////////////////

        case WM_LBUTTONDOWN:
        break;

        ///////////////////////////////////////////////////////////

        case WM_LBUTTONUP:
        break;

        ///////////////////////////////////////////////////////////

        case WM_MOUSEMOVE:
        //GET_Y_LPARAM(lParam); 
        //GET_X_LPARAM(lParam); 
        break;

        ///////////////////////////////////////////////////////////

        case WM_SIZE:
        input.type = app::Input::Window;
        input.window.sizeState = app::InputWindow::Continued;
        input.window.width  = LOWORD(lParam);
        input.window.height = HIWORD(lParam);

        switch(wParam)
        {
            case SIZE_MAXIMIZED:
            case SIZE_MINIMIZED:
            static bool minmax = false;
            minmax = true;
            break;
            case SIZE_RESTORED:
            if (minmax == true)
                input.window.sizeState = app::InputWindow::End;
            minmax = false;
            break;
            default: 
            break;
        }
        break;

        ///////////////////////////////////////////////////////////

        case WM_EXITSIZEMOVE:
        input.type = app::Input::Window;
        input.window.sizeState = app::InputWindow::End;
        break;

        ///////////////////////////////////////////////////////////

        default: 
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

    //app::AtomicRingBuffer::WriteInput(input);
    return 0;    
}

///////////////////////////////////////////////////////////

}//ns