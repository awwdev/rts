#pragma once

#include "gui/Widgets/Widget_Window.hpp"
#include "gpu/RenderData.hpp"
#include "app/Time.hpp"

///////////////////////////////////////////////////////////

namespace rts::gui {

///////////////////////////////////////////////////////////

struct GUI_Stats
{
    Widget_Window wndStats 
    { 
        .rect  { 32, 32, 300, 300 },
        .title { "Stats", Colors::Orange },
    };
    Text fpsText { "fps" };

    void Update(gpu::RenderData&);
};

///////////////////////////////////////////////////////////

void GUI_Stats::Update(gpu::RenderData& rd)
{
    wndStats.Update(rd);

    fpsText.str.Clear();
    fpsText.str.Append("fps: ");
    fpsText.str.Append(app::Time::fps);
    wndStats.UpdateText(rd.renderDataUI, fpsText);
}

///////////////////////////////////////////////////////////

}//ns