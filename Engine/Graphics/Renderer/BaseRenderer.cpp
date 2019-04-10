#include "BaseRenderer.h"
#include "DrawingResourceDesc.h"

using namespace Engine;

uint32_t BaseRenderer::m_sVertexID[MAX_VERTEX_COUNT] = { 0 };
uint32_t BaseRenderer::m_sInstanceID[MAX_INSTANCE_COUNT] = { 0 };

const uint32_t DrawingLinkedEffectDesc::VERTEX_SHADER_ID;
const uint32_t DrawingLinkedEffectDesc::PIXEL_SHADER_ID;

BaseRenderer::BaseRenderer()
{
    InitVertexID();
    InitInstanceID();
}

BaseRenderer::BaseRenderer(const std::shared_ptr<DrawingDevice>& pDevice, const std::shared_ptr<DrawingContext>& pContext) :
    m_pDevice(pDevice), m_pDeviceContext(pContext)
{
    InitVertexID();
    InitInstanceID();
}

void BaseRenderer::MapResources(DrawingResourceTable& resTable)
{
    m_stageTable.FetchResources(resTable);
}

void BaseRenderer::DefineDefaultResources(DrawingResourceTable& resTable)
{
    DefineDefaultVertexFormat(resTable);
    DefineStaticVertexBuffer(PerVertexVertexBuffer(), 4, MAX_VERTEX_COUNT, &m_sVertexID, 4 * MAX_VERTEX_COUNT, resTable);
    DefineStaticVertexBuffer(PerInstanceVertexBuffer(), 4, MAX_INSTANCE_COUNT, &m_sInstanceID, 4 * MAX_INSTANCE_COUNT, resTable);

    DefineExternalTarget(ScreenTarget(), resTable);
    DefineExternalDepthBuffer(ScreenDepthBuffer(), resTable);

    DefineDefaultDepthState(resTable);
    
    DefineDefaultBlendState(resTable);
    DefineDefaultRasterState(resTable);

    DefinePrimitive(DefaultPrimitive(), resTable);
    DefineVaringStates(resTable);
}


void BaseRenderer::DefineGeneralEffect(std::shared_ptr<std::string> pEffectName, std::shared_ptr<std::string> pSourceName, std::shared_ptr<std::string> pTechName, DrawingResourceTable& resTable)
{
    auto pDesc = std::make_shared<DrawingGeneralEffectDesc>();

    pDesc->mProgramType = eProgram_Binary;
    pDesc->mpName = pEffectName;
    pDesc->mpSourceName = pSourceName;
    pDesc->mpTechName = pTechName;

    resTable.AddResourceEntry(pEffectName, pDesc);
}

void BaseRenderer::DefineLinkedEffect(std::shared_ptr<std::string> pEffectName, std::shared_ptr<std::string> pVSName, std::shared_ptr<std::string> pPSName, DrawingResourceTable& resTable)
{
    auto pDesc = std::make_shared<DrawingLinkedEffectDesc>();

    pDesc->mProgramType = eProgram_Shader;
    pDesc->mpName = pEffectName;

    pDesc->AddResourceDescName(DrawingLinkedEffectDesc::VERTEX_SHADER_ID, pVSName);
    pDesc->AddResourceDescName(DrawingLinkedEffectDesc::PIXEL_SHADER_ID, pPSName);

    resTable.AddResourceEntry(pEffectName, pDesc);
}

void BaseRenderer::DefinePipelineState(std::shared_ptr<std::string> pVertexFormatName,
                                       std::shared_ptr<std::string> pPipelineStateName, 
                                       std::shared_ptr<std::string> pPrimitiveName,
                                       std::shared_ptr<std::string> pVSName,
                                       std::shared_ptr<std::string> pPSName,
                                       std::shared_ptr<std::string> pBlendStateName,
                                       std::shared_ptr<std::string> pRasterStateName,
                                       std::shared_ptr<std::string> pDepthStencilStateName,
                                       std::shared_ptr<std::string> pRenderTargetName,
                                       DrawingResourceTable& resTable)
{
    auto pDesc = std::make_shared<DrawingPipelineStateDesc>();

    pDesc->AttachSubobject(DrawingPipelineStateDesc::ePipelineStateSubobjectType_InputLayout, pVertexFormatName);
    pDesc->AttachSubobject(DrawingPipelineStateDesc::ePipelineStateSubobjectType_PrimitiveTopology, pPrimitiveName);
    pDesc->AttachSubobject(DrawingPipelineStateDesc::ePipelineStateSubobjectType_Vs, pVSName);
    pDesc->AttachSubobject(DrawingPipelineStateDesc::ePipelineStateSubobjectType_Ps, pPSName);
    pDesc->AttachSubobject(DrawingPipelineStateDesc::ePipelineStateSubobjectType_BlendState, pBlendStateName);
    pDesc->AttachSubobject(DrawingPipelineStateDesc::ePipelineStateSubobjectType_RasterState, pRasterStateName);
    pDesc->AttachSubobject(DrawingPipelineStateDesc::ePipelineStateSubobjectType_DepthStencilState, pDepthStencilStateName);
    pDesc->AttachSubobject(DrawingPipelineStateDesc::ePipelineStateSubobjectType_RenderTarget, pRenderTargetName);

    resTable.AddResourceEntry(pPipelineStateName, pDesc);
}

