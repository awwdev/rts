#include <thread>

#include "wnd/Window.hpp"
#include "mem/Memory.hpp"
#include "res/Resources.hpp"
#include "gpu/vuk/Renderer.hpp"
#include "net/Network.hpp"
#include "app/Scene.hpp"
#include "app/Global.hpp"
#include "app/Time.hpp"

#include "com/String.hpp"

///////////////////////////////////////////////////////////

using namespace rts;

///////////////////////////////////////////////////////////

inline void AppMain(gpu::vuk::WindowHandle wndHandle)
{  
    auto ptrResources = mem::ClaimBlock<res::Resources>();
    auto ptrScene     = mem::ClaimBlock<app::Scene>();
    auto ptrRenderer  = mem::ClaimBlock<gpu::vuk::Renderer>(wndHandle, *ptrResources, ptrScene->renderData);
    net::Network network;

    while(app::glo::isAppRunning)
    {
        app::glo::eventBuffer.Poll();

        ptrScene->Update();
        ptrRenderer->Update(ptrScene->renderData, *ptrResources);
        
        app::UpdateTime();
        app::PrintFps();

        if (app::HasEvent(app::EventEnum::KEY_DOWN_ESCAPE))
            app::glo::isAppRunning = false;
    }
}

///////////////////////////////////////////////////////////

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int)
{
    wnd::Console console { 600, 400, 64, 400 + 64 };
    mem::Allocate();
    mem::PrintAlloc();

    //test
    com::String<100> str { "String" };
    com::String<100> str2;
    str.Append("hello");
    str = "test";
    str.Append(123);
    str2 = str;
    str2.Append(str);
    com::Print(str2);

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