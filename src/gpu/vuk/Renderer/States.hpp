#pragma once

#include "gpu/vuk/Renderer/Commands.hpp"

#include "gpu/vuk/States/StateDefault.hpp"
#include "gpu/vuk/States/StatePost.hpp"
#include "gpu/vuk/States/StateUI.hpp"

#include "gpu/RenderData.hpp"
#include "res/Resources.hpp"

///////////////////////////////////////////////////////////

namespace rts::gpu::vuk {

///////////////////////////////////////////////////////////

struct States
{
    StateDefault stateDefault;
    StatePost    statePost;
    StateUI      stateUI;

    void Create(Context&, Commands&, res::Resources&, RenderData&);
    void Destroy();
    void Record(Commands&, uint32_t);
    void Update(RenderData&);
};

///////////////////////////////////////////////////////////

void States::Create(Context& context, Commands& commands, res::Resources& resources, RenderData& renderData)
{
    stateDefault.Create(context, commands, resources);
    statePost.Create(context, commands, resources, stateDefault);
    stateUI.Create(context, commands, resources);

    //recording once
    for(idx_t i = 0; i < context.swapchain.images.count; ++i)
    {
        Update(renderData);
        Record(commands, i);
    }        
}

///////////////////////////////////////////////////////////

void States::Destroy()
{
    statePost.Destroy();
    stateDefault.Destroy();
    stateUI.Destroy();
}

///////////////////////////////////////////////////////////

void States::Update(RenderData& renderData)
{
    stateDefault.Update(renderData);
    statePost.Update(renderData);
    stateUI.Update(renderData);
}

///////////////////////////////////////////////////////////

void States::Record(Commands& commands, uint32_t imageIndex)
{
    auto cmdBuffer = commands.buffers[imageIndex];
    auto beginInfo = CreateCmdBeginInfo();
    VkCheck(vkBeginCommandBuffer(cmdBuffer, &beginInfo));
    stateDefault.Record(cmdBuffer, imageIndex);
    statePost.Record(cmdBuffer, imageIndex);
    stateUI.Record(cmdBuffer, imageIndex);
    VkCheck(vkEndCommandBuffer(cmdBuffer));
}

///////////////////////////////////////////////////////////

}//ns