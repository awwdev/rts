#pragma once

#include "com/Windows.hpp"
#include "wnd/Win32/Win32_WindowProc.hpp"
#include "com/Types.hpp"
#include "com/Print.hpp"

///////////////////////////////////////////////////////////

namespace mini::wnd {

///////////////////////////////////////////////////////////

struct Win32_Window
{
    HWND hWnd = 0;
    HINSTANCE hInstance = GetModuleHandle(0);
    chars_t wndClassName = "wnd";

    Win32_Window(chars_t, i32, i32, i32, i32);
    ~Win32_Window();
    void Update();
};

///////////////////////////////////////////////////////////

Win32_Window::Win32_Window(
chars_t title  = "Window",
i32 width  = CW_USEDEFAULT,
i32 height = CW_USEDEFAULT,
i32 xpos   = CW_USEDEFAULT,
i32 ypos   = CW_USEDEFAULT)
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
}

///////////////////////////////////////////////////////////

Win32_Window::~Win32_Window()
{
    WinCheck(DestroyWindow(hWnd));
    WinCheck(UnregisterClass(wndClassName, hInstance));
}

///////////////////////////////////////////////////////////

void Win32_Window::Update()
{
    app::glo::events.count = 0;
    for (MSG message; PeekMessage(&message, NULL, 0, 0, PM_REMOVE);)
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }    
}

///////////////////////////////////////////////////////////

}//ns