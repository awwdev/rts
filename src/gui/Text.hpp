#pragma once

#include "com/Color.hpp"
#include "com/String.hpp"
#include "com/Rect.hpp"

///////////////////////////////////////////////////////////

namespace rts::gui {

///////////////////////////////////////////////////////////

namespace Colors
{
    constexpr Col4n AlmostWhite = { 0.95, 0.95, 0.95, 1 };
    constexpr Col4n Orange      = { 255/255.f, 160/255.f, 80/255.f, 1.0 };
}

///////////////////////////////////////////////////////////

struct Font
{
    i32 heigth;
    i32 width;
    i32 spacing;
};

///////////////////////////////////////////////////////////

constexpr Font EDITOR_BOLD_FONT
{
    .heigth  = 14,
    .width   = 14,
    .spacing = -4,
};

constexpr Font EDITOR_DEFAULT_FONT
{
    .heigth  = 14,
    .width   = 14,
    .spacing = -4,
};

///////////////////////////////////////////////////////////

struct Text
{
    com::String<100> str;
    Col4n color = Colors::AlmostWhite;
    Font font = EDITOR_BOLD_FONT;
    i32 x = 0;
    i32 y = 0;

    void Center(com::Recti const& rect)
    {
        x = rect.x + rect.w / 2 - ((font.width + font.spacing) * str.length) / 2;
        y = rect.y + rect.h / 2 - (font.heigth) / 2;
    }
};

///////////////////////////////////////////////////////////

}//ns