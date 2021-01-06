#pragma once

#include "gui/Widgets/WidgetWindow.hpp"
#include "gpu/RenderData.hpp"
#include "app/Time.hpp"
#include "cmd/Timeline.hpp"

///////////////////////////////////////////////////////////

namespace rts::gui {

///////////////////////////////////////////////////////////

struct GUI_Stats
{
    WidgetWindow wndStats 
    { 
        .rect  { .p1 {32, 32}, .p2 {300, 128} },
        .title { "Stats", Colors::Orange },
    };
    Text fpsText { "fps:  " };
    Text dtText  { "ftm:  " };
    Text stepText{ "step: " };

    void Update(gpu::RenderData&, cmd::Timeline&);
};

///////////////////////////////////////////////////////////

void GUI_Stats::Update(gpu::RenderData& rd, cmd::Timeline& timeline)
{
    wndStats.Update(rd);

    fpsText.str.Clear(6);
    fpsText.str.Append(app::Time::fps);
    dtText.str.Clear(6);
    dtText.str.Append(app::Time::frameTime);
    stepText.str.Clear(6);
    stepText.str.Append(timeline.stepIdx);

    wndStats.UpdateText(rd.ui, fpsText);
    wndStats.UpdateText(rd.ui, dtText); 
    wndStats.UpdateText(rd.ui, stepText); 
}

///////////////////////////////////////////////////////////

}//ns