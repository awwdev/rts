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

    Scene();
    void Update();
};

///////////////////////////////////////////////////////////

Scene::Scene()
{
    for(auto i = 0; i < 100; ++i)
    {
        auto ID = ecs.AddEntity();
        auto& transformComponent = ecs.arrays.Add<ecs::TransformComponent>(ID);
        auto x = rand() % 600;
        auto y = rand() % 400;
        transformComponent.position = { x, y };
        transformComponent.positionTarget = { x, y };
        transformComponent.size = { 64, 64 }; //double scale 
        auto& renderComponent = ecs.arrays.Add<ecs::RenderComponent>(ID);
        renderComponent.texIndex = 0;
    }
}

///////////////////////////////////////////////////////////

void Scene::Update()
{
    //? CLEAR
    renderData.Clear();

    //? ECS
    if (lockstep.Update())
        ecs.Step();
    ecs.Render(renderData, lockstep);

    //? UI
    guiStats.Update(renderData);

    if (app::Inputs::keyboard.keys[27])
        app::Inputs::window.shouldClose = true;
}

///////////////////////////////////////////////////////////

}//ns





/*
//ecs::TransformComponent* transformComponent;

//auto ID = ecs.AddEntity();
//ecs.arrays.Add<ecs::RenderComponent>(ID);
//transformComponent = &ecs.arrays.Add<ecs::TransformComponent>(ID);
//transformComponent->position  = { 32, 32 };
//transformComponent->positionTarget = transformComponent->position;
//transformComponent->size = { 32, 32 };

//FOR_ARRAY(app::glo::events, i)
{
//auto& event = app::events[i];
//if (event.eventEnum == app::EventEnum::MB_LEFT_DOWN)
//{
//transformComponent->positionTarget = { event.xpos, event.ypos };
//}
}

*/