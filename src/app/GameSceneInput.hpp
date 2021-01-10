#pragma once

#include "ecs/ECS.hpp"
#include "gpu/RenderData.hpp"
#include "app/Camera.hpp"
#include "cmd/Timeline.hpp"
#include "com/Array.hpp"
#include "com/Rect.hpp"

///////////////////////////////////////////////////////////

namespace rts::app {

///////////////////////////////////////////////////////////

struct GameSceneInput
{
    enum class InputMode 
    { 
        None, 
        Selecting 
    } 

    inputMode = InputMode::None;
    com::Recti selectionRect;
    void Update(ecs::ECS&, cmd::Timeline&, Camera&, gpu::RenderData&);
    com::Array<ecs::ID, 100> selection;
    bool selectBegin;

private:
    void Select(ecs::ECS&);
};

///////////////////////////////////////////////////////////

void GameSceneInput::Update(ecs::ECS& ecs, cmd::Timeline& timeline, Camera& camera, gpu::RenderData& renderData)
{
    camera.Update(renderData);
    if (app::Inputs::keyboard.keys[27]) //quick exit ESC
        app::Inputs::window.shouldClose = true;  

    //?SCENE LAYER
    if (Inputs::activeLayer != Inputs::ActiveLayer::Scene)
        return;

    //STATE
    if (Inputs::mouse.IsPressed(InputMouse::Left))
    {
        selectionRect.pos = Inputs::mouse.pos;
        selectBegin = true;
    }
    if (Inputs::mouse.IsHeld(InputMouse::Left))
    {
        if (selectBegin && selectionRect.pos != Inputs::mouse.pos)
            inputMode = InputMode::Selecting;  
    }
    if (Inputs::mouse.IsReleased(InputMouse::Left))
    { 
        inputMode = InputMode::None;  
        selectBegin = false;
    }
    if (Inputs::mouse.IsPressed(InputMouse::Right))
        selection.count = 0;

    //PROCESS STATE
    if (inputMode == InputMode::Selecting)
    {
        selectionRect.size = Inputs::mouse.pos - selectionRect.pos;
        renderData.wire.AddRect(selectionRect);
        Select(ecs);
    }
    if (inputMode == InputMode::None)
    {
        if (Inputs::mouse.IsPressed(InputMouse::Left))
        {
            using namespace cmd;
            auto cmd = Command::InitUnion<CmdMove>();
            auto& cmdMove = cmd.cmdUnion.cmdMove;
            cmdMove.entities.AppendArray(selection);
            cmdMove.pos = app::Inputs::mouse.pos - camera.pos; 
            timeline.Store(cmd, timeline.stepIdx + 2);
        }
    }
}

///////////////////////////////////////////////////////////

void GameSceneInput::Select(ecs::ECS& ecs)
{
    selection.count = 0;
    FOR_ARRAY(ecs.arrays.mainComponents.dense, denseID)
    {
        auto& mainComponent = ecs.arrays.mainComponents.dense[denseID];
        auto& position = mainComponent.transform.pos;
        //TODO camera pos offset
        if (selectionRect.IsPointInside(position))
        {
            auto entity = ecs.arrays.mainComponents.GetEntity(denseID);
            selection.Append(entity);
            //com::Print(entity);
        }
    }
}

///////////////////////////////////////////////////////////

}//ns