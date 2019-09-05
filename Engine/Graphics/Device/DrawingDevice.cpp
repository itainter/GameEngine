#include "Algorithm.h"

#include "BaseRenderer.h"
#include "DrawingDevice.h"

using namespace Engine;

uint32_t DrawingDevice::s_gConstantBufferID = 0;

DrawingResource::DrawingResource(const std::shared_ptr<DrawingDevice>& pDevice) : m_pDevice(pDevice),
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

void DrawingResource::SetName(std::shared_ptr<std::string> pName)
{
    m_pName = pName;
}

const std::shared_ptr<DrawingResourceDesc>& DrawingResource::GetDesc() const
{
    return m_pDesc;
}

void DrawingResource::SetDesc(std::shared_ptr<DrawingResourceDesc> pDesc)
{
    m_pDesc = pDesc;
}

DrawingTexture::DrawingTexture(const std::shared_ptr<DrawingDevice>& pDevice) : DrawingResourceWrapper<DrawingRawTexture>(pDevice)
{
}

DrawingTexture::~DrawingTexture()
{
}

EDrawingResourceType DrawingTexture::GetType() const
{
    return eResource_Texture;
}

DrawingShader::DrawingShader(const std::shared_ptr<DrawingDevice>& pDevice) : DrawingResourceWrapper<DrawingRawShader>(pDevice)
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

DrawingTexBuffer::DrawingTexBuffer(const std::shared_ptr<DrawingDevice>& pDevice) : DrawingResourceWrapper<DrawingRawTexBuffer>(pDevice)
{
}

DrawingTexBuffer::~DrawingTexBuffer()
{
}

EDrawingResourceType DrawingTexBuffer::GetType() const
{
    return eResource_TexBuffer;
}

DrawingRWBuffer::DrawingRWBuffer(const std::shared_ptr<DrawingDevice>& pDevice) : DrawingResourceWrapper<DrawingRawRWBuffer>(pDevice)
{
}

DrawingRWBuffer::~DrawingRWBuffer()
{
}

EDrawingResourceType DrawingRWBuffer::GetType() const
{
    return eResource_RWBuffer;
}

DrawingEffect::DrawingEffect(const std::shared_ptr<DrawingDevice>& pDevice) : DrawingResourceWrapper<DrawingRawEffect>(pDevice)
{
}

DrawingEffect::~DrawingEffect()
{
}

EDrawingResourceType DrawingEffect::GetType() const
{
    return eResource_Effect;
}

DrawingBlendState::DrawingBlendState(const std::shared_ptr<DrawingDevice>& pDevice) : DrawingResourceWrapper<DrawingRawBlendState>(pDevice)
{
}

DrawingBlendState::~DrawingBlendState()
{
}

EDrawingResourceType DrawingBlendState::GetType() const
{
    return eResource_Blend_State;
}

DrawingDepthState::DrawingDepthState(const std::shared_ptr<DrawingDevice>& pDevice) : DrawingResourceWrapper<DrawingRawDepthState>(pDevice)
{
}

DrawingDepthState::~DrawingDepthState()
{
}

EDrawingResourceType DrawingDepthState::GetType() const
{
    return eResource_Depth_State;
}

DrawingRasterState::DrawingRasterState(const std::shared_ptr<DrawingDevice>& pDevice) : DrawingResourceWrapper<DrawingRawRasterState>(pDevice)
{
}

DrawingRasterState::~DrawingRasterState()
{
}

EDrawingResourceType DrawingRasterState::GetType() const
{
    return eResource_Raster_State;
}

DrawingSamplerState::DrawingSamplerState(const std::shared_ptr<DrawingDevice>& pDevice) : DrawingResourceWrapper<DrawingRawSamplerState>(pDevice)
{
}

DrawingSamplerState::~DrawingSamplerState()
{
}

EDrawingResourceType DrawingSamplerState::GetType() const
{
    return eResource_Sampler_State;
}

DrawingVertexFormat::DrawingVertexFormat(const std::shared_ptr<DrawingDevice>& pDevice) : DrawingResourceWrapper<DrawingRawVertexFormat>(pDevice)
{
}

DrawingVertexFormat::~DrawingVertexFormat()
{
}

EDrawingResourceType DrawingVertexFormat::GetType() const
{
    return eResource_Vertex_Format;
}

