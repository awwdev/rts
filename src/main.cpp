#include <thread>

#include "wnd/Window.hpp"
#include "mem/Memory.hpp"
#include "res/Resources.hpp"
#include "gpu/vuk/Renderer.hpp"
#include "net/Network.hpp"

#include "app/GameScene.hpp"
#include "app/Time.hpp"
#include "app/Inputs.hpp"

///////////////////////////////////////////////////////////

using namespace rts;

///////////////////////////////////////////////////////////

inline void AppMain(gpu::vuk::WindowHandle wndHandle)
{  
    mem::Allocate();
    mem::PrintAlloc();
    {
        auto ptrResources = mem::ClaimBlock<res::Resources>();
        auto ptrScene     = mem::ClaimBlock<app::GameScene>();
        auto ptrRenderer  = mem::ClaimBlock<gpu::vuk::Renderer>(wndHandle, *ptrResources, ptrScene->renderData);
        auto ptrNetwork   = mem::ClaimBlock<net::Network>();
        
        while(!app::Inputs::window.shouldClose)
        {
            app::Time::Update();
            app::Inputs::Update();
            ptrScene->Update();
            ptrRenderer->Update(ptrScene->renderData, *ptrResources);
        } 
    }
    mem::Deallocate();
}

///////////////////////////////////////////////////////////

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int)
{
    wnd::Console console { 600, 400, 64, 400 + 64 };
    wnd::Window window { hInst, "mini window", 600, 400, 64, 64 };
    std::thread appThread { AppMain, gpu::vuk::WindowHandle { window.hInstance, window.hWnd } };
    window.BlockingPollEvents(); 
    appThread.join();
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