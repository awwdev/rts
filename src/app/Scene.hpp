#pragma once

#include "ecs/ECS.hpp"
#include "gpu/RenderData.hpp"
#include "cmd/Timeline.hpp"

///////////////////////////////////////////////////////////

namespace rts::app {

///////////////////////////////////////////////////////////

struct Scene 
{
    ecs::ECS ecs; //could be optional (optionally initialized)
    gpu::RenderData renderData;
    cmd::Timeline timeline;

    //test
    ecs::TransformComponent* transformComponent;

    Scene();
    void Update();
};

///////////////////////////////////////////////////////////

Scene::Scene()
{
    //test
    auto ID = ecs.AddEntity();
    ecs.arrays.Add<ecs::RenderComponent>(ID);
    transformComponent = &ecs.arrays.Add<ecs::TransformComponent>(ID);
    transformComponent->position  = { 16 + 32, 16 };
    transformComponent->size = { 32, 32 };

    {
        auto ID = ecs.AddEntity();
        auto& transformComponent = ecs.arrays.Add<ecs::TransformComponent>(ID);
        transformComponent.position  = { 64, 64 };
        transformComponent.size = { 64, 64 };
        auto& renderComponent = ecs.arrays.Add<ecs::RenderComponent>(ID);
        renderComponent.textureId = 1;
    }
}

///////////////////////////////////////////////////////////

void Scene::Update()
{
    //test
    FOR_ARRAY(app::events, i)
    {
        auto& event = app::events[i];
        if (event.eventEnum == app::EventEnum::MB_LEFT_DOWN)
        {
            transformComponent->position = { event.xpos, event.ypos };
        }
    }

    ecs.Update(renderData);
    //UI
}

///////////////////////////////////////////////////////////

}//ns