#pragma once

#include "ecs/EntityID.hpp"
#include "com/POD_Array.hpp"

///////////////////////////////////////////////////////////

namespace rts::ecs {

///////////////////////////////////////////////////////////

#define TEMPLATE template<typename T, auto N>

///////////////////////////////////////////////////////////

template<typename T, auto N = ENTITY_COUNT_MAX>
struct ComponentArray
{
    com::POD_Array<T, N> dense;
    ID denseLookup [N];  //via entity id
    ID entityLookup [N]; //via dense index

    auto& Add(ID entityID);
    void  Remove(ID entityID);
    auto  GetEntity(ID denseID) const;
    auto& GetComponent(ID entityID);
};

///////////////////////////////////////////////////////////

TEMPLATE 
auto& ComponentArray<T, N>::Add(ID entityID)
{
    auto& component = dense.Append();
    auto denseIdx = dense.count - 1;
    denseLookup[entityID] = denseIdx;
    entityLookup[denseIdx] = entityID;
    return component;
}

///////////////////////////////////////////////////////////

TEMPLATE 
void ComponentArray<T, N>::Remove(ID entityID)
{
    
}

///////////////////////////////////////////////////////////

TEMPLATE
auto ComponentArray<T, N>::GetEntity(ID denseID) const
{
    return entityLookup[denseID];
}

///////////////////////////////////////////////////////////

TEMPLATE
auto& ComponentArray<T, N>::GetComponent(ID entityID) 
{
    return dense[denseLookup[entityID]];
}

///////////////////////////////////////////////////////////


#undef TEMPLATE

///////////////////////////////////////////////////////////

}//ns