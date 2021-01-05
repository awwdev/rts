#pragma once

#include "ecs/ECS.hpp"
#include "gpu/RenderData.hpp"
#include "app/Camera.hpp"
#include "cmd/Timeline.hpp"

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
    com::Vec2i selectionBegin;

    void Update(ecs::ECS&, Camera&, gpu::RenderData&);
};

///////////////////////////////////////////////////////////

void GameSceneInput::Update(ecs::ECS& ecs, Camera& camera, gpu::RenderData& renderData)
{
    camera.Update(renderData);

    //input state mode determine
    if (Inputs::mouse.IsPressed(InputMouse::Left))
    {
        inputMode = InputMode::Selecting;    
        selectionBegin = Inputs::mouse.pos;
    }
    if (Inputs::mouse.IsReleased(InputMouse::Left))
    {
        inputMode = InputMode::None;  
    }

    //input state mode process
    if (inputMode == InputMode::Selecting)
    {
        renderData.wire.AddRect(selectionBegin, Inputs::mouse.pos);
    }

    //quick exit app
    if (app::Inputs::keyboard.keys[27])
        app::Inputs::window.shouldClose = true;  
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