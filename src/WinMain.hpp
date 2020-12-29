#pragma once

#include <thread>
#include "app/CmdArgs.hpp"
#include "wnd/Win32/Win32_Window.hpp"
#include "wnd/Win32/Win32_Console.hpp"
#include "mem/Memory.hpp"
#include "res/Resources.hpp"
#include "gpu/vuk/Renderer.hpp"
#include "net/Win32/Win32_Network.hpp"
#include "app/GameScene.hpp"
#include "app/Time.hpp"
#include "app/Inputs.hpp"

///////////////////////////////////////////////////////////

namespace rts::app {

///////////////////////////////////////////////////////////

inline void AppThread(gpu::vuk::WindowHandle wndHandle, app::CmdArgs const& cmdArgs)
{  
    mem::Allocate();
    mem::PrintAlloc();
    {
        auto ptrResources = mem::ClaimBlock<res::Resources>();
        auto ptrScene     = mem::ClaimBlock<app::GameScene>();
        auto ptrRenderer  = mem::ClaimBlock<gpu::vuk::Renderer>(wndHandle, *ptrResources, ptrScene->renderData);
        auto ptrNetwork   = mem::ClaimBlock<net::Win32_Network>(cmdArgs);

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

static void AppMain(CmdArgs const& cmdArgs)
{
    wnd::Win32_Console console { cmdArgs };
    wnd::Win32_Window window { GetModuleHandle(NULL), "mini window", cmdArgs };
    std::thread appThread { AppThread, gpu::vuk::WindowHandle { window.hInstance, window.hWnd }, cmdArgs };
    window.BlockingPollEvents(); 
    appThread.join();
    return EXIT_SUCCESS;
}

///////////////////////////////////////////////////////////

}//ns