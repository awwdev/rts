#pragma once

#include "gpu/RenderDataUI.hpp"
#include "com/Rect.hpp"
#include "com/Vec.hpp"
#include "com/String.hpp"

///////////////////////////////////////////////////////////

namespace rts::gui {

///////////////////////////////////////////////////////////

constexpr u32 TEX_ID_OPAQUE = 0;
constexpr i32 FONT_HEIGHT = 9;
constexpr i32 FONT_WIDTH = 7;
constexpr i32 FONT_SPACING = 0;

///////////////////////////////////////////////////////////

inline void AddRect(
gpu::RenderDataUI& rd, 
Recti const& rect, 
u32 texId = TEX_ID_OPAQUE, 
Col4f col = { 1, 1, 1, 1 })
{
    rd.quadData.Append(rect, col, texId);
}

///////////////////////////////////////////////////////////

inline void AddText(
gpu::RenderDataUI& rd, 
i32 xpos, i32 ypos, 
chars_t text,
Col4f col = { 1, 1, 1, 1 })
{
    auto len = com::StrLen(text);
    for(i32 i = 0; i < len; ++i)
    {
        Recti glyph { xpos + i * FONT_WIDTH + FONT_SPACING, ypos, FONT_WIDTH, FONT_HEIGHT };
        u32 texId = text[i] - 31; //32 is space, 0 is opaque
        AddRect(rd, glyph, texId, col);
    }
}

///////////////////////////////////////////////////////////

inline void AddTextCentered(
gpu::RenderDataUI& rd, 
Recti rect, 
chars_t text,
Col4f col = { 1, 1, 1, 1 })
{
    auto len = com::StrLen(text);
    i32 xpos = rect.x + (rect.w / 2 - (FONT_WIDTH * len) / 2);
    i32 ypos = rect.y + (rect.h / 2 - (FONT_HEIGHT) / 2);
    AddText(rd, xpos, ypos, text, col);
}

///////////////////////////////////////////////////////////

}//ns