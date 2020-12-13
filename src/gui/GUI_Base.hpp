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

struct Text
{
    com::String<100> str;
    Col4f color = Colors::AlmostWhite;
    i32 x = 0;
    i32 y = 0;

    void Center(com::Recti const& rect)
    {
        x = rect.x + (rect.w / 2 - (FONT_WIDTH * str.length) / 2);
        y = rect.y + (rect.h / 2 - (FONT_HEIGHT) / 2);
    }
};

///////////////////////////////////////////////////////////

struct Rect
{
    com::Recti rect  = {};
    Col4f color = Colors::AlmostWhite;
    u32 texId = TEX_ID_OPAQUE;
    //pretty much the same as UniformQuadData
};

///////////////////////////////////////////////////////////

static void AddRect(gpu::RenderDataUI& rd, Rect const& rect)
{
    rd.quadData.Append(rect.rect, rect.color, rect.texId);
}

///////////////////////////////////////////////////////////

static void AddText(gpu::RenderDataUI& rd, Text const& text)
{
    FOR_STRING(text.str, i)
    {
        com::Recti glyph { text.x + (i32)i * FONT_WIDTH + FONT_SPACING, text.y, FONT_WIDTH, FONT_HEIGHT };
        u32 texId = text.str[i] - 31; //32 is space, 0 is opaque
        AddRect(rd, { glyph, text.color, texId });
    }
}

///////////////////////////////////////////////////////////

static void AddRectBlur(gpu::RenderDataPost& rd, com::Recti const& rect)
{
    Vec2f uv0 { (f32)rect.x / app::glo::windowWidth, (f32)rect.y / app::glo::windowHeight };
    Vec2f uv1 { (f32)rect.x / app::glo::windowWidth, (f32)(rect.y + rect.h) / app::glo::windowHeight };
    Vec2f uv2 { (f32)(rect.x + rect.w) / app::glo::windowWidth, (f32)(rect.y + rect.h) / app::glo::windowHeight };
    Vec2f uv3 { (f32)(rect.x + rect.w) / app::glo::windowWidth, (f32)rect.y / app::glo::windowHeight };

    Vec2f p0 { uv0.x * 2 - 1, uv0.y * 2 - 1 };
    Vec2f p1 { uv1.x * 2 - 1, uv1.y * 2 - 1 };
    Vec2f p2 { uv2.x * 2 - 1, uv2.y * 2 - 1 };
    Vec2f p3 { uv3.x * 2 - 1, uv3.y * 2 - 1 };

    rd.vertices.Append(p0, uv0, 1);
    rd.vertices.Append(p1, uv1, 1);
    rd.vertices.Append(p2, uv2, 1);
    rd.vertices.Append(p0, uv0, 1);
    rd.vertices.Append(p2, uv2, 1);
    rd.vertices.Append(p3, uv3, 1);
}

///////////////////////////////////////////////////////////

}//ns