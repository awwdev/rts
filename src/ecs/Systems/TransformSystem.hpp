#pragma once

#include "ecs/ComponentArrays.hpp"
#include "com/Utils.hpp"
#include "cmd/Lockstep.hpp"

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

        auto moveFn = [](idx_t stepIdx, i32 coord, i32 delta, i32& pos, i32 target, i32 spd)
        {
            if (coord != 0 && stepIdx % Abs(coord) == 0 && delta != 0)
            {
                auto sign1 = Sign(delta);
                pos += sign1 * (spd / cmd::STEPS_PER_SEC); //!
                auto sign2 = Sign(target - pos);
                if (sign1 != sign2)
                    pos = target;
            }
        };
        moveFn(stepIdx, trans.xspd, trans.delta.x, trans.pos.x, trans.posTarget.x, trans.spd);
        moveFn(stepIdx, trans.yspd, trans.delta.y, trans.pos.y, trans.posTarget.y, trans.spd);

        //don't get stuck
        if (trans.delta == 0)
        {
            FOR_ARRAY(dense, j)
            {
                if (i == j) continue;
                auto& other = dense[j];
                auto delta = other.transform.pos - trans.pos;
                auto dist = Magnitude(delta);
                if (dist < 8)
                {
                    trans.posTarget = trans.posTarget - delta;
                    trans.CalculateDelta();
                }
            }
        }
        
    }

}

///////////////////////////////////////////////////////////

}//ns