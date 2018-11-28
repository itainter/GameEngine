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

DrawingPrimitive::DrawingPrimitive(std::shared_ptr<DrawingDevice> pDevice) : DrawingResource(pDevice)
{
}

DrawingPrimitive::~DrawingPrimitive()
{
}

EDrawingPrimitiveType DrawingPrimitive::GetPrimitiveType() const
{
    return mPrimitiveType;
}

void DrawingPrimitive::SetPrimitiveType(EDrawingPrimitiveType type)
{
    mPrimitiveType = type;
}

uint32_t DrawingPrimitive::GetVertexCount() const
{
    return mVertexCount;
}

void DrawingPrimitive::SetVertexCount(uint32_t count)
{
    mVertexCount = count;
}

uint32_t DrawingPrimitive::GetIndexCount() const
{
    return mIndexCount;
}

void DrawingPrimitive::SetIndexCount(uint32_t count)
{
    mIndexCount = count;
}

uint32_t DrawingPrimitive::GetInstanceCount() const
{
    return mInstanceCount;
}

void DrawingPrimitive::SetInstanceCount(uint32_t count)
{
    mInstanceCount = count;
}

uint32_t DrawingPrimitive::GetVertexOffset() const
{
    return mVertexOffset;
}

void DrawingPrimitive::SetVertexOffset(uint32_t offset)
{
    mVertexOffset = offset;
}

uint32_t DrawingPrimitive::GetIndexOffset() const
{
    return mIndexOffset;
}

void DrawingPrimitive::SetIndexoffset(uint32_t offset)
{
    mIndexOffset = offset;
}

uint32_t DrawingPrimitive::GetInstanceOffset() const
{
    return mInstanceOffset;
}

void DrawingPrimitive::SetInstanceOffset(uint32_t offset)
{
    mInstanceOffset = offset;
}

EDrawingResourceType DrawingPrimitive::GetType() const
{
    return eResource_Primitive;;
}

DrawingContext::DrawingContext(std::shared_ptr<DrawingDevice> pDevice) : m_pNativeContext(nullptr), m_pDevice(pDevice)
{
}

DrawingContext::~DrawingContext()
{
    m_pNativeContext = nullptr;
    m_pDevice = nullptr;
}

std::shared_ptr<DrawingNativeContext> DrawingContext::GetNativeContext()
{
    return m_pNativeContext;
}

void DrawingContext::SetNativeContext(std::shared_ptr<DrawingNativeContext> context)
{
    m_pNativeContext = context;
}
