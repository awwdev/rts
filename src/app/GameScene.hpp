#pragma once

#include "ecs/ECS.hpp"
#include "gpu/RenderData.hpp"
#include "app/Camera.hpp"
#include "cmd/Timeline.hpp"
#include "com/Random.hpp"
#include "app/GameSceneInput.hpp"
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
    app::Camera camera;
    app::GameSceneInput input;

    GameScene();
    void Update();

private:
    void UpdateInput();
    void UpdateStep();
    void UpdateUI();
};

///////////////////////////////////////////////////////////

GameScene::GameScene()
{
    //test
    for(auto i = 0; i < 1; ++i)
    {
        auto ID = ecs.AddEntity();
        auto& mainComponent = ecs.arrays.Add<ecs::MainComponent>(ID);
        auto x = 128;//com::GetRandomNumber(0, 600);
        auto y = 128;//com::GetRandomNumber(0, 400);
        //com::Print(x, y);
        mainComponent.transform.SetPosition({x, y});
        mainComponent.transform.size = { 64, 64 };
        constexpr auto PX_PER_SEC = 64;
        mainComponent.transform.spd = PX_PER_SEC;
        mainComponent.sprite.texIdx = 0;
        mainComponent.sprite.frameTime = (com::GetRandomNumber(0, 100)) / 100.f;
    }

    //TODO swapresource for sprites to fight flickering
}

///////////////////////////////////////////////////////////

void GameScene::Update()
{
    app::Inputs::activeLayer = app::Inputs::ActiveLayer::Scene; //reset
    renderData.Clear();
    UpdateUI(); //before gamescene input (might set active input layer)
    input.Update(ecs, camera, renderData);
    UpdateStep();
}

///////////////////////////////////////////////////////////

void GameScene::UpdateStep()
{
    ecs.Render(renderData, timeline.StepTimePrevLerp());
    if (timeline.Update())
    {
        ecs.Update(timeline.stepIdx);
        timeline.Execute(ecs);
    }
}

///////////////////////////////////////////////////////////

void GameScene::UpdateUI()
{
    guiStats.Update(renderData, timeline); 
}

///////////////////////////////////////////////////////////

}//ns