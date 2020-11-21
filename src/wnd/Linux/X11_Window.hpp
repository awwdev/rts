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
PRIVATE Atom wm_delete_window;

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

    wm_delete_window = XInternAtom(display, "WM_DELETE_WINDOW", false);
    XSetWMProtocols(display, windowId, &wm_delete_window, 1);
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
    while(XCheckWindowEvent(display, windowId, 0xFFFFFFFF, &e))
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

    if (XCheckTypedWindowEvent(display, windowId, ClientMessage, &e))
    {
        if (e.xclient.message_type == wm_protocols &&
            e.xclient.data.l[0]    == wm_delete_window)
        {
            com::Print("Close");
            app::isAppRunning = false;
        }
    }
}

///////////////////////////////////////////////////////////

};  

///////////////////////////////////////////////////////////

}//ns