DrawingVertexBuffer::DrawingVertexBuffer(const std::shared_ptr<DrawingDevice>& pDevice) : DrawingResourceWrapper<DrawingRawVertexBuffer>(pDevice)
{
}

DrawingVertexBuffer::~DrawingVertexBuffer()
{
}

EDrawingResourceType DrawingVertexBuffer::GetType() const
{
    return eResource_Vertex_Buffer;
}

DrawingIndexBuffer::DrawingIndexBuffer(const std::shared_ptr<DrawingDevice>& pDevice) : DrawingResourceWrapper<DrawingRawIndexBuffer>(pDevice)
{
}

DrawingIndexBuffer::~DrawingIndexBuffer()
{
}

EDrawingResourceType DrawingIndexBuffer::GetType() const
{
    return eResource_Index_Buffer;
}

DrawingConstantBuffer::DrawingConstantBuffer(const std::shared_ptr<DrawingDevice>& pDevice) : DrawingResource(pDevice),
    m_pParams(std::make_shared<DrawingParameterSet>())
{
}

DrawingConstantBuffer::~DrawingConstantBuffer()
{
    ClearParameters();
}

void DrawingConstantBuffer::AddParameter(std::shared_ptr<DrawingParameter> pParam)
{
    m_pParams->AddUnique(pParam);
}

void DrawingConstantBuffer::RemoveParameter(std::shared_ptr<DrawingParameter> pParam)
{
    m_pParams->Remove(pParam);
}

std::shared_ptr<DrawingParameter> DrawingConstantBuffer::GetParameter(std::shared_ptr<std::string> pName)
{
    int32_t paramIndex = m_pParams->IndexOfName(pName);
    if (paramIndex == -1)
        return nullptr;

    return (*m_pParams)[paramIndex];
}

bool DrawingConstantBuffer::UpdateEffect(std::shared_ptr<DrawingEffect> pEffect)
{
    bool ret = true;
    for (int32_t i = 0; i < m_pParams->Count(); ++i)
    {
        std::shared_ptr<DrawingParameter> pParam = (*m_pParams)[i];
        if (pParam != nullptr)
        {
            if (!UpdateParameterToEffect(pParam, pEffect))
                ret = false;
        }
    }
    return ret;
}

EDrawingResourceType DrawingConstantBuffer::GetType() const
{
    return eResource_Constant_Buffer;
}

void DrawingConstantBuffer::ClearParameters()
{
    if (m_pParams != nullptr)
        m_pParams->Clear();

    m_pParams = nullptr;
}

bool DrawingConstantBuffer::UpdateParameterToEffect(std::shared_ptr<DrawingParameter> pParam, std::shared_ptr<DrawingEffect> pEffect)
{
    assert(pParam != nullptr);
    return m_pDevice->UpdateEffectParameter(pParam, pEffect);
}

DrawingTarget::DrawingTarget(const std::shared_ptr<DrawingDevice>& pDevice) : DrawingResourceWrapper<DrawingRawTarget>(pDevice)
{
}

DrawingTarget::~DrawingTarget()
{
}

EDrawingResourceType DrawingTarget::GetType() const
{
    return eResource_Target;
}

DrawingDepthBuffer::DrawingDepthBuffer(const std::shared_ptr<DrawingDevice>& pDevice) : DrawingResourceWrapper<DrawingRawTarget>(pDevice)
{
}

DrawingDepthBuffer::~DrawingDepthBuffer()
{
}

EDrawingResourceType DrawingDepthBuffer::GetType() const
{
    return eResource_DepthBuffer;
}

DrawingPrimitive::DrawingPrimitive(const std::shared_ptr<DrawingDevice>& pDevice) : DrawingResource(pDevice)
{
}

DrawingPrimitive::~DrawingPrimitive()
{
}

EDrawingPrimitiveType DrawingPrimitive::GetPrimitiveType() const
{
    return m_primitiveType;
}

void DrawingPrimitive::SetPrimitiveType(EDrawingPrimitiveType type)
{
    m_primitiveType = type;
}

uint32_t DrawingPrimitive::GetVertexCount() const
{
    return m_vertexCount;
}

void DrawingPrimitive::SetVertexCount(uint32_t count)
{
    m_vertexCount = count;
}

uint32_t DrawingPrimitive::GetIndexCount() const
{
    return m_indexCount;
}

