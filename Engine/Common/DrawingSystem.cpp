#include <assert.h>
#include <fstream>

#include "Global.h"
#include "CameraComponent.h"
#include "TransformComponent.h"
#include "MeshFilterComponent.h"
#include "MeshRendererComponent.h"
#include "FrameGraphComponent.h"

#include "DrawingSystem.h"
#include "D3D11/DrawingDevice_D3D11.h"
#include "D3D12/DrawingDevice_D3D12.h"

using namespace Engine;

DrawingSystem::DrawingSystem() : m_window(nullptr),
    m_deviceSize(0),
    m_deviceType(gpGlobal->GetConfiguration<GraphicsConfiguration>().GetDeviceType()),
    m_pDevice(nullptr),
    m_pContext(nullptr),
    m_pEffectPool(nullptr),
    m_pResourceFactory(nullptr),
    m_pResourceTable(nullptr)
{
}

DrawingSystem::~DrawingSystem()
{
}

void DrawingSystem::Initialize()
{
    if (!EstablishConfiguration())
        return;
}

void DrawingSystem::Shutdown()
{
}

void DrawingSystem::Tick(float elapsedTime)
{
    for (auto& pCamera : m_pCameraList)
    {
        auto pFrameGraphComponent = pCamera->GetComponent<FrameGraphComponent>();
        if (pFrameGraphComponent == nullptr)
            continue;

        auto pFrameGraph = pFrameGraphComponent->GetFrameGraph();
        if (pFrameGraph == nullptr)
            continue;

        pFrameGraph->EnqueuePasses();
    }

    m_pDevice->Present(m_pContext->GetSwapChain(), 0);
}

void DrawingSystem::FlushEntity(std::shared_ptr<IEntity> pEntity)
{
    if (pEntity->HasComponent<CameraComponent>() && pEntity->HasComponent<TransformComponent>())
        m_pCameraList.emplace_back(pEntity);

    if (pEntity->HasComponent<MeshFilterComponent>() && pEntity->HasComponent<TransformComponent>())
        m_pMeshList.emplace_back(pEntity);
}

EConfigurationDeviceType DrawingSystem::GetDeviceType() const
{
    return m_deviceType;
}

void DrawingSystem::SetDeviceType(EConfigurationDeviceType type)
{
    m_deviceType = type;
}

bool DrawingSystem::EstablishConfiguration()
{
    if (!PreConfiguration())
        return false;

    if (!CreateDevice())
        return false;

    if (!CreatePreResource())
        return false;

    if (!RegisterRenderer())
        return false;

    if (!PostConfiguration())
        return false;

    return true;
}

bool DrawingSystem::PreConfiguration()
{
    if (gpGlobal == nullptr)
        return false;

    m_deviceSize.x = gpGlobal->GetConfiguration<AppConfiguration>().GetWidth();
    m_deviceSize.y = gpGlobal->GetConfiguration<AppConfiguration>().GetHeight();
    m_window = gpGlobal->GetConfiguration<AppConfiguration>().GetAppHandle();

    return true;
}

bool DrawingSystem::CreateDevice()
{
    switch(m_deviceType)
    {
        case eDevice_D3D11:
            m_pDevice = CreateNativeDevice<eDevice_D3D11>();
            break;
        case eDevice_D3D12:
            m_pDevice = CreateNativeDevice<eDevice_D3D12>();
            break;
        default:
            assert(false);
    }
    m_pDevice->Initialize();
    m_pContext = std::make_shared<DrawingContext>(m_pDevice);
    return true;
}

bool DrawingSystem::CreatePreResource()
{
    m_pEffectPool = std::make_shared<DrawingEffectPool>(m_pDevice);
    m_pResourceFactory = std::make_shared<DrawingResourceFactory>(m_pDevice);
    m_pResourceTable = std::make_shared<DrawingResourceTable>(*m_pResourceFactory);

    m_pResourceFactory->SetEffectPool(m_pEffectPool);

    return true;
}

bool DrawingSystem::RegisterRenderer()
{
    for (uint32_t type = eRenderer_Start; type != eRenderer_End; type++)
    {
        auto& pRenderer = gpGlobal->GetRenderer((ERendererType)type);
        if (pRenderer != nullptr)
        {
            pRenderer->AttachDevice(m_pDevice, m_pContext);
            pRenderer->BuildPass();
            pRenderer->DefineResources(*m_pResourceTable);
        }
    }
    return true;
}

