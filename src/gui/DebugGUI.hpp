#pragma once

#include "gui/Widgets/Window.hpp"
#include "gpu/RenderData.hpp"

///////////////////////////////////////////////////////////

namespace rts::gui {

///////////////////////////////////////////////////////////

struct DebugGUI
{
    Window wndStats { 32, 32, 128, 64 };

    void Update(gpu::RenderData&);
};

///////////////////////////////////////////////////////////

void DebugGUI::Update(gpu::RenderData& renderData)
{

}

///////////////////////////////////////////////////////////

}//ns