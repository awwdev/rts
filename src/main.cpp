#include "wnd/Window.hpp"

using namespace mini;

///////////////////////////////////////////////////////////

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    wnd::Console console { 600, 400, 64, 400 + 64 };
    wnd::Window  window  { "mini window", 600, 400, 64, 64 };

    com::PrintWarning("Hello");

    while(true)
    {
        window.PollEvents();
    }
}
#endif

///////////////////////////////////////////////////////////

#ifdef __linux__

#endif

///////////////////////////////////////////////////////////
