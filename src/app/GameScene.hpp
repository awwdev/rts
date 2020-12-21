#pragma once

#include "ecs/ECS.hpp"
#include "gpu/RenderData.hpp"
#include "cmd/Timeline.hpp"
#include "cmd/Lockstep.hpp"
#include "gui/Editor/GUI_Stats.hpp"

///////////////////////////////////////////////////////////

namespace rts::app {

///////////////////////////////////////////////////////////

struct GameScene 
{
    ecs::ECS ecs;
    cmd::Timeline timeline;
    cmd::Lockstep lockstep;
    gpu::RenderData renderData;
    gui::GUI_Stats guiStats;

    GameScene();
    void Update();
};

///////////////////////////////////////////////////////////

GameScene::GameScene()
{
    for(auto i = 0; i < 1; ++i)
    {
        auto ID = ecs.AddEntity();
        auto& mainComponent = ecs.arrays.Add<ecs::MainComponent>(ID);
        auto x = rand() % 600;
        auto y = rand() % 400;
        mainComponent.transform.pos  = { x, y };
        mainComponent.transform.posTarget = mainComponent.transform.pos;
        mainComponent.transform.size = { 64, 64 };
        mainComponent.sprite.texIdx = 0;
        mainComponent.sprite.time = (rand() % 100) / 100.f;
    }
}

///////////////////////////////////////////////////////////

void GameScene::Update()
{
    //? CLEAR
    renderData.Clear();

    //? ECS
    if (lockstep.Update())
    {
        ecs.Update(timeline.stepIdx);
        timeline.stepIdx++;
    }
    ecs.Render(renderData, lockstep);

    //? UI
    guiStats.Update(renderData, timeline);

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