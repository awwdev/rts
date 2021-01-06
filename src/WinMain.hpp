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
#include "app/Input/Inputs.hpp"

///////////////////////////////////////////////////////////

namespace rts::app {

///////////////////////////////////////////////////////////

inline void AppThread(gpu::vuk::WindowHandle wndHandle, CmdArgs const& cmdArgs)
{  
    USING_NAMESPACES
    Allocate();
    {
        auto ptrResources = ClaimBlock<Resources>();
        auto ptrScene     = ClaimBlock<GameScene>();
        auto ptrRenderer  = ClaimBlock<vuk::Renderer>(wndHandle, *ptrResources, ptrScene->renderData);
        auto ptrNetwork   = ClaimBlock<Win32_Network>(cmdArgs);

        while(!app::Inputs::window.shouldClose)
        {
            Time::Update();
            Inputs::Update();
            ptrScene->Update();
            ptrRenderer->Update(ptrScene->renderData, *ptrResources);
        } 
    }
    Deallocate();
}

///////////////////////////////////////////////////////////

static void AppMain(CmdArgs const& cmdArgs)
{
    USING_NAMESPACES
    Win32_Console console { cmdArgs };
    Win32_Window window { GetModuleHandle(NULL), "mini window", cmdArgs };
    std::thread appThread { AppThread, vuk::WindowHandle { window.hInstance, window.hWnd }, cmdArgs };
    window.BlockingPollEvents(); 
    appThread.join();
}

///////////////////////////////////////////////////////////

}//ns