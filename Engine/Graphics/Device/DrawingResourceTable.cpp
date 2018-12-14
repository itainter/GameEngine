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

bool DrawingResourceFactory::CreateResource(const std::shared_ptr<DrawingResourceDesc>& pDesc, std::shared_ptr<DrawingResource>& pRes, const void* pData, uint32_t size) const
{
    bool result = false;

    switch (pDesc->GetType())
    {
    case eResource_Vertex_Format:   result = CreateVertexFormat(pDesc, pRes); break;
    case eResource_Vertex_Buffer:   result = CreateVertexBuffer(pDesc, pRes, pData, size); break;
    case eResource_Index_Buffer:    result = CreateIndexBuffer(pDesc, pRes, pData, size); break;
    case eResource_Texture:         result = CreateTexture(pDesc, pRes, pData, size); break;
    case eResource_Blend_State:     result = CreateBlendState(pDesc, pRes); break;
    case eResource_Depth_State:     result = CreateDepthState(pDesc, pRes); break;
    case eResource_Raster_State:    result = CreateRasterState(pDesc, pRes); break;
    case eResource_Sampler_State:   result = CreateSamplerState(pDesc, pRes); break;
    case eResource_Vertex_Shader:   result = CreateVertexShader(pDesc, pRes); break;
    case eResource_Pixel_Shader:    result = CreatePixelShader(pDesc, pRes); break;
    case eResource_Primitive:       result = CreatePrimitiveInfo(pDesc, pRes); break;
    default:
        result = false;
        break;
    }

    return result;
}

bool DrawingResourceFactory::CreateVertexFormat(const std::shared_ptr<DrawingResourceDesc>& pDesc, std::shared_ptr<DrawingResource>& pRes) const
{
    auto pVertexFormatDesc = std::static_pointer_cast<const DrawingVertexFormatDesc>(pDesc);
    if (pVertexFormatDesc == nullptr)
        return false;

    std::shared_ptr<DrawingVertexFormat> pVertexFormat;
    bool result = m_pDevice->CreateVertexFormat(*pVertexFormatDesc, pVertexFormat);
    pRes = pVertexFormat;

    return result;
}

bool DrawingResourceFactory::CreateVertexBuffer(const std::shared_ptr<DrawingResourceDesc>& pDesc, std::shared_ptr<DrawingResource>& pRes, const void* pData, uint32_t size) const
{
    auto pVertexBufferDesc = std::static_pointer_cast<const DrawingVertexBufferDesc>(pDesc);
    if (pVertexBufferDesc == nullptr)
        return false;

    std::shared_ptr<DrawingVertexBuffer> pVertexBuffer;
    bool result = m_pDevice->CreateVertexBuffer(*pVertexBufferDesc, pVertexBuffer, nullptr, pData, size);
    pRes = pVertexBuffer;

    return result;
}

bool DrawingResourceFactory::CreateIndexBuffer(const std::shared_ptr<DrawingResourceDesc>& pDesc, std::shared_ptr<DrawingResource>& pRes, const void* pData, uint32_t size) const
{
    auto pIndexBufferDesc = std::static_pointer_cast<const DrawingIndexBufferDesc>(pDesc);
    if (pIndexBufferDesc == nullptr)
        return false;

    std::shared_ptr<DrawingIndexBuffer> pIndexBuffer;
    bool result = m_pDevice->CreateIndexBuffer(*pIndexBufferDesc, pIndexBuffer, nullptr, pData, size);
    pRes = pIndexBuffer;

    return result;
}

bool DrawingResourceFactory::CreateTexture(const std::shared_ptr<DrawingResourceDesc>& pDesc, std::shared_ptr<DrawingResource>& pRes, const void* pData, uint32_t size) const
{
    auto pTextureDesc = std::static_pointer_cast<const DrawingTextureDesc>(pDesc);
    if (pTextureDesc == nullptr)
        return false;

    std::shared_ptr<DrawingTexture> pTexture;
    bool result = m_pDevice->CreateTexture(*pTextureDesc, pTexture, pData, size);
    pRes = pTexture;

    return result;
}

bool DrawingResourceFactory::CreateBlendState(const std::shared_ptr<DrawingResourceDesc>& pDesc, std::shared_ptr<DrawingResource>& pRes) const
{
    auto pBlendStateDesc = std::static_pointer_cast<const DrawingBlendStateDesc>(pDesc);
    if (pBlendStateDesc == nullptr)
        return false;

    std::shared_ptr<DrawingBlendState> pBlendState;
    bool result = m_pDevice->CreateBlendState(*pBlendStateDesc, pBlendState);
    pRes = pBlendState;

    return result;
}

bool DrawingResourceFactory::CreateDepthState(const std::shared_ptr<DrawingResourceDesc>& pDesc, std::shared_ptr<DrawingResource>& pRes) const
{
    auto pDepthStateDesc = std::static_pointer_cast<const DrawingDepthStateDesc>(pDesc);
    if (pDepthStateDesc == nullptr)
        return false;

    std::shared_ptr<DrawingDepthState> pDepthState;
    bool result = m_pDevice->CreateDepthState(*pDepthStateDesc, pDepthState);
    pRes = pDepthState;

    return result;
}

