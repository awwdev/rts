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
    com::AbsRecti selectionRect;
    void Update(ecs::ECS&, Camera&, gpu::RenderData&);
    com::Array<ecs::ID, 100> selection;

private:
    void Select(ecs::ECS&);
};

///////////////////////////////////////////////////////////

void GameSceneInput::Update(ecs::ECS& ecs, Camera& camera, gpu::RenderData& renderData)
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
        inputMode = InputMode::Selecting;    
        selectionRect.v1 = Inputs::mouse.pos;
    }
    if (Inputs::mouse.IsReleased(InputMouse::Left))
    { 
        inputMode = InputMode::None;  
    }

    //PROCESS STATE
    if (inputMode == InputMode::Selecting)
    {
        selectionRect.v2 = Inputs::mouse.pos;
        renderData.wire.AddRect(selectionRect);
        Select(ecs);
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
        if (selectionRect.IsPointInside(position))
        {
            auto entity = ecs.arrays.mainComponents.GetEntity(denseID);
            selection.Append(entity);
            com::Print(entity);
        }
    }
}

///////////////////////////////////////////////////////////

}//ns

/*
if (app::Inputs::mouse.IsPressed(app::InputMouse::Left))
{
    using namespace cmd;
    auto cmd = Command::InitUnion<CmdMove>();
    auto& cmdMove = cmd.cmdUnion.cmdMove;
    for(ecs::ID id = 0; id < 10; ++id)
        cmdMove.entities.Append(id);
    cmdMove.pos = app::Inputs::mouse.pos - camera.pos; 
    timeline.Store(cmd, timeline.stepIdx + 2);
}
*/