#pragma once

#include "gui/GUI_Base.hpp"
#include "com/Rect.hpp"
#include "gpu/RenderDataUI.hpp"
#include "com/String.hpp"

///////////////////////////////////////////////////////////

namespace rts::gui {

///////////////////////////////////////////////////////////

struct Widget_Window 
{
    static constexpr i32 BAR_H = 24;
    static constexpr Col4f WN_COL_BACK { 0.f, 0.f, 0.f, 0.25 };
    static constexpr Col4f WND_COL_BAR { 0.1, 0.1, 0.1, 1.f };
    static constexpr Col4f WND_COL_SIZE_BTN { 0.1, 0.1, 0.1, 1.f };
    static constexpr Col4f WND_COL_MIN_BTN { 0.2, 0.2, 0.2, 1.f };
    static constexpr i32 RESIZE_BTN = 8;

    Recti rect;
    Recti limits { BAR_H, BAR_H, i32min, i32max };
    ColorText title
    {
        .str   = "Window",
        .color = Colors::Orange
    };

    void Render(gpu::RenderDataUI&);
};

///////////////////////////////////////////////////////////

void Widget_Window::Render(gpu::RenderDataUI& rd)
{
    Recti wndBar  { rect.x, rect.y, rect.w, BAR_H };
    Recti sizeBtn { rect.x + rect.w - RESIZE_BTN, rect.y + rect.h - RESIZE_BTN, RESIZE_BTN, RESIZE_BTN };
    Recti minBtn  { rect.x + rect.w - BAR_H, rect.y, BAR_H, BAR_H };
    title.Center(wndBar);

    AddRect(rd, { rect, WN_COL_BACK });
    AddRect(rd, { wndBar, WND_COL_BAR });
    AddRect(rd, { sizeBtn, WND_COL_SIZE_BTN });
    AddRect(rd, { minBtn, WND_COL_MIN_BTN });
    AddText(rd, title);
}

///////////////////////////////////////////////////////////

}//ns