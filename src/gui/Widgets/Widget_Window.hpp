#pragma once

#include "gui/GUI_Base.hpp"
#include "com/Rect.hpp"
#include "gpu/RenderDataUI.hpp"

///////////////////////////////////////////////////////////

namespace rts::gui {

///////////////////////////////////////////////////////////

struct Widget_Window 
{
    static constexpr f32 BAR_H = 20;

    Rectf rect;
    Rectf limits { 32, 32, f32max, f32max };

    void Update(gpu::RenderDataUI&);
};

///////////////////////////////////////////////////////////

void Widget_Window::Update(gpu::RenderDataUI& rd)
{
    AddRect(rd,  rect);
}

//https://github.com/awwdev/rpg/blob/master/src/gui/Widgets/Widget_Window.hpp
//https://github.com/awwdev/rpg/blob/master/src/gui/GUI_Base.hpp
//https://github.com/awwdev/rpg/tree/master/src/gui/Editor

///////////////////////////////////////////////////////////

}//ns