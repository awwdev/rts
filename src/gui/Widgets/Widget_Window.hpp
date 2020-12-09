#pragma once

#include "gui/GUI_Base.hpp"
#include "com/Rect.hpp"
#include "gpu/RenderDataUI.hpp"

///////////////////////////////////////////////////////////

namespace rts::gui {

///////////////////////////////////////////////////////////

struct Widget_Window 
{
    static constexpr i32 BAR_H = 20;
    Recti rect;
    Recti limits { 32, 32, i32min, i32max };

    void Render(gpu::RenderDataUI&);
};

///////////////////////////////////////////////////////////

void Widget_Window::Render(gpu::RenderDataUI& rd)
{
    AddRect(rd, rect);
}

//https://github.com/awwdev/rpg/blob/master/src/gui/Widgets/Widget_Window.hpp
//https://github.com/awwdev/rpg/blob/master/src/gui/GUI_Base.hpp
//https://github.com/awwdev/rpg/tree/master/src/gui/Editor

///////////////////////////////////////////////////////////

}//ns