bool DrawingResourceFactory::CreateRasterState(const std::shared_ptr<DrawingResourceDesc>& pDesc, std::shared_ptr<DrawingResource>& pRes) const
{
    auto pRasterStateDesc = std::static_pointer_cast<const DrawingRasterStateDesc>(pDesc);
    if (pRasterStateDesc == nullptr)
        return false;

    std::shared_ptr<DrawingRasterState> pRasterState;
    bool result = m_pDevice->CreateRasterState(*pRasterStateDesc, pRasterState);
    pRes = pRasterState;

    return result;
}

bool DrawingResourceFactory::CreateSamplerState(const std::shared_ptr<DrawingResourceDesc>& pDesc, std::shared_ptr<DrawingResource>& pRes) const
{
    auto pSamplerStateDesc = std::static_pointer_cast<const DrawingSamplerStateDesc>(pDesc);
    if (pSamplerStateDesc == nullptr)
        return false;

    std::shared_ptr<DrawingSamplerState> pSamplerState;
    bool result = m_pDevice->CreateSamplerState(*pSamplerStateDesc, pSamplerState);
    pRes = pSamplerState;

    return result;
}

bool DrawingResourceFactory::CreateVertexShader(const std::shared_ptr<DrawingResourceDesc>& pDesc, std::shared_ptr<DrawingResource>& pRes) const
{
    return true;
}

bool DrawingResourceFactory::CreatePixelShader(const std::shared_ptr<DrawingResourceDesc>& pDesc, std::shared_ptr<DrawingResource>& pRes) const
{
    return true;
}

bool DrawingResourceFactory::CreatePrimitiveInfo(const std::shared_ptr<DrawingResourceDesc>& pDesc, std::shared_ptr<DrawingResource>& pRes) const
{
    auto pPrimitiveInfoDesc = std::static_pointer_cast<const DrawingPrimitiveDesc>(pDesc);
    if (pPrimitiveInfoDesc == nullptr)
        return false;

    std::shared_ptr<DrawingPrimitive> pPrimitiveInfo;
    bool result = m_pDevice->CreatePrimitiveInfo(*pPrimitiveInfoDesc, pPrimitiveInfo);
    pRes = pPrimitiveInfo;

    return result;
}


DrawingResourceTable::ResourceEntry::~ResourceEntry()
{
    m_pDesc = nullptr;
    m_pRes = nullptr;
}

bool DrawingResourceTable::ResourceEntry::CreateResource()
{
    if (m_pRes != nullptr)
        return true;

    std::shared_ptr<DrawingResource> pRes = nullptr;
    if (!m_factory.CreateResource(m_pDesc, pRes, m_pData, m_size))
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

DrawingResourceTable::ResourceEntry::ResourceEntry(std::shared_ptr<DrawingResourceDesc> pDesc, const DrawingResourceFactory& factory, DrawingResourceTable& table) :
    m_pDesc(pDesc), m_pRes(nullptr), m_pData(nullptr), m_size(0), m_factory(factory)
{
}

DrawingResourceTable::DrawingResourceTable(const DrawingResourceFactory& factory) : m_factory(factory)
{
}

DrawingResourceTable::~DrawingResourceTable()
{
    ClearResourceEntries();
}

std::shared_ptr<DrawingResourceTable::ResourceEntry> DrawingResourceTable::GetResourceEntry(std::shared_ptr<std::string> pName) const
{
    auto it = m_resourceTable.find(pName);
    if (it == m_resourceTable.cend())
        return nullptr;

    return it->second;
}

bool DrawingResourceTable::AddResourceEntry(std::shared_ptr<std::string> pName, std::shared_ptr<DrawingResourceDesc> pDesc)
{
    auto it = m_resourceTable.find(pName);
    if (it != m_resourceTable.cend())
        return false;

    std::shared_ptr<ResourceEntry> pEntry(new ResourceEntry(pDesc, m_factory, *this));
    m_resourceTable.emplace(pName, pEntry);
    return true;
}

bool DrawingResourceTable::RemoveResourceEntry(std::shared_ptr<std::string> pName)
{
    auto it = m_resourceTable.find(pName);
    if (it == m_resourceTable.cend())
        return false;

    m_resourceTable.erase(it);
    return true;
}

void DrawingResourceTable::ClearResourceEntries()
{
    m_resourceTable.clear();
}

bool DrawingResourceTable::BuildResources()
{
    bool result = true;
    std::for_each(m_resourceTable.begin(), m_resourceTable.end(), [&result](std::pair<std::shared_ptr<std::string>, std::shared_ptr<ResourceEntry>> elem){
        if (auto entry = elem.second)
        {
            if (!entry->CreateResource())
                result = false;
        }
    });

    return result;
}