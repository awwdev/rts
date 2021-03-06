#pragma once

#include "com/Unix.hpp"
#include "com/Types.hpp"
#include "com/Print.hpp"
#include "app/Input/Inputs.hpp"

///////////////////////////////////////////////////////////

namespace rts::wnd {

///////////////////////////////////////////////////////////

struct UnixWindow
{
    ::Window window;
    ::Display* display;
    int screen;
    Atom wmDeleteWindow;

    UnixWindow(chars_t, i32, i32, i32, i32);
    ~UnixWindow();
    void PollEvents();
};

///////////////////////////////////////////////////////////
    
UnixWindow::UnixWindow(
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

    XSelectInput(display, window, 
    ExposureMask | KeyPressMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask);
    XMapWindow(display, window);

    wmDeleteWindow = XInternAtom(display, "WM_DELETE_WINDOW", false);
    XSetWMProtocols(display, window, &wmDeleteWindow, 1);

    app::Inputs::window.width = width;
    app::Inputs::window.height = height;
}

///////////////////////////////////////////////////////////

UnixWindow::~UnixWindow()
{
    XDestroyWindow(display, window);
}

///////////////////////////////////////////////////////////

void UnixWindow::PollEvents()
{
    XEvent event;
    while(XCheckWindowEvent(display, window, 0xFFFFFFFF, &event))
    {
        app::Input input {};
        XWindowAttributes attributes;

        //TODO: NO NEED FOR INPUT BUFFER, JUST WRITE INTO THE GLOBAL STRUCT

        switch(event.type)
        {
            case KeyPress:
                input.type = app::Input::Keyboard;
                input.key.value = event.xkey.keycode;
                input.key.state = app::InputKey::Down;
                app::Inputs::inputBuffer.Write(input);
            break;

            case Expose:
                XGetWindowAttributes(display, window, &attributes);
                input.type = app::Input::Window;
                input.window.sizeState = app::InputWindow::End;
                input.window.width = attributes.width;
                input.window.height = attributes.height;
                app::Inputs::inputBuffer.Write(input);
            break;

            case ButtonPress:
                input.type = app::Input::Mouse;
                input.mouse.buttons[app::InputMouse::Left] = app::InputMouse::Pressed;
                input.mouse.pos.x = event.xbutton.x;
                input.mouse.pos.y = event.xbutton.y;
                app::Inputs::inputBuffer.Write(input);
            break;

            case ButtonRelease:
                input.type = app::Input::Mouse;
                input.mouse.buttons[app::InputMouse::Left] = app::InputMouse::Released;
                input.mouse.pos.x = event.xbutton.x;
                input.mouse.pos.y = event.xbutton.y;
                app::Inputs::inputBuffer.Write(input);
            break;

            case MotionNotify:
                input.type = app::Input::Mouse;
                input.mouse.pos.x = event.xbutton.x;
                input.mouse.pos.y = event.xbutton.y;
                app::Inputs::inputBuffer.Write(input);
            break;
        }
    }

    //int a, b, c, d;
    //unsigned f;
    //Window w1, w2;
    //XQueryPointer(display, window, &w1, &w2, &a, &b, &c, &d, &f);
    //com::Print(a,b,c,d,f);

    //close button
    if (XCheckTypedWindowEvent(display, window, ClientMessage, &event))
    {
        if ((unsigned long)event.xclient.data.l[0] == wmDeleteWindow)
        {
            app::Input input {};
            input.type = app::Input::Window;
            input.window.shouldClose = true;
            app::Inputs::inputBuffer.Write(input);
        }
    }
}

///////////////////////////////////////////////////////////

}//ns