void BaseRenderer::DefineVertexShaderFromBlob(std::shared_ptr<std::string> pShaderName, std::shared_ptr<std::string> pSourceName, DrawingResourceTable& resTable)
{
    DoDefineShaderFromBlob<DrawingVertexShaderDesc>(pShaderName, pSourceName, resTable);
}

void BaseRenderer::DefinePixelShaderFromBlob(std::shared_ptr<std::string> pShaderName, std::shared_ptr<std::string> pSourceName, DrawingResourceTable& resTable)
{
    DoDefineShaderFromBlob<DrawingPixelShaderDesc>(pShaderName, pSourceName, resTable);
}

void BaseRenderer::DefineVertexShader(std::shared_ptr<std::string> pShaderName, std::shared_ptr<std::string> pFileName, std::shared_ptr<std::string> pEntryName, DrawingResourceTable& resTable)
{
    DoDefineShader<DrawingVertexShaderDesc>(pShaderName, pFileName, pEntryName, resTable);
}

void BaseRenderer::DefinePixelShader(std::shared_ptr<std::string> pShaderName, std::shared_ptr<std::string> pFileName, std::shared_ptr<std::string> pEntryName, DrawingResourceTable& resTable)
{
    DoDefineShader<DrawingPixelShaderDesc>(pShaderName, pFileName, pEntryName, resTable);
}

void BaseRenderer::DefineDefaultVertexFormat(DrawingResourceTable& resTable)
{
    auto pDesc = std::make_shared<DrawingVertexFormatDesc>();

    DrawingVertexFormatDesc::VertexInputElement inputElem;

    inputElem.mFormat = eFormat_R32_FLOAT;
    inputElem.mpName = strPtr("TEXCOORD");
    inputElem.mIndex = 0;
    inputElem.mSlot = 0;
    inputElem.mOffset = 0;
    inputElem.mInstanceStepRate = 0;
    pDesc->m_inputElements.emplace_back(inputElem);

    inputElem.mFormat = eFormat_R32_FLOAT;
    inputElem.mpName = strPtr("TEXCOORD");
    inputElem.mIndex = 1;
    inputElem.mSlot = 1;
    inputElem.mOffset = 0;
    inputElem.mInstanceStepRate = 1;
    pDesc->m_inputElements.emplace_back(inputElem);

    resTable.AddResourceEntry(DefaultVertexFormat(), pDesc);
}

void BaseRenderer::DefineStaticVertexBuffer(std::shared_ptr<std::string> pName, uint32_t stride, uint32_t count, const void* data, uint32_t size, DrawingResourceTable& resTable)
{
    auto pDesc = std::make_shared<DrawingVertexBufferDesc>();

    pDesc->mSizeInBytes = stride * count;
    pDesc->mStrideInBytes = stride;
    pDesc->mUsage = eUsage_Default;
    pDesc->mAccess = eAccess_No_Access;
    pDesc->mFlags = 0;

    if (resTable.AddResourceEntry(pName, pDesc))
    {
        auto pEntry = resTable.GetResourceEntry(pName);
        if (pEntry != nullptr)
        {
            pEntry->SetInitData(data, size);
            pEntry->SetInitDataSlices(1);
        }
    }
}

void BaseRenderer::DefineStaticIndexBuffer(std::shared_ptr<std::string> pName, uint32_t count, const void* data, uint32_t size, DrawingResourceTable& resTable)
{
    auto pDesc = std::make_shared<DrawingIndexBufferDesc>();

    pDesc->mSizeInBytes = 4 * count;
    pDesc->mStrideInBytes = 4;
    pDesc->mUsage = eUsage_Default;
    pDesc->mAccess = eAccess_No_Access;
    pDesc->mFlags = 0;

    if (resTable.AddResourceEntry(pName, pDesc))
    {
        auto pEntry = resTable.GetResourceEntry(pName);
        if (pEntry != nullptr)
        {
            pEntry->SetInitData(data, size);
            pEntry->SetInitDataSlices(1);
        }
    }

}

