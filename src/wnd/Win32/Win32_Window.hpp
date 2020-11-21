#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "wnd/Win32/Win32_Undef.hpp"
#include "wnd/Win32/Win32_WindowProc.hpp"
#include "wnd/Win32/Win32_WinAssert.hpp"
#include "com/Types.hpp"
#include "com/Print.hpp"

///////////////////////////////////////////////////////////

namespace mini::wnd {

////////////////////////////////////////////////////////////

struct Win32_Window {

///////////////////////////////////////////////////////////

PRIVATE HWND hWnd = 0;
PRIVATE HINSTANCE hInstance = GetModuleHandle(0);
PRIVATE chars_t wndClassName = "wnd";

///////////////////////////////////////////////////////////

PUBLIC Win32_Window(
chars_t title  = "Window",
i32 width  = CW_USEDEFAULT,
i32 height = CW_USEDEFAULT,
i32 xpos   = CW_USEDEFAULT,
i32 ypos   = CW_USEDEFAULT)
{
    mRegisterClass();
    mCreateWindow(xpos, ypos, width, height, title);
}

///////////////////////////////////////////////////////////

PUBLIC ~Win32_Window()
{
    WinAssert(UnregisterClass(wndClassName, hInstance));
}

///////////////////////////////////////////////////////////

PRIVATE void mRegisterClass()
{
    const WNDCLASSEX wndClass 
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
    WinAssert(RegisterClassEx(&wndClass));
}

///////////////////////////////////////////////////////////

PRIVATE void mCreateWindow(i32 xpos, i32 ypos, i32 width, i32 height, chars_t title)
{
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
    WinAssert(hWnd);  
}

///////////////////////////////////////////////////////////

PUBLIC void PollEvents()
{
    for (MSG message; PeekMessage(&message, NULL, 0, 0, PM_REMOVE);)
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }    
}

///////////////////////////////////////////////////////////

PUBLIC void Display()
{

}

///////////////////////////////////////////////////////////

};//struct  

////////////////////////////////////////////////////////////

}//ns