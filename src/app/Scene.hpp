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
    ecs::MainComponent* mainComponent;

    Scene();
    void Update();
};

///////////////////////////////////////////////////////////

Scene::Scene()
{
    com::Print(std::boolalpha, cmd::b);

    //test
    {
        auto  ID = ecs.AddEntity();
        auto& mainComponent = ecs.arrays.Add<ecs::MainComponent>(ID);
        mainComponent.pos  = { 16, 16 };
        mainComponent.size = { 32, 32 };
        mainComponent.textureId = 0;
    }

    auto  ID = ecs.AddEntity();
    mainComponent = &ecs.arrays.Add<ecs::MainComponent>(ID);
    mainComponent->pos  = { 16 + 32, 16 };
    mainComponent->size = { 32, 32 };
    mainComponent->textureId = 1;
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
            mainComponent->pos = { (f32)event.xpos, (f32)event.ypos };
        }
    }

    ecs.Update(renderData);
    //UI
}

///////////////////////////////////////////////////////////

}//ns