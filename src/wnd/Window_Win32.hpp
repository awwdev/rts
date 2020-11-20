#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "com/UndefWin32.hpp"

#include "com/Types.hpp"
#include "com/Print.hpp"

///////////////////////////////////////////////
// Window
///////////////////////////////////////////////

namespace min::wnd {

inline bool running = true;

inline LRESULT WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_CLOSE:
        {
            running = false;
            break;
        }

        default: break;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

inline void WinAssert(auto pExpr)
{
    if (pExpr == 0)
    {
        auto err = GetLastError();
        com::PrintError("WinAssert failed", err);
    }
}

struct Window
{
    ///////////////////////////////////////////////
    // Constructor
    ///////////////////////////////////////////////

    Window(
        const char* title = "Window", 
        i32 width  = CW_USEDEFAULT,
        i32 height = CW_USEDEFAULT,
        i32 xpos   = CW_USEDEFAULT,
        i32 ypos   = CW_USEDEFAULT)
    {
        Register();
        Create(title, width, height, xpos, ypos);
        ShowWindow(hWnd, 1); 
        UpdateWindow(hWnd); 
    }

    ~Window()
    {
        WinAssert(UnregisterClass(wndClassName, hInstance));
    }

    ///////////////////////////////////////////////
    // Display
    ///////////////////////////////////////////////

    void Display()
    {
        
    }

    void PollEvents()
    {
        for (MSG message; PeekMessageW(&message, NULL, 0, 0, PM_REMOVE);)
        {
            TranslateMessage(&message);
            DispatchMessageW(&message);
        }
    }

    ///////////////////////////////////////////////
    // Helper
    ///////////////////////////////////////////////

    void Register()
    {
        const WNDCLASSEX wndClass 
        {
            .cbSize         = sizeof(WNDCLASSEX),
            .style          = 0,
            .lpfnWndProc    = WindowProc,
            .cbClsExtra     = 0,
            .cbWndExtra     = 0,
            .hInstance      = hInstance,
            .hIcon          = LoadIcon(NULL, IDI_APPLICATION),
            .hCursor        = LoadCursor(NULL, IDC_ARROW),
            .hbrBackground  = 0,
            .lpszMenuName   = 0,
            .lpszClassName  = wndClassName,
            .hIconSm        = LoadIcon(NULL, IDI_APPLICATION),
        };
        WinAssert(RegisterClassEx(&wndClass));
    }    

    void Create(const char* title, i32 width, i32 height, i32 xpos, i32 ypos)
    {
        hWnd = CreateWindowEx(
            0,                      //dwExStyle                  
            wndClassName,           //lpClassName                  
            title,                  //lpWindowName                 
            WS_OVERLAPPEDWINDOW,    //dwStyle                 
            xpos,                   //x
            ypos,                   //y    
            width,                  //nWidth
            height,                 //nHeight
            0,                      //hWndParent
            0,                      //hMenu
            hInstance,              //hInstance
            0                       //lpParam
        );
        WinAssert(hWnd);
    }

    ///////////////////////////////////////////////
    // Members
    ///////////////////////////////////////////////

    const char* wndClassName = "wnd";
    HWND hWnd;
    HINSTANCE hInstance = GetModuleHandle(NULL);
    
};

}//ns