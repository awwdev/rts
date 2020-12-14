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
        .rect  { 32, 32, 300, 300 },
        .title { "Stats", Colors::Orange, EDITOR_FONT },
    };

    void Render(gpu::RenderData&);
};

///////////////////////////////////////////////////////////

void GUI_Stats::Render(gpu::RenderData& renderData)
{
    wndStats.Render(renderData);
}

///////////////////////////////////////////////////////////

}//ns