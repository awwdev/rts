#pragma once

#include "vuk/Renderer/Context.hpp"
#include "vuk/Renderer/Presentation.hpp"
#include "vuk/Renderer/States.hpp"
#include "vuk/Renderer/Commands.hpp"

///////////////////////////////////////////////////////////

namespace mini::vuk {

///////////////////////////////////////////////////////////

struct Renderer 
{
    Context context;
    Presentation presentation;
    States states;
    Commands commands;

    Renderer(WindowHandle const&);
    ~Renderer(); 
    void Update();
};

///////////////////////////////////////////////////////////

Renderer::Renderer(WindowHandle const& wndHandle)
{
    context.Create(wndHandle);
    presentation.Create(context);
    states.Create(context); 
    commands.Create(context.physical.queueIndex);
}

///////////////////////////////////////////////////////////

Renderer::~Renderer()
{
    vkDeviceWaitIdle(g_devicePtr);
    commands.Destroy();
    states.Destroy();
    presentation.Destroy();   
    context.Destroy();
}

////////////////////////////////////////////////////////////

void Renderer::Update()
{
    if (app::glo::windowHeight <= 0 || app::glo::windowWidth <= 0)
        return;

    if (app::glo::HasEvent(app::EventEnum::WND_MOVE_SIZE))
    {
        vkDeviceWaitIdle(g_devicePtr);

        commands.Destroy();
        states.Destroy();
        presentation.Destroy();   
        context.swapchain.Destroy();

        context.surface.UpdateSurfaceCapabilities(context.physical);
        context.swapchain.Create(context.device, context.surface);
        presentation.Create(context);
        states.Create(context); 
        commands.Create(context.physical.queueIndex);
    }

    presentation.Present(context, commands, states);
}

///////////////////////////////////////////////////////////

}//ns