void DrawingPrimitive::SetIndexCount(uint32_t count)
{
    m_indexCount = count;
}

uint32_t DrawingPrimitive::GetInstanceCount() const
{
    return m_instanceCount;
}

void DrawingPrimitive::SetInstanceCount(uint32_t count)
{
    m_instanceCount = count;
}

uint32_t DrawingPrimitive::GetVertexOffset() const
{
    return m_vertexOffset;
}

void DrawingPrimitive::SetVertexOffset(uint32_t offset)
{
    m_vertexOffset = offset;
}

uint32_t DrawingPrimitive::GetIndexOffset() const
{
    return m_indexOffset;
}

void DrawingPrimitive::SetIndexOffset(uint32_t offset)
{
    m_indexOffset = offset;
}

uint32_t DrawingPrimitive::GetInstanceOffset() const
{
    return m_instanceOffset;
}

void DrawingPrimitive::SetInstanceOffset(uint32_t offset)
{
    m_instanceOffset = offset;
}

EDrawingResourceType DrawingPrimitive::GetType() const
{
    return eResource_Primitive;;
}

DrawingVaringStates::DrawingVaringStates(const std::shared_ptr<DrawingDevice>& pDevice) : DrawingResource(pDevice)
{
}

DrawingVaringStates::~DrawingVaringStates()
{
}

void DrawingVaringStates::SetViewport(const Box2& vp)
{
    mViewport = vp;
}

Box2 DrawingVaringStates::GetViewport() const
{
    return mViewport;
}

EDrawingResourceType DrawingVaringStates::GetType() const
{
    return eResource_Varing_States;
}

DrawingContext::DrawingContext(const std::shared_ptr<DrawingDevice>& pDevice) : m_pNativeContext(nullptr), m_pDevice(pDevice), m_pSwapChain(nullptr), m_pDepthBuffer(nullptr)
{
}

DrawingContext::~DrawingContext()
{
    m_pNativeContext = nullptr;
    m_pDevice = nullptr;
    m_pSwapChain = nullptr;
    m_pDepthBuffer = nullptr;
}

std::shared_ptr<DrawingNativeContext> DrawingContext::GetNativeContext()
{
    return m_pNativeContext;
}

void DrawingContext::SetNativeContext(std::shared_ptr<DrawingNativeContext> context)
{
    m_pNativeContext = context;
}

void DrawingContext::SetSwapChain(const std::shared_ptr<DrawingTarget> pSwapChain)
{
    m_pSwapChain = pSwapChain;
}

std::shared_ptr<DrawingTarget> DrawingContext::GetSwapChain() const
{
    return m_pSwapChain;
}

void DrawingContext::SetDepthBuffer(const std::shared_ptr<DrawingDepthBuffer> pDepthBuffer)
{
    m_pDepthBuffer = pDepthBuffer;
}

std::shared_ptr<DrawingDepthBuffer> DrawingContext::GetDepthBuffer() const
{
    return m_pDepthBuffer;
}

void DrawingContext::SetViewport(const Box2& vp)
{
    m_viewport = vp;
}

Box2 DrawingContext::GetViewport() const
{
    return m_viewport;
}

void DrawingContext::UpdateContext(DrawingResourceTable& resTable)
{
    UpdateTargets(resTable);
    UpdateViewport(resTable);
}

void DrawingContext::UpdateTransform(DrawingResourceTable& resTable, float4x4 trans)
{
    auto pEntry = resTable.GetResourceEntry(BaseRenderer::DefaultWorldMatrix());
    assert(pEntry != nullptr);
    auto pCB = std::dynamic_pointer_cast<DrawingConstantBuffer>(pEntry->GetResource());
    if (pCB == nullptr)
        return;
    auto pParam = pCB->GetParameter(strPtr("gWorldMatrix"));
    if (pParam != nullptr)
        pParam->AsFloat4x4(trans);
}