std::shared_ptr<DrawingTarget> DrawingSystem::CreateSwapChain()
{
    assert(m_window != nullptr);

    DrawingTargetDesc desc;
    desc.mHwnd = m_window;
    desc.mWidth = m_deviceSize.x;
    desc.mHeight = m_deviceSize.y;
    desc.mFormat = eFormat_R8G8B8A8_UNORM;
    desc.mMultiSampleCount = gpGlobal->GetConfiguration<GraphicsConfiguration>().GetMSAA();
    desc.mMultiSampleQuality = gpGlobal->GetConfiguration<GraphicsConfiguration>().GetMSAA() == eMSAA_Disable ? 0 : 1;

    std::shared_ptr<DrawingTarget> pSwapChain;

    if (!m_pDevice->CreateTarget(desc, pSwapChain))
        return nullptr;

    return pSwapChain;
}

std::shared_ptr<DrawingDepthBuffer> DrawingSystem::CreateDepthBuffer()
{
    DrawingDepthBufferDesc desc;
    desc.mWidth = m_deviceSize.x;
    desc.mHeight = m_deviceSize.y;
    desc.mFormat = eFormat_D24S8;
    desc.mMultiSampleCount = gpGlobal->GetConfiguration<GraphicsConfiguration>().GetMSAA();
    desc.mMultiSampleQuality = gpGlobal->GetConfiguration<GraphicsConfiguration>().GetMSAA() == eMSAA_Disable ? 0 : 1;

    std::shared_ptr<DrawingDepthBuffer> pDepthBuffer;

    if (!m_pDevice->CreateDepthBuffer(desc, pDepthBuffer))
        return nullptr;

    return pDepthBuffer;
}

bool DrawingSystem::PostConfiguration()
{
    auto pSwapChain = CreateSwapChain();
    auto pDepthBuffer = CreateDepthBuffer();

    m_pContext->SetSwapChain(pSwapChain);
    m_pContext->SetDepthBuffer(pDepthBuffer);
    m_pContext->SetViewport(Box2(float2(0, 0), float2((float)gpGlobal->GetConfiguration<AppConfiguration>().GetWidth(), (float)gpGlobal->GetConfiguration<AppConfiguration>().GetHeight())));

    m_pContext->UpdateTargets(*m_pResourceTable);

    if(!m_pResourceTable->BuildResources())
        return false;

    m_pDevice->Flush();

    BuildFrameGraph();

    return true;
}

void DrawingSystem::BuildFrameGraph()
{
    for (auto& pCamera : m_pCameraList)
    {
        std::shared_ptr<FrameGraph> pFrameGraph = std::make_shared<FrameGraph>();

        FrameGraphComponent frameGraphComponent;
        frameGraphComponent.SetFrameGraph(pFrameGraph);
        pCamera->AttachComponent<FrameGraphComponent>(frameGraphComponent);

        auto pCameraComponent = pCamera->GetComponent<CameraComponent>();

        if (pCameraComponent->GetRendererType() == eRenderer_Forward)
            BuildForwardFrameGraph(pFrameGraph, pCamera);
    }
}

