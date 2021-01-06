#pragma once

#include "com/Rect.hpp"
#include "com/Print.hpp"
#include "com/Color.hpp"
#include "gpu/RenderData.hpp"
#include "com/String.hpp"
#include "app/Input/Inputs.hpp"

///////////////////////////////////////////////////////////

namespace rts::gui {

///////////////////////////////////////////////////////////

struct WidgetWindow 
{
    static constexpr i32 BAR_H = 24;
    static constexpr i32 ROW_H = 24;
    static constexpr i32 ROW_PADDING = 4;
    static constexpr i32 RESIZE_BTN = 8;

    static constexpr com::Col4n WND_COL_BACK     { 0.f, 0.f, 0.f, 0.25 };
    static constexpr com::Col4n WND_COL_BAR      { 0.1, 0.1, 0.1, 1.f };
    static constexpr com::Col4n WND_COL_SIZE_BTN { 0.1, 0.1, 0.1, 1.f };
    static constexpr com::Col4n WND_COL_MIN_BTN  { 0.2, 0.2, 0.2, 1.f };
    static constexpr com::Col4n WND_COL_ACTIVE   { 0.8, 0.2, 0.2, 1.f };

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

void WidgetWindow::Update(gpu::RenderData& rd)
{
    using namespace com;
    rowCount = 0;

    Recti wndBar  { rect.p1.x, rect.p1.y, rect.p2.x, BAR_H };
    Recti wndBack { rect.p1.x, rect.p1.y + BAR_H, rect.p2.x, rect.p2.y - BAR_H };
    Recti btnSize { rect.p1.x + rect.p2.x - RESIZE_BTN, rect.p1.y + rect.p2.y - RESIZE_BTN, RESIZE_BTN, RESIZE_BTN };
    Recti btnMin  { rect.p1.x + rect.p2.x - BAR_H, rect.p1.y, BAR_H, BAR_H };
    title.Center(wndBar);

    //TODO: MAKE ALL RECT USAGE WITH ABS POINTS !
    //TODO: SHADER REWRITE

    using namespace app;
    bool onBtnMin  = btnMin.IsPointInside  (Inputs::mouse.pos);
    bool onWndBar  = wndBar.IsPointInside  (Inputs::mouse.pos) && !onBtnMin;
    bool onBtnSize = btnSize.IsPointInside (Inputs::mouse.pos);
    bool onWnd     = (wndBack.IsPointInside(Inputs::mouse.pos) || wndBar.IsPointInside(Inputs::mouse.pos));
    bool onDrag    = onWnd && !onBtnMin && !onBtnSize && (!isMini || (onWndBar && !onBtnMin));

    if (onWnd || isDragged || isSize)
        app::Inputs::activeLayer = app::Inputs::ActiveLayer::UI;

    UpdateMinMax(onBtnMin);
    UpdateDrag(onDrag);
    UpdateSize(onBtnSize);

    auto& rdui   = rd.ui;
    auto& rdpost = rd.post;
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

void WidgetWindow::UpdateDrag(bool onWndDrag)
{
    using namespace app;
    if (onWndDrag && Inputs::mouse.IsPressed(InputMouse::Left))
    {
        isDragged = true;
        dragOffset = Inputs::mouse.pos;
    }
    if (isDragged)
    {
        auto delta = Inputs::mouse.pos - dragOffset;
        rect.p1.x += delta.x;
        rect.p1.y += delta.y;
        dragOffset = Inputs::mouse.pos;
    }
    if (isDragged && Inputs::mouse.IsReleased(InputMouse::Left))
    {
        isDragged = false;
    }
}

///////////////////////////////////////////////////////////

void WidgetWindow::UpdateSize(bool onBtnSize)
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
        rect.p2.x += delta.x;
        rect.p2.y += delta.y;
        sizeOffset = Inputs::mouse.pos;
    }
    if (isSize && Inputs::mouse.IsReleased(InputMouse::Left))
    {
        isSize = false;
    }   
}

///////////////////////////////////////////////////////////

void WidgetWindow::UpdateMinMax(bool onBtnMin)
{
    using namespace app;
    if (onBtnMin && Inputs::mouse.IsPressed(InputMouse::Left))
        isMini = !isMini; 
}

///////////////////////////////////////////////////////////

void WidgetWindow::UpdateText(gpu::RenderDataUI& rd, Text& text)
{
    if (isMini) 
        return;

    text.x = rect.p1.x + ROW_PADDING;
    text.y = rect.p1.y + ROW_PADDING + BAR_H + rowCount * ROW_H;
    rowCount++;
    rd.AddText(text);
}

///////////////////////////////////////////////////////////

}//ns