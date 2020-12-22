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
    for(auto i = 0; i < 1'00; ++i)
    {
        auto ID = ecs.AddEntity();
        auto& mainComponent = ecs.arrays.Add<ecs::MainComponent>(ID);
        auto x = rand() % 600;
        auto y = rand() % 400;
        mainComponent.transform.SetPosition({x, y});
        mainComponent.transform.size = { 64, 64 };
        mainComponent.transform.spd = 2 + rand() % 8;
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
    ecs.Render(renderData, lockstep, lockstep.StepLerpProgress());
    if (lockstep.Update())
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
        cmd::CmdsPerStep cmds; //TODO somewhere else
        cmd::Command cmd {};
        cmd.type = cmd::CmdEnum::Move;
        using namespace ecs;
        for(ecs::ID id = 0; id < 10; ++id)
            cmd.cmdUnion.cmdMove.entities.Append(id);
        cmd.cmdUnion.cmdMove.pos = app::Inputs::mouse.pos;
        cmds.Append(cmd);
        timeline.Store(cmds, 0.1, timeline.stepIdx + 2);
    }
}

///////////////////////////////////////////////////////////

}//ns