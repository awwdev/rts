#pragma once

#include "gpu/RenderDataUI.hpp"
#include "com/Rect.hpp"
#include "com/Vec.hpp"
#include "com/String.hpp"

///////////////////////////////////////////////////////////

namespace rts::gui {

///////////////////////////////////////////////////////////

//TODO too specialized, should be more according to editor font only
constexpr u32 TEX_ID_OPAQUE = 0;
constexpr i32 FONT_HEIGHT = 9;
constexpr i32 FONT_WIDTH = 7;
constexpr i32 FONT_SPACING = 0;

///////////////////////////////////////////////////////////

namespace Colors
{
    constexpr Col4f AlmostWhite = { 0.95, 0.95, 0.95, 1 };
    constexpr Col4f Orange      = { 255/255.f, 160/255.f, 80/255.f, 1.0 };
}

///////////////////////////////////////////////////////////

struct ColorText
{
    com::String<100> str;
    Col4f color = Colors::AlmostWhite;
    i32 x = 0;
    i32 y = 0;

    void Center(Recti const& rect)
    {
        x = rect.x + (rect.w / 2 - (FONT_WIDTH * str.length) / 2);
        y = rect.y + (rect.h / 2 - (FONT_HEIGHT) / 2);
    }
};

///////////////////////////////////////////////////////////

struct ColorRect
{
    Recti rect  = {};
    Col4f color = Colors::AlmostWhite;
    u32 texId   = TEX_ID_OPAQUE;
    //pretty much the same as UniformQuadData
};

///////////////////////////////////////////////////////////

static void AddRect(gpu::RenderDataUI& rd, ColorRect const& rect)
{
    rd.quadData.Append(rect.rect, rect.color, rect.texId);
}

///////////////////////////////////////////////////////////

static void AddText(gpu::RenderDataUI& rd, ColorText const& text)
{
    FOR_STRING(text.str, i)
    {
        Recti glyph { text.x + (i32)i * FONT_WIDTH + FONT_SPACING, text.y, FONT_WIDTH, FONT_HEIGHT };
        u32 texId = text.str[i] - 31; //32 is space, 0 is opaque
        AddRect(rd, { glyph, text.color, texId });
    }
}

///////////////////////////////////////////////////////////

}//ns