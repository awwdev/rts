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
    StateDefault state_Default;
    StatePost    state_Post;
    //StateUI      state_UI;

    void Create(Context&, Commands&, res::Resources&, RenderData&);
    void Destroy();
    void Record(Commands&, uint32_t);
    void Update(RenderData&);
};

///////////////////////////////////////////////////////////

void States::Create(Context& context, Commands& commands, res::Resources& resources, RenderData& renderData)
{
    state_Default.Create(context, commands, resources);
    state_Post.Create(context, commands, resources, state_Default);

    for(idx_t i = 0; i < context.swapchain.images.count; ++i)
    {
        Update(renderData);
        Record(commands, i);
    }        
}

///////////////////////////////////////////////////////////

void States::Destroy()
{
    state_Post.Destroy();
    state_Default.Destroy();
}

///////////////////////////////////////////////////////////

void States::Update(RenderData& renderData)
{
    state_Default.Update(renderData);
    state_Post.Update(renderData);
}

///////////////////////////////////////////////////////////

void States::Record(Commands& commands, uint32_t imageIndex)
{
    auto cmdBuffer = commands.buffers[imageIndex];
    auto beginInfo = CreateCmdBeginInfo();
    VkCheck(vkBeginCommandBuffer(cmdBuffer, &beginInfo));
    state_Default.Record(cmdBuffer, imageIndex);
    state_Post.Record(cmdBuffer, imageIndex);
    VkCheck(vkEndCommandBuffer(cmdBuffer));
}

///////////////////////////////////////////////////////////

}//ns