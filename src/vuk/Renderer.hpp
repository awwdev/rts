#pragma once

#include "vuk/Context.hpp"
#include "vuk/Presentation.hpp"

///////////////////////////////////////////////////////////

namespace mini::vuk {
struct Renderer {

////////////////////////////////////////////////////////////

Context context;
Presentation presentation;

///////////////////////////////////////////////////////////

Renderer(WindowHandle const& wndHandle) : context { wndHandle }
{
}

///////////////////////////////////////////////////////////

};
}//ns