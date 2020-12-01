#include "wnd/Window.hpp"
#include "mem/Memory.hpp"
#include "app/Global.hpp"
#include "gpu/vuk/Renderer.hpp"
#include "net/Network.hpp"
#include "res/Resources.hpp"
#include "com/Time.hpp"
#include "com/Clock.hpp"
#include "app/Scene.hpp"

#include <cmath>

///////////////////////////////////////////////////////////

using namespace mini;

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

        //test
        {
            auto  ID = scene.ecs.AddEntity();
            auto& mainComponent = scene.ecs.arrays.Add<ecs::MainComponent>(ID);
            mainComponent.pos  = { 16, 16 };
            mainComponent.size = { 32, 32 };
            mainComponent.textureId = 0;
        }
        {
            auto  ID = scene.ecs.AddEntity();
            auto& mainComponent = scene.ecs.arrays.Add<ecs::MainComponent>(ID);
            mainComponent.pos  = { 16 + 32, 16 };
            mainComponent.size = { 32, 32 };
            mainComponent.textureId = 1;
        }
        
        while(app::glo::isAppRunning)
        {
            window.Update(); 
            scene.Update();
            renderer.Update(scene.renderData, resources);
            
            com::dt::UpdateTime();
            com::dt::PrintFps();

            if (app::glo::HasEvent(app::EventEnum::KEY_DOWN_ESCAPE))
                app::glo::isAppRunning = false;
        }
    }

    mem::GlobalDealloc();
    return EXIT_SUCCESS;
}
#endif

struct Foo {} constexpr foo;

///////////////////////////////////////////////////////////

#ifdef __linux__
int main()
{
    wnd::Window   window { "mini window", 600, 400, 64, 64 };
    gpu::vuk Renderer renderer { { window.display, window.window } };

    //TODO socket
    //TODO mem

    while(app::glo::isAppRunning)
    {
        window.PollEvents();
        renderer.Update();

        com::dt::UpdateTime();
        com::dt::PrintFps();

        if (app::glo::HasEvent(app::EventEnum::KEY_DOWN_ESCAPE))
            app::glo::isAppRunning = false;
    }   
}
#endif

///////////////////////////////////////////////////////////