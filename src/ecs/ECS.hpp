#pragma once

#include "ecs/Systems/RenderSystem.hpp"
#include "ecs/ComponentArrays.hpp"
#include "gpu/RenderData.hpp"
#include "com/Bitset.hpp"

///////////////////////////////////////////////////////////

namespace mini::ecs {

///////////////////////////////////////////////////////////

#define TEMPLATE template<typename T>

///////////////////////////////////////////////////////////

struct ECS 
{
    com::Bitset<ENTITY_COUNT_MAX> entities;
    ComponentArrays arrays;

    auto AddEntity();
    void RemoveEntity();
    void Update(gpu::RenderData&);

    TEMPLATE auto& AddComponent(ID);
    TEMPLATE void  RemoveComponent(ID);
};

///////////////////////////////////////////////////////////

auto ECS::AddEntity()
{
    auto freeBit = entities.FindFirstFreeBit();
    com::Assert(freeBit.hasValue, "no free entity");

    return (ID) 0;
}

///////////////////////////////////////////////////////////

void ECS::RemoveEntity()
{

}

///////////////////////////////////////////////////////////

TEMPLATE
auto& ECS::AddComponent(ID entityID)
{
    return arrays.mainComponents.dense[0];
}

///////////////////////////////////////////////////////////

TEMPLATE
void ECS::RemoveComponent(ID entityID)
{

}

///////////////////////////////////////////////////////////

void ECS::Update(gpu::RenderData& renderData)
{
    //calling systems
    RenderSystem(arrays, renderData);
}

///////////////////////////////////////////////////////////

#undef TEMPLATE

///////////////////////////////////////////////////////////

}//ns