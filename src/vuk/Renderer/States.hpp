#pragma once

#include "vuk/States/DefaultState.hpp"

///////////////////////////////////////////////////////////

namespace mini::vuk {

///////////////////////////////////////////////////////////

struct States
{
    DefaultState defaultState;

    void Create(Context&);
    void Destroy();
    void Record(Commands&, uint32_t);
};

////////////////////////////////////////////////////////////

void States::Create(Context& context)
{
    defaultState.Create(context);
}

////////////////////////////////////////////////////////////

void States::Destroy()
{
    defaultState.Destroy();
}

////////////////////////////////////////////////////////////

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