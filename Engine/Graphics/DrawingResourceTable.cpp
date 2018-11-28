#include "DrawingDevice.h"
#include "DrawingResourceDesc.h"

#include "DrawingResourceTable.h"

using namespace Engine;

DrawingResourceFactory::DrawingResourceFactory(std::shared_ptr<DrawingDevice> pDevice) : m_pDevice(pDevice)
{
}

DrawingResourceFactory::~DrawingResourceFactory()
{
    m_pDevice = nullptr;
}

bool DrawingResourceFactory::CreateResource(const DrawingResourceDesc& desc, std::shared_ptr<DrawingResource>& pRes, const void* pData, uint32_t size) const
{
    bool result = false;

    switch (desc.GetType())
    {
    case eResource_Vertex_Format:   result = CreateVertexFormat(desc, pRes); break;
    case eResource_Vertex_Buffer:   result = CreateVertexBuffer(desc, pRes, pData, size); break;
    case eResource_Index_Buffer:    result = CreateIndexBuffer(desc, pRes, pData, size); break;
    case eResource_Texture:         result = CreateTexture(desc, pRes, pData, size); break;
    case eResource_Blend_State:     result = CreateBlendState(desc, pRes); break;
    case eResource_Depth_State:     result = CreateDepthState(desc, pRes); break;
    case eResource_Raster_State:    result = CreateRasterState(desc, pRes); break;
    case eResource_Sampler_State:   result = CreateSamplerState(desc, pRes); break;
    case eResource_Vertex_Shader:   result = CreateVertexShader(desc, pRes); break;
    case eResource_Pixel_Shader:    result = CreatePixelShader(desc, pRes); break;
    case eResource_Primitive:       result = CreatePrimitiveInfo(desc, pRes); break;
    default:
        result = false;
        break;
    }

    return result;
}

bool DrawingResourceFactory::CreateVertexFormat(const DrawingResourceDesc& desc, std::shared_ptr<DrawingResource>& pRes) const
{
    auto pDesc = static_cast<const DrawingVertexFormatDesc*>(&desc);
    if (pDesc == nullptr)
        return false;

    std::shared_ptr<DrawingVertexFormat> pVertexFormat;
    bool result = m_pDevice->CreateVertexFormat(*pDesc, pVertexFormat);
    pRes = pVertexFormat;

    return result;
}

bool DrawingResourceFactory::CreateVertexBuffer(const DrawingResourceDesc& desc, std::shared_ptr<DrawingResource>& pRes, const void* pData, uint32_t size) const
{
    auto pDesc = static_cast<const DrawingVertexBufferDesc*>(&desc);
    if (pDesc == nullptr)
        return false;

    std::shared_ptr<DrawingVertexBuffer> pVertexBuffer;
    bool result = m_pDevice->CreateVertexBuffer(*pDesc, pVertexBuffer, pData, size);
    pRes = pVertexBuffer;

    return result;
}

bool DrawingResourceFactory::CreateIndexBuffer(const DrawingResourceDesc& desc, std::shared_ptr<DrawingResource>& pRes, const void* pData, uint32_t size) const
{
    auto pDesc = static_cast<const DrawingIndexBufferDesc*>(&desc);
    if (pDesc == nullptr)
        return false;

    std::shared_ptr<DrawingIndexBuffer> pIndexBuffer;
    bool result = m_pDevice->CreateIndexBuffer(*pDesc, pIndexBuffer, pData, size);
    pRes = pIndexBuffer;

    return result;
}

bool DrawingResourceFactory::CreateTexture(const DrawingResourceDesc& desc, std::shared_ptr<DrawingResource>& pRes, const void* pData, uint32_t size) const
{
    auto pDesc = static_cast<const DrawingTextureDesc*>(&desc);
    if (pDesc == nullptr)
        return false;

    std::shared_ptr<DrawingTexture> pTexture;
    bool result = m_pDevice->CreateTexture(*pDesc, pTexture, pData, size);
    pRes = pTexture;

    return result;
}

