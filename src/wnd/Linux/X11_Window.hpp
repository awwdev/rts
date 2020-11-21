#pragma once
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>
#include "com/Types.hpp"
#include "com/Print.hpp"

///////////////////////////////////////////////////////////

namespace mini::wnd {

///////////////////////////////////////////////////////////

struct X11_Window {

///////////////////////////////////////////////////////////
    
PRIVATE Window windowId;

///////////////////////////////////////////////////////////

PUBLIC X11_Window(
    chars_t title  = "Window",
    i32 width  = 600,
    i32 height = 400,
    i32 xpos   = 64,
    i32 ypos   = 64)
{
    windowId = XCreateWindow(
        0,          //display
        0,          //paren
        xpos,       //xpos
        ypos,       //ypos
        width,      //width
        height,     //height
        0,          //border
        0,          //depth
        0,          //clazz
        0,          //visual
        0,          //mask
        0           //attributes
    );

}

///////////////////////////////////////////////////////////

};  

///////////////////////////////////////////////////////////

}//ns