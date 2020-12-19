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
        .rect  { 32, 32, 300, 128 },
        .title { "Stats", Colors::Orange },
    };
    Text fpsText { "fps" };
    Text dtText  { "dt" };

    void Update(gpu::RenderData&);
};

///////////////////////////////////////////////////////////

void GUI_Stats::Update(gpu::RenderData& rd)
{
    wndStats.Update(rd);

    if (app::Time::hasSecondPassed)
    {   
        fpsText.str.Clear();
        fpsText.str.Append("fps: ");
        fpsText.str.Append(app::Time::fps);
        dtText.str.Clear();
        dtText.str.Append("dt:  ");
        dtText.str.Append(app::Time::dt);
    }

    wndStats.UpdateText(rd.renderDataUI, fpsText);
    wndStats.UpdateText(rd.renderDataUI, dtText); 
}

///////////////////////////////////////////////////////////

}//ns