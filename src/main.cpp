#include "wnd/Window.hpp"
#include "mem/Memory.hpp"
#include "app/Global.hpp"
#include "gpu/vuk/Renderer.hpp"
#include "net/Network.hpp"
#include "res/Resources.hpp"
#include "com/Time.hpp"
#include "com/Clock.hpp"
#include "app/Scene.hpp"

#include <thread>

///////////////////////////////////////////////////////////

using namespace rts;

///////////////////////////////////////////////////////////

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    wnd::Console console { 600, 400, 64, 400 + 64 };
    mem::GlobalAlloc();
    mem::PrintAlloc();

    {
        wnd::Window window { "mini window", 600, 400, 64, 64 };
        res::Resources resources;
        gpu::vuk::Renderer renderer { { window.hInstance, window.hWnd }, resources };
        net::Network network;
        app::Scene scene;

        //! not stable yet
        std::jthread t {
            [&] {
                while(app::isAppRunning)
                {
                    scene.Update();
                    renderer.Update(scene.renderData, resources);
                    
                    com::dt::UpdateTime();
                    com::dt::PrintFps();

                    if (app::HasEvent(app::EventEnum::KEY_DOWN_ESCAPE))
                        app::isAppRunning = false;
                }
            }
        };

        while(app::isAppRunning)
        {
            window.Update(); 
        }
    }

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

    while(app::isAppRunning)
    {
        window.PollEvents();
        renderer.Update();

        com::dt::UpdateTime();
        com::dt::PrintFps();

        if (app::HasEvent(app::EventEnum::KEY_DOWN_ESCAPE))
            app::isAppRunning = false;
    }   
}
#endif

///////////////////////////////////////////////////////////