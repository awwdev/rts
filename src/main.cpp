#include "wnd/Window.hpp"
#include "app/Global.hpp"
#include "vuk/Context.hpp"

using namespace mini;

///////////////////////////////////////////////////////////

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    wnd::Console console { 600, 400, 64, 400 + 64 };
    wnd::Window  window  { "mini window", 600, 400, 64, 64 };
    vuk::Context context {};

    while(app::isAppRunning)
    {
        window.PollEvents();
    }

    return EXIT_SUCCESS;
}
#endif

///////////////////////////////////////////////////////////

#ifdef __linux__
int main()
{
    mini::wnd::Window window;
    while(app::isAppRunning)
    {
        window.PollEvents();
    }   
}
#endif

///////////////////////////////////////////////////////////
