#include "rtpch.h"
#include "GraphicsContext.h"
#include "renderer.h"

#include "platform/opengl/GLGraphicsContext.h"

std::unique_ptr<GraphicsContext> GraphicsContext::create(void* window)
{
    switch (Renderer::getAPI())
    {
    case RendererAPI::API::None:
        ASSERT(false, "Invalid API: None");
        return nullptr;
    case RendererAPI::API::OpenGL:
        return std::make_unique<GLGraphicsContext>(window);
    }
}
