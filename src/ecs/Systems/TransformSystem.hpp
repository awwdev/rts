#pragma once

#include "ecs/ComponentArrays.hpp"
#include "com/Utils.hpp"

///////////////////////////////////////////////////////////

namespace rts::ecs {

///////////////////////////////////////////////////////////

static void TransformSystem(ComponentArrays& arrays, idx_t stepIdx)
{
    using namespace com;

    auto& mainComponents = arrays.mainComponents;
    auto& dense = mainComponents.dense;

    FOR_ARRAY(dense, i)
    {
        auto& trans = dense[i].transform;
        trans.delta = trans.posTarget - trans.pos;
        trans.posPrev = trans.pos;
       
        while (trans.delta.x == 0 && trans.delta.y == 0)
        {
            //test
            trans.posTarget.x = rand() % 600;
            trans.posTarget.y = rand() % 400;
            //xspd and yspd
            trans.delta = trans.posTarget - trans.pos;
            auto m = Max(Abs(trans.delta.x), Abs(trans.delta.y));
            if (trans.delta.x != 0)
                trans.xspd = m / trans.delta.x;
            if (trans.delta.y != 0)
                trans.yspd = m / trans.delta.y;
        }

        auto fn = [](idx_t stepIdx, i32 coord, i32 delta, i32& pos, i32 target, i32 spd)
        {
            if (coord != 0 && stepIdx % Abs(coord) == 0 && delta != 0)
            {
                auto sign1 = Sign(delta);
                pos += sign1 * spd;
                auto sign2 = Sign(target - pos);
                if (sign1 != sign2)
                    pos = target;
            }
        };

        fn(stepIdx, trans.xspd, trans.delta.x, trans.pos.x, trans.posTarget.x, trans.spd);
        fn(stepIdx, trans.yspd, trans.delta.y, trans.pos.y, trans.posTarget.y, trans.spd);
    }

}

///////////////////////////////////////////////////////////

}//ns



//if (trans.xspd != 0 && stepIdx % Abs(trans.xspd) == 0 && trans.delta.x != 0)
//{
//    auto sign1 = Sign(trans.delta.x);
//    trans.pos.x += sign1 * trans.spd;
//    auto sign2 = Sign(trans.posTarget.x - trans.pos.x);
//    if (sign1 != sign2)
//        trans.pos.x = trans.posTarget.x;
//}
//if (trans.yspd != 0 && stepIdx % Abs(trans.yspd) == 0 && trans.delta.y != 0)
//{
//    auto sign1 = Sign(trans.delta.y);
//    trans.pos.y += sign1 * trans.spd;
//    auto sign2 = Sign(trans.posTarget.y - trans.pos.y);
//    if (sign1 != sign2)
//        trans.pos.y = trans.posTarget.y;
//}