#pragma once

#include "com/Windows.hpp"
#include "wnd/Win32/Win32_WindowProc.hpp"
#include "com/Types.hpp"
#include "com/Print.hpp"
#include "app/_Old/Global.hpp"

///////////////////////////////////////////////////////////

namespace rts::wnd {

///////////////////////////////////////////////////////////

struct Win32_Window
{
    HINSTANCE hInstance;
    HWND hWnd = NULL;
    chars_t wndClassName = "wnd";

    Win32_Window(HINSTANCE, chars_t, i32, i32, i32, i32);
    ~Win32_Window();
    void BlockingPollEvents();
};

///////////////////////////////////////////////////////////

Win32_Window::Win32_Window(
HINSTANCE pInst = GetModuleHandle(NULL),
chars_t title = "Window",
i32 width  = CW_USEDEFAULT,
i32 height = CW_USEDEFAULT,
i32 xpos   = CW_USEDEFAULT,
i32 ypos   = CW_USEDEFAULT)
    : hInstance { pInst }
{
    WNDCLASSEX wndClass 
    {
        .cbSize         = sizeof(WNDCLASSEX),
        .style          = CS_HREDRAW | CS_VREDRAW,
        .lpfnWndProc    = WindowProc,
        .cbClsExtra     = 0,
        .cbWndExtra     = 0,
        .hInstance      = hInstance,
        .hIcon          = 0,
        .hCursor        = LoadCursor(NULL, IDC_ARROW),
        .hbrBackground  = 0,
        .lpszMenuName   = 0,
        .lpszClassName  = wndClassName,
        .hIconSm        = LoadIcon(NULL, IDI_APPLICATION),
    };
    WinCheck(RegisterClassEx(&wndClass));

    hWnd = CreateWindowEx(
        0,                                //dwExStyle                  
        wndClassName,                     //lpClassName                  
        title,                            //lpWindowName                 
        WS_OVERLAPPEDWINDOW | WS_VISIBLE, //dwStyle                 
        xpos,                             //x
        ypos,                             //y    
        width,                            //nWidth
        height,                           //nHeight
        0,                                //hWndParent
        0,                                //hMenu
        hInstance,                        //hInstance
        0                                 //lpParam
    );
    WinCheck(hWnd);  

    //TODO REMOVE
    app::glo::isWndResized = false; //since create will post WM_SIZE

    app2::Event event {};
    event.type = app2::EventType::WM_Size;
    event.window.state = app2::Window::End;
    app2::EventBuffer::PushEvent(event);

}

///////////////////////////////////////////////////////////

Win32_Window::~Win32_Window()
{
    WinCheck(DestroyWindow(hWnd));
    WinCheck(UnregisterClass(wndClassName, hInstance));
}

///////////////////////////////////////////////////////////

void Win32_Window::BlockingPollEvents()
{
    MSG message;
    BOOL rtn;
    while((rtn = GetMessage(&message, NULL, 0, 0)))
    {
        WinCheck(rtn != -1, "GetMessage Error");
        if (!app::glo::isAppRunning)
            break;

        TranslateMessage(&message);
        DispatchMessage(&message);
    } 
}

///////////////////////////////////////////////////////////

}//ns