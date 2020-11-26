#pragma once

#include "gpu/vuk/States/DefaultState.hpp"
#include "gpu/RenderData.hpp"

///////////////////////////////////////////////////////////

namespace mini::gpu::vuk {

///////////////////////////////////////////////////////////

struct States
{
    DefaultState defaultState;

    void Create(Context&);
    void Destroy();
    void Record(Commands&, uint32_t);
    void Update(RenderData&);
};

///////////////////////////////////////////////////////////

void States::Create(Context& context)
{
    defaultState.Create(context);
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