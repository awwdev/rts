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

inline void AppMain(gpu::vuk::WindowHandle wndHandle)
{  
    res::Resources resources;
    gpu::vuk::Renderer renderer { wndHandle, resources };
    net::Network network;
    app::Scene scene;

    while(app::isAppRunning)
    {
        app::events.count = 0;
        while(auto optEv = app::eventBuffer.Poll())
        {
            app::events.Append(optEv.Data());
        }

        scene.Update();
        renderer.Update(scene.renderData, resources);
        
        com::dt::UpdateTime();
        com::dt::PrintFps();

        if (app::HasEvent(app::EventEnum::KEY_DOWN_ESCAPE))
            app::isAppRunning = false;
    }
}

///////////////////////////////////////////////////////////

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int)
{
    wnd::Console console { 600, 400, 64, 400 + 64 };
    mem::GlobalAlloc();
    mem::PrintAlloc();

    wnd::Window window { hInst, "mini window", 600, 400, 64, 64 };
    std::jthread appThread { AppMain, gpu::vuk::WindowHandle { window.hInstance, window.hWnd } };
    window.BlockingPollEvents(); 

    mem::GlobalDealloc();
    return EXIT_SUCCESS;
}
#endif

///////////////////////////////////////////////////////////

#ifdef __linux__
int main()
{
    wnd::Window window { "mini window", 600, 400, 64, 64 };
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