#pragma once

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
    static constexpr i32 RESIZE_BTN = 8;

    static constexpr Col4n WND_COL_BACK     { 0.f, 0.f, 0.f, 0.25 };
    static constexpr Col4n WND_COL_BAR      { 0.1, 0.1, 0.1, 1.f };
    static constexpr Col4n WND_COL_SIZE_BTN { 0.1, 0.1, 0.1, 1.f };
    static constexpr Col4n WND_COL_MIN_BTN  { 0.2, 0.2, 0.2, 1.f };
    static constexpr Col4n WND_COL_ACTIVE   { 0.8, 0.2, 0.2, 1.f };

    com::Recti rect;
    Text title;
    bool isDragged;
    bool isMini;
    bool isSize;
    i32 rowCount;
    com::Vec2i dragOffset;
    com::Vec2i sizeOffset;

    void Update(gpu::RenderData&);
    void UpdateText(gpu::RenderDataUI&, Text&);

private:
    void UpdateDrag(bool);
    void UpdateSize(bool);
    void UpdateMinMax(bool);
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
    bool onBtnMin  = btnMin.IsPointInside (Inputs::mouse.pos);
    bool onWndBar  = wndBar.IsPointInside (Inputs::mouse.pos) && !onBtnMin;
    bool onBtnSize = btnSize.IsPointInside(Inputs::mouse.pos);

    UpdateMinMax(onBtnMin);
    UpdateDrag(onWndBar);
    UpdateSize(onBtnSize);

    auto& rdui   = rd.renderDataUI;
    auto& rdpost = rd.renderDataPost;
    rdui.AddQuad({ wndBar, onWndBar ? WND_COL_BAR.Highlighted() : WND_COL_BAR });
    rdui.AddText(title);
    rdui.AddQuad({ btnMin, onBtnMin ? WND_COL_ACTIVE : WND_COL_MIN_BTN });

    if (!isMini)
    {
        rdui.AddQuad({ wndBack, WND_COL_BACK });
        rdui.AddQuad({ btnSize, onBtnSize ? WND_COL_ACTIVE : WND_COL_SIZE_BTN });
        rdpost.AddBlurQuad(rect);
    }
}

///////////////////////////////////////////////////////////

void Widget_Window::UpdateDrag(bool onWndBar)
{
    using namespace app;
    if (onWndBar && Inputs::mouse.IsPressed(InputMouse::Left))
    {
        isDragged = true;
        dragOffset = Inputs::mouse.pos;
    }
    if (isDragged)
    {
        auto delta = Inputs::mouse.pos - dragOffset;
        rect.x += delta.x;
        rect.y += delta.y;
        dragOffset = Inputs::mouse.pos;
    }
    if (isDragged && Inputs::mouse.IsReleased(InputMouse::Left))
    {
        isDragged = false;
    }
}

///////////////////////////////////////////////////////////

void Widget_Window::UpdateSize(bool onBtnSize)
{
    using namespace app;
    if (onBtnSize && Inputs::mouse.IsPressed(InputMouse::Left))
    {
        isSize = true;
        sizeOffset = Inputs::mouse.pos;
    }
    if (isSize)
    {
        auto delta = Inputs::mouse.pos - sizeOffset;
        rect.w += delta.x;
        rect.h += delta.y;
        sizeOffset = Inputs::mouse.pos;
    }
    if (isSize && Inputs::mouse.IsReleased(InputMouse::Left))
    {
        isSize = false;
    }   
}

///////////////////////////////////////////////////////////

void Widget_Window::UpdateMinMax(bool onBtnMin)
{
    using namespace app;
    if (onBtnMin && Inputs::mouse.IsPressed(InputMouse::Left))
        isMini = !isMini; 
}

///////////////////////////////////////////////////////////

void Widget_Window::UpdateText(gpu::RenderDataUI& rd, Text& text)
{
    if (isMini) 
        return;

    text.x = rect.x + ROW_PADDING;
    text.y = rect.y + ROW_PADDING + BAR_H + rowCount * ROW_H;
    rowCount++;
    rd.AddText(text);
}

///////////////////////////////////////////////////////////

}//ns