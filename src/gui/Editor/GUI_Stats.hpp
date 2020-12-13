#pragma once

#include "gui/Widgets/Widget_Window.hpp"
#include "gpu/RenderData.hpp"

///////////////////////////////////////////////////////////

namespace rts::gui {

///////////////////////////////////////////////////////////

struct GUI_Stats
{
    Widget_Window wndStats 
    { 
        .rect  { 32, 32, 128, 128 },
        .title { "Stats", Colors::Orange }
    };

    void Render(gpu::RenderData&);
};

///////////////////////////////////////////////////////////

void GUI_Stats::Render(gpu::RenderData& renderData)
{
    auto& renderDataUI = renderData.renderDataUI;
    wndStats.Render(renderDataUI);
}

///////////////////////////////////////////////////////////

}//ns