#pragma once

#include "ecs/Systems/RenderSystem.hpp"
#include "ecs/ComponentArrays.hpp"
#include "gpu/RenderData.hpp"
#include "com/Bitset.hpp"

///////////////////////////////////////////////////////////

namespace mini::ecs {

///////////////////////////////////////////////////////////

struct ECS 
{
    com::Bitset<ENTITY_COUNT_MAX> entities;
    ComponentArrays arrays;

    auto AddEntity();
    void RemoveEntity();
    void Update(gpu::RenderData&);
};

///////////////////////////////////////////////////////////

auto ECS::AddEntity()
{
    auto freeBit = entities.FindFirstFreeBit();
    com::Assert(freeBit.hasValue, "no free entity");
    entities.Set(freeBit.Value());
    return freeBit.Value();
}

///////////////////////////////////////////////////////////

void ECS::RemoveEntity()
{

}

///////////////////////////////////////////////////////////

void ECS::Update(gpu::RenderData& renderData)
{
    RenderSystem(arrays, renderData);
}

///////////////////////////////////////////////////////////

}//ns