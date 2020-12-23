#pragma once

#include "ecs/Systems/RenderSystem.hpp"
#include "ecs/Systems/TransformSystem.hpp"

#include "ecs/ComponentArrays.hpp"
#include "gpu/RenderData.hpp"
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
    void Update(idx_t);
    void Render(gpu::RenderData&, f32);
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

void ECS::Update(idx_t stepIdx)
{
    TransformSystem(arrays, stepIdx);
}

///////////////////////////////////////////////////////////

void ECS::Render(gpu::RenderData& renderData, f32 stepProgress)
{
    RenderSystem(arrays, renderData.sprites, stepProgress);
}

///////////////////////////////////////////////////////////

}//ns