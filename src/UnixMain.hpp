#pragma once

#include "app/CmdArgs.hpp"
#include "wnd/Unix/UnixWindow.hpp"
#include "net/Unix/UnixNetwork.hpp"
#include "mem/Memory.hpp"
#include "res/Resources.hpp"
#include "gpu/vuk/Renderer.hpp"
#include "app/GameScene.hpp"
#include "app/Time.hpp"
#include "app/Inputs.hpp"

///////////////////////////////////////////////////////////

namespace rts::app {

///////////////////////////////////////////////////////////

static void AppMain(CmdArgs const& cmdArgs)
{
    wnd::UnixWindow window { "mini window", 600, 400, 64, 64 };

    mem::Allocate();
    mem::PrintAlloc();
    {
        auto ptrResources = mem::ClaimBlock<res::Resources>();
        auto ptrScene     = mem::ClaimBlock<app::GameScene>();
        auto ptrRenderer  = mem::ClaimBlock<gpu::vuk::Renderer>
        (gpu::vuk::WindowHandle { window.display, window.window }, *ptrResources, ptrScene->renderData);
        auto ptrNetwork   = mem::ClaimBlock<net::UnixNetwork>(cmdArgs);

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

///////////////////////////////////////////////////////////

}//ns