#pragma once

#include <X11/Xlib.h>
#include "com/Types.hpp"
#include "com/Print.hpp"
#include "app/Global.hpp"

///////////////////////////////////////////////////////////

namespace mini::wnd {

///////////////////////////////////////////////////////////

struct X11_Window
{
    ::Window window;
    ::Display* display;
    int screen;
    Atom wmDeleteWindow;

    X11_Window(chars_t, i32, i32, i32, i32);
    ~X11_Window();
    void PollEvents();
};

///////////////////////////////////////////////////////////
    
X11_Window::X11_Window(
chars_t title  = "Window",
i32 width  = 600,
i32 height = 400,
i32 xpos   = 64,
i32 ypos   = 64)
{
    display  = XOpenDisplay(NULL);
    screen   = DefaultScreen(display);

    window = XCreateSimpleWindow(
        display,
        RootWindow(display, screen),
        xpos,
        ypos,
        width,
        height,
        1,
        BlackPixel(display, screen),
        WhitePixel(display, screen)
    );

    XStoreName(display, window, title);

    XSelectInput(display, window, ExposureMask | KeyPressMask);
    XMapWindow(display, window);

    wmDeleteWindow = XInternAtom(display, "WM_DELETE_WINDOW", false);
    XSetWMProtocols(display, window, &wmDeleteWindow, 1);
}

///////////////////////////////////////////////////////////

X11_Window::~X11_Window()
{
    //XCloseDisplay(display);
}

///////////////////////////////////////////////////////////

void X11_Window::PollEvents()
{
    XEvent e;
    while(XCheckWindowEvent(display, window, 0xFFFFFFFF, &e))
    {
        switch(e.type)
        {
            case KeyPress:
            {
                app::isAppRunning = false;
            } 
            break;
        }
    }

    if (XCheckTypedWindowEvent(display, window, ClientMessage, &e))
    {
        if ((unsigned long)e.xclient.data.l[0] == wmDeleteWindow)
        {
            com::Print("Close");
            app::isAppRunning = false;
        }
    }
}

///////////////////////////////////////////////////////////

}//ns