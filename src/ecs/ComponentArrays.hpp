#pragma once

#include "ecs/ComponentArray.hpp"
#include "ecs/Components/TransformComponent.hpp"
#include "ecs/Components/RenderComponent.hpp"

///////////////////////////////////////////////////////////

namespace rts::ecs {

///////////////////////////////////////////////////////////

#define TEMPLATE template<typename T>

///////////////////////////////////////////////////////////

struct ComponentArrays 
{
    ComponentArray<TransformComponent> transformComponents;
    ComponentArray<RenderComponent>    renderComponents;
    
    TEMPLATE auto& Add(ID);
    TEMPLATE void  Remove(ID);
};

///////////////////////////////////////////////////////////

TEMPLATE 
auto& ComponentArrays::Add(ID entityID)
{
    if constexpr(std::is_same_v<T, TransformComponent>) return transformComponents.Add(entityID); 
    if constexpr(std::is_same_v<T, RenderComponent>)    return renderComponents.Add(entityID); 
}

///////////////////////////////////////////////////////////

TEMPLATE 
void ComponentArrays::Remove(ID entityID)
{
}

///////////////////////////////////////////////////////////

#undef TEMPLATE

///////////////////////////////////////////////////////////

}//ns