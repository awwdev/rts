#pragma once
#include <X11/Xlib.h>
#include "com/Types.hpp"
#include "com/Print.hpp"

///////////////////////////////////////////////////////////

namespace mini::wnd {

///////////////////////////////////////////////////////////

struct X11_Window {

///////////////////////////////////////////////////////////
    
PRIVATE ::Window windowId;

///////////////////////////////////////////////////////////

PUBLIC X11_Window(
    chars_t title  = "Window",
    i32 width  = 600,
    i32 height = 400,
    i32 xpos   = 64,
    i32 ypos   = 64)
{
    

    /*
    windowId = XCreateWindow(
        display,    //display
        0,          //parent
        xpos,       //xpos
        ypos,       //ypos
        width,      //width
        height,     //height
        1,          //border
        1,          //depth
        0,          //clazz
        0,          //visual
        0,          //mask
        0           //attributes
    );
    */

    Display* display = XOpenDisplay(NULL);
    if (display == NULL)
        com::PrintError("NULL");
    auto defaultScreen = DefaultScreen(display);
    windowId = XCreateSimpleWindow(
        display,
        RootWindow(display, defaultScreen),
        xpos,
        ypos,
        width,
        height,
        1,
        BlackPixel(display, defaultScreen),
        WhitePixel(display, defaultScreen)
    );

    XSelectInput(display, windowId, ExposureMask | KeyPressMask);
    XMapWindow(display, windowId);

    XEvent e;
    while(1) {
        XNextEvent(display, &e);
        if (e.type == Expose) 
        {
            XFillRectangle(display, windowId, DefaultGC(display, defaultScreen), 20, 20, 10, 10);
            XDrawString(display, windowId, DefaultGC(display, defaultScreen), 10, 50, "string", 6);
        }
        if (e.type == KeyPress)
            break;
    }

    XCloseDisplay(display);

}

///////////////////////////////////////////////////////////

};  

///////////////////////////////////////////////////////////

}//ns