#include <thread>

#include "wnd/Window.hpp"
#include "mem/Memory.hpp"
#include "res/Resources.hpp"
#include "gpu/vuk/Renderer.hpp"
#include "net/Network.hpp"
#include "app/Scene.hpp"
#include "app/Global.hpp"
#include "app/Time.hpp"

///////////////////////////////////////////////////////////

using namespace rts;

///////////////////////////////////////////////////////////

inline void AppMain(gpu::vuk::WindowHandle wndHandle)
{  
    res::Resources resources;
    app::Scene scene;
    gpu::vuk::Renderer renderer { wndHandle, resources, scene.renderData };
    net::Network network;

    while(app::glo::isAppRunning)
    {
        scene.Update();
        renderer.Update(scene.renderData, resources);
        
        app::UpdateTime();
        app::PrintFps();

        if (app::HasEvent(app::EventEnum::KEY_DOWN_ESCAPE))
            app::glo::isAppRunning = false;

        app::glo::eventBuffer.Reset();
    }
}

///////////////////////////////////////////////////////////

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int)
{
    wnd::Console console { 600, 400, 64, 400 + 64 };
    mem::Allocate();
    mem::PrintAlloc();

    wnd::Window window { hInst, "mini window", 600, 400, 64, 64 };
    std::jthread appThread { AppMain, gpu::vuk::WindowHandle { window.hInstance, window.hWnd } };
    window.BlockingPollEvents(); 

    mem::Deallocate();
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

        app::UpdateTime();
        app::PrintFps();

        if (app::HasEvent(app::EventEnum::KEY_DOWN_ESCAPE))
            app::isAppRunning = false;
    }   
}
#endif

///////////////////////////////////////////////////////////