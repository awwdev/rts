#pragma once

#include "gpu/RenderDataUI.hpp"
#include "com/Rect.hpp"
#include "com/Vec.hpp"
#include "com/String.hpp"

///////////////////////////////////////////////////////////

namespace rts::gui {

///////////////////////////////////////////////////////////

constexpr u32 TEX_ID_OPAQUE = 95;

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
Recti const& rect, 
chars_t text,
Col4f col = { 1, 1, 1, 1 })
{
    auto len = com::StrLen(text);
    for(i32 i = 0; i < len; ++i)
    {
        Recti glyph { rect.x + i * 16, rect.y, 16, 16 };
        u32 texId = text[i] - 33;
        AddRect(rd, glyph, texId, col);
    }
}

///////////////////////////////////////////////////////////

}//ns