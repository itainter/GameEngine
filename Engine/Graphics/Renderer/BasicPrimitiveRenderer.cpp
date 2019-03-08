#include "BasicPrimitiveRenderer.h"
#include "DrawingDevice.h"

using namespace Engine;

BasicPrimitiveRenderer::BasicPrimitiveRenderer() : BaseRenderer()
{
}

BasicPrimitiveRenderer::BasicPrimitiveRenderer(const std::shared_ptr<DrawingDevice>& pDevice, const std::shared_ptr<DrawingContext>& pContext) : BaseRenderer(pDevice, pContext)
{
}

void BasicPrimitiveRenderer::Initialize()
{
}

void BasicPrimitiveRenderer::Shutdown()
{
}

void BasicPrimitiveRenderer::Tick()
{
}

void BasicPrimitiveRenderer::DefineResources(DrawingResourceTable& resTable)
{
    DefineDefaultResources(resTable);
    DefineShaderResource(resTable);
}

void BasicPrimitiveRenderer::SetupStages()
{
    auto pStage = CreateStage(BasicPrimitiveStage());
    pStage->AppendDrawingPass(CreateDefaultPass(BasicPrimitiveDefaultPass(), BasicPrimitiveEffect(), BasicPrimitiveIndexBuffer()));

    m_stageTable.AddDrawingStage(pStage->GetName(), pStage);
}

void BasicPrimitiveRenderer::SetupBuffers(DrawingResourceTable& resTable)
{
}

void BasicPrimitiveRenderer::Cleanup()
{
}

void BasicPrimitiveRenderer::BeginFrame()
{
}

void BasicPrimitiveRenderer::EndFrame()
{
}

void BasicPrimitiveRenderer::UpdatePrimitive(DrawingResourceTable& resTable)
{
    auto pEntry = resTable.GetResourceEntry(DefaultPrimitive());
    if (pEntry == nullptr)
        return;

    auto pPrimitive = std::dynamic_pointer_cast<DrawingPrimitive>(pEntry->GetResource());
    if (pPrimitive == nullptr)
        return;

    pPrimitive->SetPrimitiveType(ePrimitive_TriangleStrip);
    pPrimitive->SetVertexCount(3);
    pPrimitive->SetIndexCount(0);
    pPrimitive->SetInstanceCount(64 * 64);

    pPrimitive->SetVertexOffset(0);
    pPrimitive->SetIndexOffset(0);
    pPrimitive->SetInstanceOffset(0);
}

void BasicPrimitiveRenderer::Draw(DrawingResourceTable& resTable)
{
    UpdatePrimitive(resTable);
    FlushStage(BasicPrimitiveStage());
}

void BasicPrimitiveRenderer::DefineShaderResource(DrawingResourceTable& resTable)
{
    DefineVertexShader(BasicPrimitiveVertexShader(), strPtr("Asset\\Shader\\HLSL\\basic.vs"), strPtr("BasicPrimitive_VS"), resTable);
    DefinePixelShader(BasicPrimitivePixelShader(), strPtr("Asset\\Shader\\HLSL\\basic.ps"), strPtr("BasicPrimitive_PS"), resTable);

    DefineLinkedEffect(BasicPrimitiveEffect(), BasicPrimitiveVertexShader(), BasicPrimitivePixelShader(), resTable);
}

std::shared_ptr<DrawingPass> BasicPrimitiveRenderer::CreateDefaultPass(
    std::shared_ptr<std::string> pPassName,
    std::shared_ptr<std::string> pEffectName,
    std::shared_ptr<std::string> pIndexName)
{
    auto pPass = CreatePass(pPassName);

    BindEffect(*pPass, pEffectName);
    BindInputs(*pPass);
    BindStates(*pPass);
    BindOutput(*pPass);
    BindPrimitive(*pPass, DefaultPrimitive());
    BindVaringStates(*pPass, DefaultVaringStates());
    BindCommandList(*pPass, DefaultCommandList());

    return pPass;
}