bool DrawingResourceFactory::CreateBlendState(const DrawingResourceDesc& desc, std::shared_ptr<DrawingResource>& pRes) const
{
    auto pDesc = static_cast<const DrawingBlendStateDesc*>(&desc);
    if (pDesc == nullptr)
        return false;

    std::shared_ptr<DrawingBlendState> pBlendState;
    bool result = m_pDevice->CreateBlendState(*pDesc, pBlendState);
    pRes = pBlendState;

    return result;
}

bool DrawingResourceFactory::CreateDepthState(const DrawingResourceDesc& desc, std::shared_ptr<DrawingResource>& pRes) const
{
    auto pDesc = static_cast<const DrawingDepthStateDesc*>(&desc);
    if (pDesc == nullptr)
        return false;

    std::shared_ptr<DrawingDepthState> pDepthState;
    bool result = m_pDevice->CreateDepthState(*pDesc, pDepthState);
    pRes = pDepthState;

    return result;
}

bool DrawingResourceFactory::CreateRasterState(const DrawingResourceDesc& desc, std::shared_ptr<DrawingResource>& pRes) const
{
    auto pDesc = static_cast<const DrawingRasterStateDesc*>(&desc);
    if (pDesc == nullptr)
        return false;

    std::shared_ptr<DrawingRasterState> pRasterState;
    bool result = m_pDevice->CreateRasterState(*pDesc, pRasterState);
    pRes = pRasterState;

    return result;
}

bool DrawingResourceFactory::CreateSamplerState(const DrawingResourceDesc& desc, std::shared_ptr<DrawingResource>& pRes) const
{
    auto pDesc = static_cast<const DrawingSamplerStateDesc*>(&desc);
    if (pDesc == nullptr)
        return false;

    std::shared_ptr<DrawingSamplerState> pSamplerState;
    bool result = m_pDevice->CreateSamplerState(*pDesc, pSamplerState);
    pRes = pSamplerState;

    return result;
}

bool DrawingResourceFactory::CreateVertexShader(const DrawingResourceDesc& desc, std::shared_ptr<DrawingResource>& pRes) const
{
    return true;
}

bool DrawingResourceFactory::CreatePixelShader(const DrawingResourceDesc& desc, std::shared_ptr<DrawingResource>& pRes) const
{
    return true;
}

bool DrawingResourceFactory::CreatePrimitiveInfo(const DrawingResourceDesc& desc, std::shared_ptr<DrawingResource>& pRes) const
{
    auto pDesc = static_cast<const DrawingPrimitiveDesc*>(&desc);
    if (pDesc == nullptr)
        return false;

    std::shared_ptr<DrawingPrimitive> pPrimitive;
    bool result = m_pDevice->CreatePrimitiveInfo(*pDesc, pPrimitive);
    pRes = pPrimitive;

    return result;
}

bool DrawingResourceTable::ResourceEntry::CreateResource()
{
    if (m_pRes != nullptr)
        return true;

    std::shared_ptr<DrawingResource> pRes = nullptr;
    if (!m_factory.CreateResource(*m_pDesc.get(), pRes, m_pData, m_size))
        return false;

    m_pRes = pRes;

    return true;
}

std::shared_ptr<DrawingResource> DrawingResourceTable::ResourceEntry::GetResource()
{
    return m_pRes;
}

const std::shared_ptr<DrawingResourceDesc> DrawingResourceTable::ResourceEntry::GetDesc() const
{
    return m_pDesc;
}

void DrawingResourceTable::ResourceEntry::SetDesc(std::shared_ptr<DrawingResourceDesc> pDesc)
{
    if (m_pDesc != pDesc)
    {
        m_pDesc = pDesc;
        m_pRes = nullptr;
    }
}

DrawingResourceTable::ResourceEntry::ResourceEntry(const DrawingResourceDesc& desc, const DrawingResourceFactory& factory, DrawingResourceTable& table) :
    m_pDesc(std::make_shared<DrawingResourceDesc>(&desc)), m_pRes(nullptr), m_pData(nullptr), m_size(0), m_factory(factory)
{
}

DrawingResourceTable::ResourceEntry::~ResourceEntry()
{
    m_pDesc = nullptr;
    m_pRes = nullptr;
}