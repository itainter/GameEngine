#include "DrawingDevice.h"

using namespace Engine;

DrawingResource::DrawingResource(std::shared_ptr<DrawingDevice> pDevice) : m_pDevice(pDevice),
    m_pName(nullptr), m_pDesc(nullptr)
{
}

const std::shared_ptr<DrawingDevice>& DrawingResource::GetDevice()
{
    return m_pDevice;
}

const std::shared_ptr<std::string>& DrawingResource::GetName() const
{
    return m_pName;
}

void DrawingResource::SetName(std::shared_ptr<std::string> name)
{
    m_pName = name;
}

const std::shared_ptr<DrawingResourceDesc>& DrawingResource::GetDesc() const
{
    return m_pDesc;
}

void DrawingResource::SetDesc(std::shared_ptr<DrawingResourceDesc> desc)
{
    m_pDesc = desc;
}

DrawingTexture::DrawingTexture(std::shared_ptr<DrawingDevice> pDevice) : DrawingResourceWrapper<DrawingRawTexture>(pDevice)
{
}

DrawingTexture::~DrawingTexture()
{
}

EDrawingResourceType DrawingTexture::GetType() const
{
    return eResource_Texture;
}

DrawingShader::DrawingShader(std::shared_ptr<DrawingDevice> pDevice) : DrawingResourceWrapper<DrawingRawShader>(pDevice)
{
}

DrawingShader::~DrawingShader()
{
}

EDrawingResourceType DrawingVertexShader::GetType() const
{
    return eResource_Vertex_Shader;
}

EDrawingResourceType DrawingPixelShader::GetType() const
{
    return eResource_Pixel_Shader;
}

DrawingBlendState::DrawingBlendState(std::shared_ptr<DrawingDevice> pDevice) : DrawingResourceWrapper<DrawingRawBlendState>(pDevice)
{
}

DrawingBlendState::~DrawingBlendState()
{
}

EDrawingResourceType DrawingBlendState::GetType() const
{
    return eResource_Blend_State;
}

DrawingDepthState::DrawingDepthState(std::shared_ptr<DrawingDevice> pDevice) : DrawingResourceWrapper<DrawingRawDepthState>(pDevice)
{
}

DrawingDepthState::~DrawingDepthState()
{
}

EDrawingResourceType DrawingDepthState::GetType() const
{
    return eResource_Depth_State;
}

DrawingRasterState::DrawingRasterState(std::shared_ptr<DrawingDevice> pDevice) : DrawingResourceWrapper<DrawingRawRasterState>(pDevice)
{
}

DrawingRasterState::~DrawingRasterState()
{
}

EDrawingResourceType DrawingRasterState::GetType() const
{
    return eResource_Raster_State;
}

DrawingSamplerState::DrawingSamplerState(std::shared_ptr<DrawingDevice> pDevice) : DrawingResourceWrapper<DrawingRawSamplerState>(pDevice)
{
}

DrawingSamplerState::~DrawingSamplerState()
{
}

EDrawingResourceType DrawingSamplerState::GetType() const
{
    return eResource_Sampler_State;
}

DrawingVertexFormat::DrawingVertexFormat(std::shared_ptr<DrawingDevice> pDevice) : DrawingResourceWrapper<DrawingRawVertexFormat>(pDevice)
{
}

DrawingVertexFormat::~DrawingVertexFormat()
{
}

EDrawingResourceType DrawingVertexFormat::GetType() const
{
    return eResource_Vertex_Format;
}

DrawingVertexBuffer::DrawingVertexBuffer(std::shared_ptr<DrawingDevice> pDevice) : DrawingResourceWrapper<DrawingRawVertexBuffer>(pDevice)
{
}

DrawingVertexBuffer::~DrawingVertexBuffer()
{
}

EDrawingResourceType DrawingVertexBuffer::GetType() const
{
    return eResource_Vertex_Buffer;
}

DrawingIndexBuffer::DrawingIndexBuffer(std::shared_ptr<DrawingDevice> pDevice) : DrawingResourceWrapper<DrawingRawIndexBuffer>(pDevice)
{
}

DrawingIndexBuffer::~DrawingIndexBuffer()
{
}

EDrawingResourceType DrawingIndexBuffer::GetType() const
{
    return eResource_Index_Buffer;
}

DrawingTarget::DrawingTarget(std::shared_ptr<DrawingDevice> pDevice) : DrawingResourceWrapper<DrawingRawTarget>(pDevice)
{
}

DrawingTarget::~DrawingTarget()
{
}

EDrawingResourceType DrawingTarget::GetType() const
{
    return eResource_Target;
}

