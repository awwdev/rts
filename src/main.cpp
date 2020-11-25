#include "wnd/Window.hpp"
#include "app/Global.hpp"
#include "vuk/Renderer.hpp"
#include "com/Time.hpp"
#include "com/Clock.hpp"

///////////////////////////////////////////////////////////

using namespace mini;

///////////////////////////////////////////////////////////

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    wnd::Console  console  { 600, 400, 64, 400 + 64 };
    wnd::Window   window   { "mini window", 600, 400, 64, 64 };
    vuk::Renderer renderer { { window.hInstance, window.hWnd } };

    while(app::glo::isAppRunning)
    {
        window.Update(); 
        renderer.Update();
        com::dt::UpdateTime();
        com::dt::PrintFps();

        if (app::glo::HasEvent(app::EventEnum::KEY_DOWN_ESCAPE))
            app::glo::isAppRunning = false;
    }

    return EXIT_SUCCESS;
}
#endif

///////////////////////////////////////////////////////////

#ifdef __linux__
int main()
{
    wnd::Window   window { "mini window", 600, 400, 64, 64 };
    vuk::Renderer renderer { { window.display, window.window } };

    while(app::glo::isAppRunning)
    {
        window.PollEvents();
    }   
}
#endif

///////////////////////////////////////////////////////////