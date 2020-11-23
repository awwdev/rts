#pragma once

#include "vuk/Context.hpp"
#include "vuk/Presentation.hpp"
#include "vuk/States.hpp"

#include <thread>

namespace mini::vuk {

///////////////////////////////////////////////////////////

struct Renderer 
{
    Context context;
    Presentation presentation;
    States states;

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
}

///////////////////////////////////////////////////////////

Renderer::~Renderer()
{
    states.Destroy();
    presentation.Destroy();   
    context.Destroy();
}

////////////////////////////////////////////////////////////

void Renderer::Update()
{
    //presentation.Present(context);
}

///////////////////////////////////////////////////////////

}//ns