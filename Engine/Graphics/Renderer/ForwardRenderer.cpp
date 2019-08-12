#include "ForwardRenderer.h"
#include "DrawingDevice.h"

using namespace Engine;

ForwardRenderer::ForwardRenderer() : BaseRenderer()
{
}

void ForwardRenderer::DefineResources(DrawingResourceTable& resTable)
{
    DefineDefaultResources(resTable);
    DefineShaderResource(resTable);
    DefinePipelineStateResource(resTable);
}

void ForwardRenderer::SetupBuffers(DrawingResourceTable& resTable)
{
}

void ForwardRenderer::BeginDrawPass()
{
    m_pTransientPositionBuffer->Open();
    m_pTransientNormalBuffer->Open();
    m_pTransientIndexBuffer->Open();
}

void ForwardRenderer::EndDrawPass()
{
    m_pTransientPositionBuffer->Close();
    m_pTransientNormalBuffer->Close();
    m_pTransientIndexBuffer->Close();
}

void ForwardRenderer::FlushData()
{
    m_pTransientPositionBuffer->FlushData();
    m_pTransientNormalBuffer->FlushData();
    m_pTransientIndexBuffer->FlushData();
}

void ForwardRenderer::ResetData()
{
    m_pTransientPositionBuffer->ResetData();
    m_pTransientNormalBuffer->ResetData();
    m_pTransientIndexBuffer->ResetData();
}

void ForwardRenderer::UpdatePrimitive(DrawingResourceTable& resTable)
{
    auto pEntry = resTable.GetResourceEntry(DefaultPrimitive());
    if (pEntry == nullptr)
        return;

    auto pPrimitive = std::dynamic_pointer_cast<DrawingPrimitive>(pEntry->GetResource());
    if (pPrimitive == nullptr)
        return;

    pPrimitive->SetPrimitiveType(ePrimitive_TriangleList);
    pPrimitive->SetVertexCount(m_pTransientPositionBuffer->GetFlushOffset());
    pPrimitive->SetIndexCount(m_pTransientIndexBuffer->GetFlushOffset());
    pPrimitive->SetInstanceCount(0);

    pPrimitive->SetVertexOffset(0);
    pPrimitive->SetIndexOffset(0);
    pPrimitive->SetInstanceOffset(0);
}

void ForwardRenderer::BuildPass()
{
    auto& pMainPass = CreateForwardBasePass(BasicPrimitiveDefaultPass(), BasicPrimitiveEffect());
    m_passTable[BasicPrimitiveDefaultPass()] = pMainPass;

    auto& pCopyPass = CreateCopyPass(CopyPass());
    m_passTable[CopyPass()] = pCopyPass;
}

void ForwardRenderer::DefineShaderResource(DrawingResourceTable& resTable)
{
    DefineVertexShader(BasicPrimitiveVertexShader(), strPtr("Asset\\Shader\\HLSL\\basic.vs"), strPtr("BasicPrimitive_VS"), resTable);
    DefinePixelShader(BasicPrimitivePixelShader(), strPtr("Asset\\Shader\\HLSL\\basic.ps"), strPtr("BasicPrimitive_PS"), resTable);

    DefineLinkedEffect(BasicPrimitiveEffect(), BasicPrimitiveVertexShader(), BasicPrimitivePixelShader(), resTable);
}

void ForwardRenderer::DefinePipelineStateResource(DrawingResourceTable& resTable)
{
    DefinePipelineState(DefaultVertexFormat(),
                        BasicPrimitivePipelineState(),
                        DefaultPrimitive(),
                        BasicPrimitiveEffect(),
                        DefaultBlendState(),
                        DefaultRasterState(),
                        DefaultDepthState(),
                        DefaultTarget(),
                        resTable);
}

std::shared_ptr<DrawingPass> ForwardRenderer::CreateForwardBasePass(std::shared_ptr<std::string> pPassName, std::shared_ptr<std::string> pEffectName)
{
    auto pPass = CreatePass(pPassName);

    BindEffect(*pPass, pEffectName);
    BindPipelineState(*pPass, BasicPrimitivePipelineState());
    BindDynamicInputs(*pPass);
    BindStates(*pPass);
    BindOutput(*pPass);
    BindPrimitive(*pPass, DefaultPrimitive());
    BindVaringStates(*pPass, DefaultVaringStates());

    BindConstants(*pPass);

    return pPass;
}

std::shared_ptr<DrawingPass> ForwardRenderer::CreateCopyPass(std::shared_ptr<std::string> pPassName)
{
    auto pPass = CreatePass(pPassName);
    return pPass;
}