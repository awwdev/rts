#pragma once

#include "ecs/ECS.hpp"
#include "gpu/RenderData.hpp"
#include "cmd/Timeline.hpp"
#include "app/Lockstep.hpp"
#include "gui/Editor/GUI_Stats.hpp"

///////////////////////////////////////////////////////////

namespace rts::app {

///////////////////////////////////////////////////////////

struct Scene 
{
    ecs::ECS ecs; //could be optional (optionally initialized)
    gpu::RenderData renderData;
    cmd::Timeline timeline;
    app::Lockstep lockstep;
    gui::GUI_Stats guiStats;

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

    for(auto i = 0; i < 1'000; ++i)
    {
        auto ID = ecs.AddEntity();
        auto& transformComponent = ecs.arrays.Add<ecs::TransformComponent>(ID);
        transformComponent.position  = { rand() % 600 / 2, rand() % 400 / 2 };
        transformComponent.positionTarget = transformComponent.position;
        transformComponent.size = { 64, 64 }; //double scale 
        auto& renderComponent = ecs.arrays.Add<ecs::RenderComponent>(ID);
        renderComponent.texIndex = 1;
    }
}

///////////////////////////////////////////////////////////

void Scene::Update()
{
    renderData.Clear();
    
    //test
    //FOR_ARRAY(app::glo::events, i)
    {
        //auto& event = app::events[i];
        //if (event.eventEnum == app::EventEnum::MB_LEFT_DOWN)
        //{
           //transformComponent->positionTarget = { event.xpos, event.ypos };
        //}
    }

    if (lockstep.Update())
    {
        ecs.Step();
    }
    ecs.Render(renderData, lockstep);
    guiStats.Update(renderData);

    //UI
}

///////////////////////////////////////////////////////////

}//ns