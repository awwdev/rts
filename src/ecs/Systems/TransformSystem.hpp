#pragma once

#include "ecs/ComponentArrays.hpp"
#include "com/Utils.hpp"

///////////////////////////////////////////////////////////

namespace rts::ecs {

///////////////////////////////////////////////////////////

static void TransformSystem(ComponentArrays& arrays, idx_t stepIdx)
{
    auto& mainComponents = arrays.mainComponents;
    auto& dense = mainComponents.dense;

    FOR_ARRAY(dense, i)
    {
        auto& trans = dense[i].transform;
        trans.delta = trans.posTarget - trans.pos;
       
        while (trans.delta.x == 0 && trans.delta.y == 0)
        {
            //test
            trans.posTarget.x = rand() % 600;
            trans.posTarget.y = rand() % 400;
            //xspd and yspd
            trans.delta = trans.posTarget - trans.pos;
            auto m = com::Max(com::Abs(trans.delta.x), com::Abs(trans.delta.y));
            if (trans.delta.x != 0)
                trans.xspd = m / trans.delta.x;
            if (trans.delta.y != 0)
                trans.yspd = m / trans.delta.y;
        }

        if (stepIdx % com::Abs(trans.xspd) == 0 && trans.delta.x != 0)
        {
            auto sign = com::Sign(trans.delta.x);
            auto diff = com::Sign(trans.posTarget.x - trans.pos.x);
            trans.pos.x += sign * trans.spd;
            auto diff2 = com::Sign(trans.posTarget.x - trans.pos.x);
            if (diff != diff2)
                trans.pos.x = trans.posTarget.x;
        }
        if (stepIdx % com::Abs(trans.yspd) == 0 && trans.delta.y != 0)
        {
            auto sign = com::Sign(trans.delta.y);
            auto diff = com::Sign(trans.posTarget.y - trans.pos.y);
            trans.pos.y += sign * trans.spd;
            auto diff2 = com::Sign(trans.posTarget.y - trans.pos.y);
            if (diff != diff2)
                trans.pos.y = trans.posTarget.y;
        }

    }

}

///////////////////////////////////////////////////////////

}//ns