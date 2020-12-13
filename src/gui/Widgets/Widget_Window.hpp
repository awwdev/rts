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
    Recti rect;
    Recti limits { 32, 32, i32min, i32max };
    com::String<100> title { "Window" };

    void Render(gpu::RenderDataUI&);
};

///////////////////////////////////////////////////////////

void Widget_Window::Render(gpu::RenderDataUI& rd)
{
    AddRect
    (
        rd, 
        rect, 
        TEX_ID_OPAQUE, 
        { 0.f, 0.f, 0.f, 0.25 }
    );

    AddRect
    (
        rd, 
        { rect.x, rect.y, rect.w, BAR_H },
        TEX_ID_OPAQUE, 
        { 0.1, 0.1, 0.1, 1.f }
    );

    AddTextCentered
    (
        rd, 
        { rect.x, rect.y, rect.w, BAR_H },
        title.data,
        { 1, 1, 1, 1 }
    );
}

///////////////////////////////////////////////////////////

}//ns