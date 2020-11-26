#include "wnd/Window.hpp"
#include "mem/Memory.hpp"
#include "app/Global.hpp"
#include "gpu/vuk/Renderer.hpp"
#include "net/UdpSocket.hpp"
#include "com/Time.hpp"
#include "com/Clock.hpp"
#include "app/Scene.hpp"

///////////////////////////////////////////////////////////

using namespace mini;

///////////////////////////////////////////////////////////

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    wnd::Console console { 600, 400, 64, 400 + 64 };
    mem::GlobalAlloc();
    mem::PrintAlloc();
    net::InitializeWinsock();

    {
        wnd::Window window { "mini window", 600, 400, 64, 64 };
        gpu::vuk::Renderer renderer { { window.hInstance, window.hWnd } };
        net::UdpSocket socket;
        app::Scene scene;

        while(app::glo::isAppRunning)
        {
            window.Update(); 
            scene.Update();
            renderer.Update();
            
            com::dt::UpdateTime();
            com::dt::PrintFps();

            if (app::glo::HasEvent(app::EventEnum::KEY_DOWN_ESCAPE))
                app::glo::isAppRunning = false;
        }
    }

    net::DestroyWinsock();
    mem::GlobalDealloc();
    return EXIT_SUCCESS;
}
#endif

///////////////////////////////////////////////////////////

#ifdef __linux__
int main()
{
    wnd::Window   window { "mini window", 600, 400, 64, 64 };
    gpu::vuk Renderer renderer { { window.display, window.window } };

    //TODO socket
    //TODO mem

    while(app::glo::isAppRunning)
    {
        window.PollEvents();
        renderer.Update();

        com::dt::UpdateTime();
        com::dt::PrintFps();

        if (app::glo::HasEvent(app::EventEnum::KEY_DOWN_ESCAPE))
            app::glo::isAppRunning = false;
    }   
}
#endif

///////////////////////////////////////////////////////////