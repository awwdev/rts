#pragma once

#include "gpu/RenderDataUI.hpp"
#include "com/Rect.hpp"
#include "com/Vec.hpp"

///////////////////////////////////////////////////////////

namespace rts::gui {

///////////////////////////////////////////////////////////

constexpr u32 TEX_ID_OPAQUE = 0;

///////////////////////////////////////////////////////////

inline void AddRect(gpu::RenderDataUI& rd, Rectf& rect)
{
    auto& p = rect.pos;
    auto& s = rect.size;
    auto  c = Col4f { 1, 1, 1, 0.5 };
    auto  t = TEX_ID_OPAQUE;

    rd.vertices.Append(p.x,         p.y,        c, t);
    rd.vertices.Append(p.x + s.x,   p.y,        c, t);
    rd.vertices.Append(p.x + s.x,   p.y + s.y,  c, t);
    rd.vertices.Append(p.x,         p.y + s.y,  c, t);
}

///////////////////////////////////////////////////////////

inline void AddText(gpu::RenderDataUI& rd, Rectf& rect)
{
    //TODO
}

///////////////////////////////////////////////////////////

}//ns