bool DrawingSystem::BuildForwardFrameGraph(std::shared_ptr<FrameGraph> pFrameGraph, std::shared_ptr<IEntity> pCamera)
{
    auto& pRenderer = gpGlobal->GetRenderer(eRenderer_Forward);
    if (pRenderer == nullptr)
        return false;

    pRenderer->CreateDataResources(*m_pResourceTable);

    auto pCameraComponent = pCamera->GetComponent<CameraComponent>();
    auto pTransformComponent = pCamera->GetComponent<TransformComponent>();
    assert(pCameraComponent != nullptr && pTransformComponent != nullptr);

    auto pMainPass = pRenderer->GetPass(ForwardRenderer::BasicPrimitiveDefaultPass());
    assert(pMainPass != nullptr);
    auto& mainPassNode = pFrameGraph->AddPass(pMainPass, GraphicsBit);

    mainPassNode.SetInitializeFunc([&](void) -> bool {
        return true;
    });

    mainPassNode.SetClearColorFunc(0, [&, pCameraComponent](float4& color) -> void {
        color = pCameraComponent->GetBackground();
    });

    mainPassNode.SetClearDepthStencilFunc([&](float& depth, uint8_t& stencil, uint32_t& flag) -> void {
        depth = 1.0f;
        stencil = 0;
        flag = eClear_Depth;
    });

    mainPassNode.SetExecuteFunc([&, pCameraComponent, pTransformComponent, pRenderer, pMainPass](void) -> void {
        auto proj = UpdateProjectionMatrix(pCameraComponent);
        auto view = UpdateViewMatrix(pTransformComponent);

        m_pContext->UpdateContext(*m_pResourceTable);
        m_pContext->UpdateCamera(*m_pResourceTable, proj, view);

        m_pDevice->ClearTarget(m_pContext->GetSwapChain(), pCameraComponent->GetBackground());
        m_pDevice->ClearDepthBuffer(m_pContext->GetDepthBuffer(), 1.0f, 0, eClear_Depth);

        RenderQueueItemListType items;
        GetVisableRenderable(items);

        pRenderer->Begin();
        pRenderer->AddRenderables(items);
        pRenderer->Flush(*m_pResourceTable, pMainPass);
    });

    auto pCopyPass = pRenderer->GetPass(ForwardRenderer::CopyPass());
    assert(pCopyPass != nullptr);
    auto& copyPassNode = pFrameGraph->AddPass(pCopyPass, GraphicsBit);

    copyPassNode.SetInitializeFunc([&](void) -> bool {
        return true;
    });

    copyPassNode.SetExecuteFunc([&, pCopyPass](void) -> void {
        auto pEntry = m_pResourceTable->GetResourceEntry(ForwardRenderer::DefaultTarget());
        if (pEntry == nullptr)
            return;

        auto pResource = pEntry->GetResource();
        if (pResource == nullptr)
            return;

        auto pSwapChain = std::dynamic_pointer_cast<DrawingResource>(m_pContext->GetSwapChain());

        m_pDevice->CopyTexture(pSwapChain, pResource);
    });

    pFrameGraph->FetchResources(*m_pResourceTable);

    return true;
}

void DrawingSystem::GetVisableRenderable(RenderQueueItemListType& items)
{
    for (auto& pEntity : m_pMeshList)
    {
        auto pTrans = pEntity->GetComponent<TransformComponent>();
        auto pMesh = pEntity->GetComponent<MeshFilterComponent>();

        items.push_back(RenderQueueItem{ dynamic_cast<IRenderable*>(pMesh->GetMesh().get()), pTrans});
    }
}

float4x4 DrawingSystem::UpdateViewMatrix(TransformComponent* pTransform)
{
    float3 pos = pTransform->GetPosition();
    float3 at = float3(0.0f, 0.0f, 1.0f);
    float3 up = float3(0.0f, 1.0f, 0.0f);

    float3 z = Vec::Normalize(at - pos);
    float3 x = Vec::Normalize(Vec::Cross(up, z));
    float3 y = Vec::Cross(z, x);

    float4x4 ret = {
        x.x, y.x, z.x, 0.f,
        x.y, y.y, z.y, 0.f,
        x.z, y.z, z.z, 0.f,
        Vec::Dot(-x, pos), Vec::Dot(-y, pos), Vec::Dot(-z, pos), 1.f
    };

    return ret;
}

float4x4 DrawingSystem::UpdateProjectionMatrix(CameraComponent* pCamera)
{
    auto fovy = pCamera->GetFov();
    auto zn = pCamera->GetClippingNear();
    auto zf = pCamera->GetClippingFar();
    auto aspect = (float)(gpGlobal->GetConfiguration<AppConfiguration>().GetWidth())
                / (float)(gpGlobal->GetConfiguration<AppConfiguration>().GetHeight());

    float d2r = PI_F / 180.0f;
    float yScale = 1.0f / std::tanf(d2r * fovy / 2.0f);
    float xScale = yScale / aspect;

    float4x4 ret = {
        xScale, 0.0f, 0.0f, 0.0f,
        0.0f, yScale, 0.0f, 0.0f,
        0.0f, 0.0f, zf / (zf - zn), 1.0f,
        0.0f, 0.0f, -zn * zf / (zf - zn), 0.0f
    };

    return ret;
}