void BaseRenderer::DefineDefaultDepthState(DrawingResourceTable& resTable)
{
    auto pDesc = std::make_shared<DrawingDepthStateDesc>();

    pDesc->mDepthState.mDepthEnable = true;
    pDesc->mDepthState.mDepthWriteEnable = false;
    pDesc->mDepthState.mDepthFunc = eComparison_Always;

    pDesc->mStencilState.mStencilEnable = false;
    pDesc->mStencilState.mStencilReadMask = 0;
    pDesc->mStencilState.mStencilWriteMask = 0;

    pDesc->mStencilState.mFrontFace.mStencilPassOp = eStencilOp_Keep;
    pDesc->mStencilState.mFrontFace.mStencilFailOp = eStencilOp_Keep;
    pDesc->mStencilState.mFrontFace.mStencilDepthFailOp = eStencilOp_Keep;
    pDesc->mStencilState.mFrontFace.mStencilFunc = eComparison_Always;

    pDesc->mStencilState.mBackFace.mStencilPassOp = eStencilOp_Keep;
    pDesc->mStencilState.mBackFace.mStencilFailOp = eStencilOp_Keep;
    pDesc->mStencilState.mBackFace.mStencilDepthFailOp = eStencilOp_Keep;
    pDesc->mStencilState.mBackFace.mStencilFunc = eComparison_Always;

    resTable.AddResourceEntry(DefaultDepthState(), pDesc);
}

void BaseRenderer::DefineDefaultBlendState(DrawingResourceTable& resTable)
{
    auto pDesc = std::make_shared<DrawingBlendStateDesc>();

    pDesc->mAlphaToCoverageEnable = false;
    pDesc->mIndependentBlendEnable = false;

    for (uint32_t i = 0; i < MAX_TARGETS; ++i)
    {
        pDesc->mTargets[i].mBlendEnable = false;

        pDesc->mTargets[i].mColorBlend.mBlendSrc = eBlend_One;
        pDesc->mTargets[i].mColorBlend.mBlendDst = eBlend_Zero;
        pDesc->mTargets[i].mColorBlend.mBlendOp = eBlendOp_Add;

        pDesc->mTargets[i].mAlphaBlend.mBlendSrc = eBlend_One;
        pDesc->mTargets[i].mAlphaBlend.mBlendDst = eBlend_Zero;
        pDesc->mTargets[i].mAlphaBlend.mBlendOp = eBlendOp_Add;

        pDesc->mTargets[i].mRenderTargetWriteMask = DrawingBlendStateDesc::BlendTarget::WriteMast_All;
    }

    resTable.AddResourceEntry(DefaultBlendState(), pDesc);
}

void BaseRenderer::DefineDefaultRasterState(DrawingResourceTable& resTable)
{
    auto pDesc = std::make_shared<DrawingRasterStateDesc>();

    pDesc->mAntialiasedLineEnable = true;
    pDesc->mDepthClipEnable = true;

    pDesc->mDepthBiasClamp = 0.0f;
    pDesc->mSlopeScaledDepthBias = 0.0f;
    pDesc->mDepthBias = 0;

    pDesc->mCullMode = eCullMode_None;
    pDesc->mFillMode = eFillMode_Solid;

    pDesc->mFrontCounterClockwise = false;
    pDesc->mMultisampleEnable = false;
    pDesc->mScissorEnable = false;

    resTable.AddResourceEntry(DefaultRasterState(), pDesc);
}

void BaseRenderer::DefineExternalTarget(std::shared_ptr<std::string> pName, DrawingResourceTable& resTable)
{
    auto pDesc = std::make_shared<DrawingTargetDesc>();

    pDesc->SetIsExternalResource(true);

    resTable.AddResourceEntry(pName, pDesc);
}

void BaseRenderer::DefineExternalDepthBuffer(std::shared_ptr<std::string> pName, DrawingResourceTable& resTable)
{
    auto pDesc = std::make_shared<DrawingDepthBufferDesc>();

    pDesc->SetIsExternalResource(true);

    resTable.AddResourceEntry(pName, pDesc);
}


void BaseRenderer::DefineVaringStates(DrawingResourceTable& resTable)
{
    auto pDesc = std::make_shared<DrawingVaringStatesDesc>();

    resTable.AddResourceEntry(DefaultVaringStates(), pDesc);
}

void BaseRenderer::DefinePrimitive(std::shared_ptr<std::string> pName, DrawingResourceTable& resTable)
{
    auto pDesc = std::make_shared<DrawingPrimitiveDesc>();

    pDesc->mPrimitive = ePrimitive_TriangleStrip;

    resTable.AddResourceEntry(pName, pDesc);
}

