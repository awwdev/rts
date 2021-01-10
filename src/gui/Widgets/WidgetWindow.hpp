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
    //sizes
    static constexpr i32 BAR_H = 24;
    static constexpr i32 ROW_H = 24;
    static constexpr i32 ROW_PADDING = 4;
    static constexpr i32 RESIZE_BTN = 8;

    //colors
    static constexpr com::Col4n COL_BACK       { 0.f, 0.f, 0.f, 0.2 };
    static constexpr com::Col4n COL_BAR        { 0.1, 0.1, 0.1, 1.f };
    static constexpr com::Col4n COL_BTN_SIZE   { 0.1, 0.1, 0.1, 1.f };
    static constexpr com::Col4n COL_BTN_MIN    { 0.2, 0.2, 0.2, 1.f };
    static constexpr com::Col4n COL_BTN_ACTIVE { 0.8, 0.2, 0.2, 1.f };

    //elements
    com::Recti rect;
    Text title;
    i32 rowCount;
    com::Vec2i dragOffset;
    com::Vec2i sizeOffset;
    bool isDragged;
    bool isMini;
    bool isSize;

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
    USING_NAMESPACES

    rowCount = 0;
  
    Recti bar     { rect.pos.x, rect.pos.y, rect.size.x, BAR_H };
    Recti btnSize { rect.pos.x + rect.size.x - RESIZE_BTN, rect.pos.y + rect.size.y - RESIZE_BTN, RESIZE_BTN, RESIZE_BTN };
    Recti btnMin  { rect.pos.x + rect.size.x - BAR_H, rect.pos.y, BAR_H, BAR_H };
    title.Center(bar);

    bool onBtnMin  = btnMin.IsPointInside  (Inputs::mouse.pos);
    bool onWndBar  = bar.IsPointInside  (Inputs::mouse.pos) && !onBtnMin;
    bool onBtnSize = btnSize.IsPointInside (Inputs::mouse.pos);
    bool onWnd     = rect.IsPointInside(Inputs::mouse.pos);
    bool onDrag    = onWnd && !onBtnMin && !onBtnSize && (!isMini || (onWndBar && !onBtnMin));

    UpdateMinMax(onBtnMin);
    UpdateDrag(onDrag);
    UpdateSize(onBtnSize);

    if (onWnd || isDragged || isSize)
        app::Inputs::activeLayer = app::Inputs::ActiveLayer::UI;

    if (!isMini)
    {
        rd.ui.AddQuad({ rect, COL_BACK });
        rd.ui.AddQuad({ btnSize, onBtnSize ? COL_BTN_ACTIVE : COL_BTN_SIZE });
        rd.post.AddBlurQuad(rect);
    }

    rd.ui.AddQuad({ bar, onWndBar ? COL_BAR.Highlighted() : COL_BAR });
    rd.ui.AddText(title);
    rd.ui.AddQuad({ btnMin, onBtnMin ? COL_BTN_ACTIVE : COL_BTN_MIN });
}

///////////////////////////////////////////////////////////

void WidgetWindow::UpdateDrag(bool onWndDrag)
{
    USING_NAMESPACES

    if (onWndDrag && Inputs::mouse.IsPressed(InputMouse::Left))
    {
        isDragged = true;
        dragOffset = Inputs::mouse.pos;
    }
    if (isDragged)
    {
        auto delta = Inputs::mouse.pos - dragOffset;
        rect.pos.x += delta.x;
        rect.pos.y += delta.y;
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
    USING_NAMESPACES

    if (onBtnSize && Inputs::mouse.IsPressed(InputMouse::Left))
    {
        isSize = true;
        sizeOffset = Inputs::mouse.pos;
    }
    if (isSize)
    {
        auto delta = Inputs::mouse.pos - sizeOffset;
        rect.size.x += delta.x;
        rect.size.y += delta.y;
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
    USING_NAMESPACES
    
    if (onBtnMin && Inputs::mouse.IsPressed(InputMouse::Left))
        isMini = !isMini; 
}

///////////////////////////////////////////////////////////

void WidgetWindow::UpdateText(gpu::RenderDataUI& rd, Text& text)
{
    if (isMini) 
        return;

    text.x = rect.pos.x + ROW_PADDING;
    text.y = rect.pos.y + ROW_PADDING + BAR_H + rowCount * ROW_H;
    rowCount++;
    rd.AddText(text);
}

///////////////////////////////////////////////////////////

}//ns