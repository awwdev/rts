#include "wnd/Window.hpp"
#include "app/Global.hpp"
#include "vuk/Renderer.hpp"

using namespace mini;

///////////////////////////////////////////////////////////

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    wnd::Console  console  { 600, 400, 64, 400 + 64 };
    wnd::Window   window   { "mini window", 600, 400, 64, 64 };
    vuk::Renderer renderer { { window.hInstance, window.hWnd } };

    while(app::isAppRunning)
    {
        window.PollEvents(); 
        //presentation.Present(context);
    }

    return EXIT_SUCCESS;
}
#endif

///////////////////////////////////////////////////////////

#ifdef __linux__
int main()
{
    wnd::Window   window;
    vuk::Renderer renderer { { window.display, window.window } };

    while(app::isAppRunning)
    {
        window.PollEvents();
    }   
}
#endif

///////////////////////////////////////////////////////////
