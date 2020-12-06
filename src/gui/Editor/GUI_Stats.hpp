#pragma once

#include "gui/Widgets/Widget_Window.hpp"
#include "gpu/RenderData.hpp"

///////////////////////////////////////////////////////////

namespace rts::gui {

///////////////////////////////////////////////////////////

struct GUI_Stats
{
    Widget_Window wndStats { 32, 32, 128, 64 };

    void Update(gpu::RenderData&);
};

///////////////////////////////////////////////////////////

void GUI_Stats::Update(gpu::RenderData& renderData)
{
    auto& renderDataUI = renderData.renderDataUI;
    wndStats.Update(renderDataUI);
}

///////////////////////////////////////////////////////////

}//ns