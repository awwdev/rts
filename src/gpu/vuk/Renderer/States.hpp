#pragma once

#include "gpu/vuk/States/DefaultState.hpp"
#include "gpu/vuk/Renderer/Commands.hpp"

#include "gpu/RenderData.hpp"
#include "res/Resources.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

struct States
{
    DefaultState defaultState;

    void Create(Context&, Commands&, res::Resources&);
    void Destroy();
    void Record(Commands&, uint32_t);
    void Update(RenderData&);
};

///////////////////////////////////////////////////////////

void States::Create(Context& context, Commands& cmds, res::Resources& resources)
{
    defaultState.Create(context, cmds, resources);
}

///////////////////////////////////////////////////////////

void States::Destroy()
{
    defaultState.Destroy();
}

///////////////////////////////////////////////////////////

void States::Update(RenderData& renderData)
{
    defaultState.Update(renderData);
}

///////////////////////////////////////////////////////////

void States::Record(Commands& commands, uint32_t imageIndex)
{
    auto cmdBuffer = commands.buffers[imageIndex];
    const auto beginInfo = CreateCmdBeginInfo();
    VkCheck(vkBeginCommandBuffer(cmdBuffer, &beginInfo));
    defaultState.Record(cmdBuffer, imageIndex);
    VkCheck(vkEndCommandBuffer(cmdBuffer));
}

///////////////////////////////////////////////////////////

}//ns