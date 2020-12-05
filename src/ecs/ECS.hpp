#pragma once

#include "ecs/Systems/RenderSystem.hpp"
#include "ecs/Systems/TransformSystem.hpp"

#include "ecs/ComponentArrays.hpp"
#include "gpu/RenderData.hpp"
#include "app/Lockstep.hpp"
#include "com/Bitset.hpp"

///////////////////////////////////////////////////////////

namespace rts::ecs {

///////////////////////////////////////////////////////////

struct ECS 
{
    com::Bitset<ENTITY_COUNT_MAX> entities;
    ComponentArrays arrays;

    auto AddEntity();
    void RemoveEntity();
    void Step();
    void Render(gpu::RenderData&, app::Lockstep&);
};

///////////////////////////////////////////////////////////

auto ECS::AddEntity()
{
    auto freeBit = entities.FindFirstFreeBit();
    com::Assert(freeBit.hasData, "no free entity");
    entities.Set(freeBit.Data());
    return freeBit.Data();
}

///////////////////////////////////////////////////////////

void ECS::RemoveEntity()
{

}

///////////////////////////////////////////////////////////

void ECS::Step()
{
    TransformSystem(arrays);
}

///////////////////////////////////////////////////////////

void ECS::Render(gpu::RenderData& renderData, app::Lockstep& lockstep)
{
    RenderSystem(arrays, renderData, lockstep);
}

///////////////////////////////////////////////////////////

}//ns