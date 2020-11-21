#pragma once
#include <X11/Xlib.h>
#include "com/Types.hpp"
#include "com/Print.hpp"
#include "app/Global.hpp"

///////////////////////////////////////////////////////////

namespace mini::wnd {

///////////////////////////////////////////////////////////

struct X11_Window {

///////////////////////////////////////////////////////////
    
PRIVATE ::Window windowId;
PRIVATE ::Display* display;
PRIVATE int screen;

///////////////////////////////////////////////////////////

PUBLIC X11_Window(
    chars_t title  = "Window",
    i32 width  = 600,
    i32 height = 400,
    i32 xpos   = 64,
    i32 ypos   = 64)
{
    display  = XOpenDisplay(NULL);
    screen   = DefaultScreen(display);

    windowId = XCreateSimpleWindow(
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

    XSelectInput(display, windowId, ExposureMask | KeyPressMask);
    XMapWindow(display, windowId);

    Atom wmDelete = XInternAtom(display, "WM_DELETE_WINDOW", true);
    XSetWMProtocols(display, windowId, &wmDelete, 1);
}

///////////////////////////////////////////////////////////

PUBLIC ~X11_Window()
{
    //XCloseDisplay(display);
}

///////////////////////////////////////////////////////////

PUBLIC void PollEvents()
{
    XEvent e;
    XNextEvent(display, &e);

    switch(e.type)
    {
        case KeyPress:
        {
            app::isAppRunning = false;
        } 
        break;

        case ClientMessage:
        {
            app::isAppRunning = false;
        }
        break;
    }
}

///////////////////////////////////////////////////////////

};  

///////////////////////////////////////////////////////////

}//ns