void DrawingContext::UpdateCamera(DrawingResourceTable& resTable, float4x4 proj, float4x4 view)
{
    auto pEntry = resTable.GetResourceEntry(BaseRenderer::DefaultProjectionMatrix());
    assert(pEntry != nullptr);
    auto pCB = std::dynamic_pointer_cast<DrawingConstantBuffer>(pEntry->GetResource());
    if (pCB == nullptr)
        return;
    auto pParam = pCB->GetParameter(strPtr("gProjectionView"));
    if (pParam != nullptr)
        pParam->AsFloat4x4(proj);

    pEntry = resTable.GetResourceEntry(BaseRenderer::DefaultViewMatrix());
    assert(pEntry != nullptr);
    pCB = std::dynamic_pointer_cast<DrawingConstantBuffer>(pEntry->GetResource());
    if (pCB == nullptr)
        return;
    pParam = pCB->GetParameter(strPtr("gViewMatrix"));
    if (pParam != nullptr)
        pParam->AsFloat4x4(view);
}

void DrawingContext::UpdateTargets(DrawingResourceTable& resTable)
{
    auto pEntry = resTable.GetResourceEntry(BaseRenderer::ScreenTarget());
    assert(pEntry != nullptr);
    pEntry->SetExternalResource(m_pSwapChain);

    pEntry = resTable.GetResourceEntry(BaseRenderer::ScreenDepthBuffer());
    assert(pEntry != nullptr);
    pEntry->SetExternalResource(m_pDepthBuffer);
}

void DrawingContext::UpdateViewport(DrawingResourceTable& resTable)
{
    auto pStates = GetVaringStates(resTable);
    pStates->SetViewport(m_viewport);
}

std::shared_ptr<DrawingVaringStates> DrawingContext::GetVaringStates(DrawingResourceTable& resTable)
{
    auto pEntry = resTable.GetResourceEntry(BaseRenderer::DefaultVaringStates());
    assert(pEntry != nullptr);

    auto pStates = std::dynamic_pointer_cast<DrawingVaringStates>(pEntry->GetResource());
    assert(pStates != nullptr);

    return pStates;
}

bool DrawingDevice::CreateConstantBuffer(const DrawingConstantBufferDesc& desc, std::shared_ptr<DrawingConstantBuffer>& pRes)
{
    std::shared_ptr<DrawingRawConstantBuffer> pConstantBufferRaw = nullptr;

    auto pConstantBuffer = std::make_shared<DrawingConstantBuffer>(shared_from_this());

    for (int32_t i = 0; i < desc.mParameters.size(); ++i)
    {
        const auto& paramDesc = desc.mParameters[i];
        auto& pParam = std::make_shared<DrawingParameter>(paramDesc.mpName, paramDesc.mType);
        pConstantBuffer->AddParameter(pParam);
    }

    pConstantBuffer->SetDesc(std::shared_ptr<DrawingResourceDesc>(desc.Clone()));

    pRes = pConstantBuffer;
    return true;
}

bool DrawingDevice::CreatePrimitive(const DrawingPrimitiveDesc& desc, std::shared_ptr<DrawingPrimitive>& pRes)
{
    auto pPrimitive = std::make_shared<DrawingPrimitive>(shared_from_this());
    pPrimitive->SetPrimitiveType(desc.mPrimitive);
    pPrimitive->SetDesc(std::shared_ptr<DrawingResourceDesc>(desc.Clone()));

    pRes = pPrimitive;
    return true;
}

bool DrawingDevice::CreateVaringStates(const DrawingVaringStatesDesc& desc, std::shared_ptr<DrawingVaringStates>& pRes)
{
    auto pVaringStates = std::make_shared<DrawingVaringStates>(shared_from_this());
    pVaringStates->SetDesc(std::shared_ptr<DrawingResourceDesc>(desc.Clone()));

    pRes = pVaringStates;
    return true;
}

DrawingDevice::ConstBufferProp* DrawingDevice::FindConstantBuffer(const DrawingDevice::ConstBufferProp& prop)
{
    ConstBufferProp* pCBProp = nullptr;

    std::for_each(m_constantBufferPool.begin(), m_constantBufferPool.end(), [this, &prop, &pCBProp](ConstBufferPropTable::value_type& aElem) {
        auto& devProp = aElem.second;
        if (devProp.IsEqual(prop))
            pCBProp = &devProp;
    });
    return pCBProp;
}

void DrawingDevice::AddConstantBuffer(const ConstBufferProp& prop)
{
    auto pName = strPtr(std::to_string(s_gConstantBufferID));
    s_gConstantBufferID++;

    m_constantBufferPool.emplace(pName, prop);
}

void DrawingDevice::ClearConstantBuffers()
{
    m_constantBufferPool.clear();
}