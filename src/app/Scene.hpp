#pragma once

#include "ecs/ECS.hpp"
#include "gpu/RenderData.hpp"
#include "cmd/Timeline.hpp"
#include "app/Lockstep.hpp"

///////////////////////////////////////////////////////////

namespace rts::app {

///////////////////////////////////////////////////////////

struct Scene 
{
    ecs::ECS ecs; //could be optional (optionally initialized)
    gpu::RenderData renderData;
    cmd::Timeline timeline;
    app::Lockstep lockstep;

    //test
    //ecs::TransformComponent* transformComponent;

    Scene();
    void Update();
};

///////////////////////////////////////////////////////////

Scene::Scene()
{
    //test
    //auto ID = ecs.AddEntity();
    //ecs.arrays.Add<ecs::RenderComponent>(ID);
    //transformComponent = &ecs.arrays.Add<ecs::TransformComponent>(ID);
    //transformComponent->position  = { 32, 32 };
    //transformComponent->positionTarget = transformComponent->position;
    //transformComponent->size = { 32, 32 };

    for(auto i = 0; i < 1000; ++i)
    {
        auto ID = ecs.AddEntity();
        auto& transformComponent = ecs.arrays.Add<ecs::TransformComponent>(ID);
        transformComponent.position  = { rand() % 600 / 2, rand() % 400 / 2 };
        transformComponent.positionTarget = transformComponent.position;
        transformComponent.size = { 32, 32 };
        auto& renderComponent = ecs.arrays.Add<ecs::RenderComponent>(ID);
        renderComponent.texIndex = 1;
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
            //transformComponent->positionTarget = { event.xpos, event.ypos };
        }
    }

    if (lockstep.Update())
    {
        ecs.Step();
    }
    ecs.Render(renderData, lockstep);

    //UI
}

///////////////////////////////////////////////////////////

}//ns