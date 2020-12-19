#pragma once

#include "gui/GUI_Base.hpp"
#include "com/Rect.hpp"
#include "com/Print.hpp"
#include "com/Color.hpp"
#include "gpu/RenderData.hpp"
#include "com/String.hpp"

///////////////////////////////////////////////////////////

namespace rts::gui {

///////////////////////////////////////////////////////////

struct Widget_Window 
{
    static constexpr i32 BAR_H = 24;
    static constexpr i32 ROW_H = 24;
    static constexpr i32 ROW_PADDING = 4;
    static constexpr Col4n WND_COL_BACK     { 0.f, 0.f, 0.f, 0.25 };
    static constexpr Col4n WND_COL_BAR      { 0.1, 0.1, 0.1, 1.f };
    static constexpr Col4n WND_COL_SIZE_BTN { 0.1, 0.1, 0.1, 1.f };
    static constexpr Col4n WND_COL_MIN_BTN  { 0.2, 0.2, 0.2, 1.f };
    static constexpr Col4n WND_COL_ACTIVE   { 0.8, 0.2, 0.2, 1.f };
    static constexpr i32 RESIZE_BTN = 8;

    com::Recti rect;
    com::Recti limits { BAR_H, BAR_H, i32min, i32max };
    Text title;
    bool isDragged;
    bool isMini;
    i32 rowCount;
    com::Vec2i dragOffset;

    void Update(gpu::RenderData&);
    void UpdateText(gpu::RenderDataUI&, Text&);
};

///////////////////////////////////////////////////////////

void Widget_Window::Update(gpu::RenderData& rd)
{
    rowCount = 0;

    com::Recti wndBar  { rect.x, rect.y, rect.w, BAR_H };
    com::Recti wndBack { rect.x, rect.y + BAR_H, rect.w, rect.h - BAR_H };
    com::Recti btnSize { rect.x + rect.w - RESIZE_BTN, rect.y + rect.h - RESIZE_BTN, RESIZE_BTN, RESIZE_BTN };
    com::Recti btnMin  { rect.x + rect.w - BAR_H, rect.y, BAR_H, BAR_H };
    title.Center(wndBar);

    using namespace app;
    bool onBtnSize = btnSize.IsPointInside(Inputs::mouse.pos);
    bool onBtnMin  = btnMin.IsPointInside (Inputs::mouse.pos);
    bool onWndBar  = wndBar.IsPointInside (Inputs::mouse.pos) && !onBtnMin;

    //? drag
    if (onWndBar && Inputs::mouse.IsPressed(InputMouse::Left))
    {
        isDragged = true;
        dragOffset = Inputs::mouse.pos - com::Vec2i { rect.x, rect.y };
    }
    if (isDragged)
    {
        rect.x = app::Inputs::mouse.pos.x - dragOffset.x;
        rect.y = app::Inputs::mouse.pos.y - dragOffset.y;
    }
    if (isDragged && Inputs::mouse.IsReleased(InputMouse::Left))
    {
        isDragged = false;
    }

    //? minmax
    if (onBtnMin && Inputs::mouse.IsPressed(InputMouse::Left))
        isMini = !isMini; 

    AddRect(rd.renderDataUI, { wndBar, onWndBar ? WND_COL_BAR.Highlighted() : WND_COL_BAR });
    AddText(rd.renderDataUI, title);
    AddRect(rd.renderDataUI, { btnMin, onBtnMin ? WND_COL_ACTIVE : WND_COL_MIN_BTN });

    if (!isMini)
    {
        AddRect(rd.renderDataUI, { wndBack, WND_COL_BACK });
        AddRect(rd.renderDataUI, { btnSize, onBtnSize ? WND_COL_ACTIVE : WND_COL_SIZE_BTN });
        AddRectBlur(rd.renderDataPost, rect);
    }
}

///////////////////////////////////////////////////////////

void Widget_Window::UpdateText(gpu::RenderDataUI& rd, Text& text)
{
    if (isMini) 
        return;

    text.x = rect.x + ROW_PADDING;
    text.y = rect.y + ROW_PADDING + BAR_H + rowCount * ROW_H;
    rowCount++;
    AddText(rd, text);
}

///////////////////////////////////////////////////////////

}//ns