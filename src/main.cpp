#include <thread>

#include "wnd/Window.hpp"
#include "mem/Memory.hpp"
#include "res/Resources.hpp"
#include "gpu/vuk/Renderer.hpp"
#include "net/Network.hpp"

#include "app/Scene.hpp"
#include "app/Time.hpp"
#include "app/Inputs.hpp"

///////////////////////////////////////////////////////////

using namespace rts;

///////////////////////////////////////////////////////////

inline void AppMain(gpu::vuk::WindowHandle wndHandle)
{  
    auto ptrResources = mem::ClaimBlock<res::Resources>();
    auto ptrScene     = mem::ClaimBlock<app::Scene>();
    auto ptrRenderer  = mem::ClaimBlock<gpu::vuk::Renderer>(wndHandle, *ptrResources, ptrScene->renderData);
    net::Network network;

    while(!app::Inputs::window.shouldClose)
    {
        app::Time::Update();
        //app::Time::PrintFps();
        app::Inputs::Update();
        ptrScene->Update();
        ptrRenderer->Update(ptrScene->renderData, *ptrResources);
    }   
}

///////////////////////////////////////////////////////////

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int)
{
    mem::Allocate();
    mem::PrintAlloc();
    wnd::Console console { 600, 400, 64, 400 + 64 };
    wnd::Window window { hInst, "mini window", 600, 400, 64, 64 };
    std::thread appThread { AppMain, gpu::vuk::WindowHandle { window.hInstance, window.hWnd } };
    window.BlockingPollEvents(); 
    appThread.join();
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