void BaseRenderer::BindResource(DrawingPass& pass, std::shared_ptr<std::string> slotName, std::shared_ptr<std::string> resName)
{
    pass.BindResource(slotName, resName);
}

void BaseRenderer::BindEffect(DrawingPass& pass, std::shared_ptr<std::string> pName)
{
    pass.BindResource(DrawingPass::EffectSlotName(), pName);
}

void BindPipeline(DrawingPass& pass, std::shared_ptr<std::string> pName)
{
    pass.BindResource(DrawingPass::PipelineStateSlotName(), pName);
}

void BaseRenderer::BindVertexFormat(DrawingPass& pass, std::shared_ptr<std::string> pName)
{
    pass.BindResource(DrawingPass::VertexFormatSlotName(), pName);
}

void BaseRenderer::BindVertexBuffer(DrawingPass& pass, uint32_t index, std::shared_ptr<std::string> pName)
{
    pass.BindResource(DrawingPass::VertexBufferSlotName(index), pName);
}

void BaseRenderer::BindIndexBuffer(DrawingPass& pass, std::shared_ptr<std::string> pName)
{
    pass.BindResource(DrawingPass::IndexBufferSlotName(), pName);
}

void BaseRenderer::BindTarget(DrawingPass& pass, uint32_t index, std::shared_ptr<std::string> pName)
{
    pass.BindResource(DrawingPass::TargetSlotName(index), pName);
}

void BaseRenderer::BindDepthBuffer(DrawingPass& pass, std::shared_ptr<std::string> pName)
{
    pass.BindResource(DrawingPass::DepthBufferSlotName(), pName);
}

void BaseRenderer::BindDepthState(DrawingPass& pass, std::shared_ptr<std::string> pName)
{
    pass.BindResource(DrawingPass::DepthStateSlotName(), pName);
}

void BaseRenderer::BindBlendState(DrawingPass& pass, std::shared_ptr<std::string> pName)
{
    pass.BindResource(DrawingPass::BlendStateSlotName(), pName);
}

void BaseRenderer::BindRasterState(DrawingPass& pass, std::shared_ptr<std::string> pName)
{
    pass.BindResource(DrawingPass::RasterStateSlotName(), pName);
}

void BaseRenderer::BindPrimitive(DrawingPass& pass, std::shared_ptr<std::string> pName)
{
    pass.BindResource(DrawingPass::PrimitiveSlotName(), pName);
}

void BaseRenderer::BindVaringStates(DrawingPass& pass, std::shared_ptr<std::string> pName)
{
    pass.BindResource(DrawingPass::VaringStatesSlotName(), pName);
}

void BaseRenderer::BindPipelineState(DrawingPass& pass, std::shared_ptr<std::string> pName)
{
    pass.BindResource(DrawingPass::PipelineStateSlotName(), pName);
}

void BaseRenderer::BindInputs(DrawingPass& pass)
{
    BindVertexFormat(pass, DefaultVertexFormat());
    BindVertexBuffer(pass, 0, PerVertexVertexBuffer());
    BindVertexBuffer(pass, 1, PerInstanceVertexBuffer());
}

void BaseRenderer::BindStates(DrawingPass& pass)
{
    BindDepthState(pass, DefaultDepthState());
    BindBlendState(pass, DefaultBlendState());
    BindRasterState(pass, DefaultRasterState());
}

void BaseRenderer::BindOutput(DrawingPass& pass)
{
    BindTarget(pass, 0, ScreenTarget());
    BindDepthBuffer(pass, ScreenDepthBuffer());
}

std::shared_ptr<DrawingStage> BaseRenderer::CreateStage(std::shared_ptr<std::string> pName)
{
    return std::make_shared<DrawingStage>(pName);
}

std::shared_ptr<DrawingPass> BaseRenderer::CreatePass(std::shared_ptr<std::string> pName)
{
    return std::make_shared<DrawingPass>(pName, m_pDevice);
}

void BaseRenderer::FlushStage(std::shared_ptr<std::string> pStageName)
{
    auto stage = m_stageTable.GetDrawingStage(pStageName);
    if (stage != nullptr)
        stage->Flush(*m_pDeviceContext);
}

void BaseRenderer::InitVertexID()
{
    for (uint32_t i = 0; i < MAX_VERTEX_COUNT; ++i)
        m_sVertexID[i] = i;
}

void BaseRenderer::InitInstanceID()
{
    for (uint32_t i = 0; i < MAX_INSTANCE_COUNT; ++i)
        m_sInstanceID[i] = i;
}