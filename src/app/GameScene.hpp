#pragma once

#include "ecs/ECS.hpp"
#include "gpu/RenderData.hpp"
#include "cmd/Timeline.hpp"
#include "gui/Editor/GUI_Stats.hpp"

///////////////////////////////////////////////////////////

namespace rts::app {

///////////////////////////////////////////////////////////

struct GameScene 
{
    ecs::ECS ecs;
    cmd::Timeline timeline;
    gpu::RenderData renderData;
    gui::GUI_Stats guiStats;

    GameScene();
    void Update();
};

///////////////////////////////////////////////////////////

GameScene::GameScene()
{
    for(auto i = 0; i < 1'00; ++i)
    {
        auto ID = ecs.AddEntity();
        auto& mainComponent = ecs.arrays.Add<ecs::MainComponent>(ID);
        auto x = rand() % 600;
        auto y = rand() % 400;
        mainComponent.transform.SetPosition({x, y});
        mainComponent.transform.size = { 64, 64 };
        constexpr auto PX_PER_SEC = 32;
        mainComponent.transform.spd = PX_PER_SEC;
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
    ecs.Render(renderData, timeline.StepTimePrevLerp());
    if (timeline.Update())
    {
        ecs.Update(timeline.stepIdx);
        timeline.Execute(ecs);
    }

    //? UI
    guiStats.Update(renderData, timeline);
    if (app::Inputs::keyboard.keys[27])
        app::Inputs::window.shouldClose = true;

    //test
    if (app::Inputs::mouse.IsPressed(app::InputMouse::Left))
    {
        cmd::Command cmd {};
        cmd.type = cmd::CmdEnum::Move;
        using namespace ecs;
        for(ecs::ID id = 0; id < 10; ++id)
            cmd.cmdUnion.cmdMove.entities.Append(id);
        cmd.cmdUnion.cmdMove.pos = app::Inputs::mouse.pos;
        timeline.Store(cmd, timeline.stepIdx + 2);
    }
}

///////////////////////////////////////////////////////////

}//ns