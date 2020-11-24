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
    commands.Destroy();
    states.Destroy();
    presentation.Destroy();   
    context.Destroy();
}

////////////////////////////////////////////////////////////

void Renderer::Update()
{
    presentation.Present(context, commands, states);
}

///////////////////////////////////////////////////////////

}//ns