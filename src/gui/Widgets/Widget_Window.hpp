#pragma once

#include "gui/GUI_Base.hpp"
#include "com/Rect.hpp"
#include "gpu/RenderData.hpp"
#include "com/String.hpp"

///////////////////////////////////////////////////////////

namespace rts::gui {

///////////////////////////////////////////////////////////

struct Widget_Window 
{
    static constexpr i32 BAR_H = 24;
    static constexpr Col4n WND_COL_BACK     { 0.f, 0.f, 0.f, 0.25 };
    static constexpr Col4n WND_COL_BAR      { 0.1, 0.1, 0.1, 1.f };
    static constexpr Col4n WND_COL_SIZE_BTN { 0.1, 0.1, 0.1, 1.f };
    static constexpr Col4n WND_COL_MIN_BTN  { 0.2, 0.2, 0.2, 1.f };
    static constexpr Col4n WND_COL_ACTIVE   { 0.8, 0.2, 0.2, 1.f };
    static constexpr i32 RESIZE_BTN = 8;

    com::Recti rect;
    com::Recti limits { BAR_H, BAR_H, i32min, i32max };
    Text title;

    void Render(gpu::RenderData&);
};

///////////////////////////////////////////////////////////

void Widget_Window::Render(gpu::RenderData& rd)
{
    com::Recti wndBar  { rect.x, rect.y, rect.w, BAR_H };
    com::Recti btnSize { rect.x + rect.w - RESIZE_BTN, rect.y + rect.h - RESIZE_BTN, RESIZE_BTN, RESIZE_BTN };
    com::Recti btnMin  { rect.x + rect.w - BAR_H, rect.y, BAR_H, BAR_H };
    title.Center(wndBar);

    bool onBtnSize = btnSize.IsPointInside(app::glo::mouse_x, app::glo::mouse_y);
    bool onBtnMin  = btnMin.IsPointInside(app::glo::mouse_x, app::glo::mouse_y);
    bool onWndBar  = wndBar.IsPointInside(app::glo::mouse_x, app::glo::mouse_y) && !onBtnMin;

    AddRect(rd.renderDataUI, { rect,    WND_COL_BACK });
    AddRect(rd.renderDataUI, { wndBar,  onWndBar  ? WND_COL_BAR.Highlighted() : WND_COL_BAR });
    AddRect(rd.renderDataUI, { btnSize, onBtnSize ? WND_COL_ACTIVE : WND_COL_SIZE_BTN });
    AddRect(rd.renderDataUI, { btnMin,  onBtnMin  ? WND_COL_ACTIVE : WND_COL_MIN_BTN });
    AddText(rd.renderDataUI, title);

    AddRectBlur(rd.renderDataPost, rect);
}

///////////////////////////////////////////////////////////

}//ns