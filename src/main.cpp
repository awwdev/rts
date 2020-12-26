#include <thread>

#include "wnd/Window.hpp"
#include "mem/Memory.hpp"
#include "res/Resources.hpp"
#include "gpu/vuk/Renderer.hpp"
#include "net/Network.hpp"

#include "app/CmdArgs.hpp"
#include "app/GameScene.hpp"
#include "app/Time.hpp"
#include "app/Inputs.hpp"

///////////////////////////////////////////////////////////

using namespace rts;

///////////////////////////////////////////////////////////

inline void AppMain(gpu::vuk::WindowHandle wndHandle, app::CmdArgs const& cmdArgs)
{  
    mem::Allocate();
    mem::PrintAlloc();
    {
        auto ptrResources = mem::ClaimBlock<res::Resources>();
        auto ptrScene     = mem::ClaimBlock<app::GameScene>();
        auto ptrRenderer  = mem::ClaimBlock<gpu::vuk::Renderer>(wndHandle, *ptrResources, ptrScene->renderData);
        auto ptrNetwork   = mem::ClaimBlock<net::Network>(cmdArgs);

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
int main(int argc, char** argv)
{   
    app::CmdArgs cmdArgs { argc, argv };
    wnd::Console console { cmdArgs };
    wnd::Window window { GetModuleHandle(NULL), "mini window", cmdArgs };
    std::thread appThread { AppMain, gpu::vuk::WindowHandle { window.hInstance, window.hWnd }, cmdArgs };
    window.BlockingPollEvents(); 
    appThread.join();
    return EXIT_SUCCESS;
}
#endif

///////////////////////////////////////////////////////////

#ifdef __linux__
int main(int argc, char** argv)
{
    app::CmdArgs cmdArgs { argc, argv };
    wnd::Window window { "mini window", 600, 400, 64, 64 };

    mem::Allocate();
    mem::PrintAlloc();
    {
        auto ptrResources = mem::ClaimBlock<res::Resources>();
        auto ptrScene     = mem::ClaimBlock<app::GameScene>();
        auto ptrRenderer  = mem::ClaimBlock<gpu::vuk::Renderer>
        (gpu::vuk::WindowHandle { window.display, window.window }, *ptrResources, ptrScene->renderData);
        auto ptrNetwork   = mem::ClaimBlock<net::Network>(cmdArgs);

        while(!app::Inputs::window.shouldClose)
        {
            window.PollEvents();
            app::Time::Update();
            app::Inputs::Update();
            ptrScene->Update();
            ptrRenderer->Update(ptrScene->renderData, *ptrResources);
        } 
    }
    mem::Deallocate();
}
#endif

///////////////////////////////////////////////////////////