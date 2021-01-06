#pragma once

#include "com/Array.hpp"
#include "com/Rect.hpp"
#include "gui/Text.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu {

///////////////////////////////////////////////////////////

struct RenderDataUI
{
    struct PushMeta
    {
        i32 windowWidth;
        i32 windowHeight;
    };

    struct UniformQuadData
    {
        com::Recti rect;
        com::Col4n col;
        u32 texId;
    };

    static constexpr auto QUAD_COUNT_MAX = 1000;
    com::Array<UniformQuadData, QUAD_COUNT_MAX> quadData;

    void Clear();
    void AddText(gui::Text const&);
    void AddQuad(UniformQuadData const&);
};

///////////////////////////////////////////////////////////

void RenderDataUI::Clear()
{
    quadData.count = 0;
}

///////////////////////////////////////////////////////////

void RenderDataUI::AddText(gui::Text const& text)
{
    constexpr u32 ASCII_OFFSET = 31;
    FOR_STRING(text.str, i)
    {
        com::Recti glyph
        { 
            .p1 { text.x + (i32)i * (text.font.width + text.font.spacing), text.y },
            .p2 { text.font.width, text.font.heigth }
        };
        u32 texId = text.str[i] - ASCII_OFFSET;
        quadData.Append(glyph, text.color, texId);
    }
}
///////////////////////////////////////////////////////////

void RenderDataUI::AddQuad(UniformQuadData const& quad)
{
    quadData.Append(quad);
}

}//ns