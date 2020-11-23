#pragma once

#include "vuk/Context.hpp"
#include "vuk/Presentation.hpp"

namespace mini::vuk {

///////////////////////////////////////////////////////////

struct Renderer 
{
    Context context;
    Presentation presentation;

    Renderer(WindowHandle const&);
    ~Renderer(); 
};

///////////////////////////////////////////////////////////

Renderer::Renderer(WindowHandle const& wndHandle)
{
    context.Create(wndHandle);
    presentation.Create();
}

///////////////////////////////////////////////////////////

Renderer::~Renderer()
{
    presentation.Destroy();   
    context.Destroy();
}

////////////////////////////////////////////////////////////

}//ns