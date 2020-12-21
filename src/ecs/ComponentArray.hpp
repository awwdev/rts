#pragma once

#include "ecs/EntityID.hpp"
#include "com/POD_Array.hpp"
#include "com/Utils.hpp"

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

    void Swap(ID, ID);
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

TEMPLATE
void ComponentArray<T, N>::Swap(ID idx1, ID idx2)
{
    com::Swap(dense.data, idx1, idx2);
    com::Swap(denseLookup, entityLookup[idx1], entityLookup[idx2]);
    com::Swap(entityLookup, idx1, idx2);
}

///////////////////////////////////////////////////////////

#undef TEMPLATE

///////////////////////////////////////////////////////////

}//ns