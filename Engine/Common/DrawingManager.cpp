#pragma once

#include <assert.h>
#include <fstream>

#include "Global.h"
#include "DrawingManager.h"
#include "D3D11/DrawingDevice_D3D11.h"
#include "D3D12/DrawingDevice_D3D12.h"

using namespace Engine;

DrawingManager::DrawingManager() : m_window(nullptr),
    m_deviceSize(0),
    m_deviceType(gpGlobal->GetConfiguration().type),
    m_pDevice(nullptr),
    m_pContext(nullptr),
    m_pEffectPool(nullptr),
    m_pResourceFactory(nullptr),
    m_pResourceTable(nullptr)
{
}

DrawingManager::~DrawingManager()
{
}

void DrawingManager::Initialize()
{
    if (!EstablishConfiguration())
        return;
}

void DrawingManager::Shutdown()
{
    m_rendererTable.clear();
}

void DrawingManager::Tick()
{
    m_pContext->UpdateContext(*m_pResourceTable);
    m_pDevice->ClearTarget(m_pContext->GetSwapChain(), gpGlobal->GetConfiguration().background);

    std::for_each(m_rendererTable.begin(), m_rendererTable.end(), [this](RendererTable::value_type& aElem)
    {
        auto& pRenderer = aElem.second;
        if (pRenderer != nullptr)
            pRenderer->Draw(*m_pResourceTable);
    });

    m_pDevice->Present(m_pContext->GetSwapChain(), 0);
}

void DrawingManager::Flush()
{
}

void DrawingManager::BeginFrame()
{
}

void DrawingManager::EndFrame()
{
}

EDeviceType DrawingManager::GetDeviceType() const
{
    return m_deviceType;
}

void DrawingManager::SetDeviceType(EDeviceType type)
{
    m_deviceType = type;
}

bool DrawingManager::EstablishConfiguration()
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

bool DrawingManager::PreConfiguration()
{
    if (gpGlobal == nullptr)
        return false;

    m_deviceSize.x = gpGlobal->GetConfiguration().width;
    m_deviceSize.y = gpGlobal->GetConfiguration().height;
    m_window = gpGlobal->GetConfiguration().hWnd;

    return true;
}

bool DrawingManager::CreateDevice()
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

bool DrawingManager::CreatePreResource()
{
    m_pEffectPool = std::make_shared<DrawingEffectPool>(m_pDevice);
    m_pResourceFactory = std::make_shared<DrawingResourceFactory>(m_pDevice);
    m_pResourceTable = std::make_shared<DrawingResourceTable>(*m_pResourceFactory);

    m_pResourceFactory->SetEffectPool(m_pEffectPool);

    return true;
}

bool DrawingManager::RegisterRenderer()
{
    for (uint32_t module = eRTModule_Renderer_Begin; module != eRTModule_Renderer_End; module++)
    {
        auto& pRenderer = gpGlobal->GetRenderer((ERTModule)module);
        if (pRenderer != nullptr)
        {
            m_rendererTable.emplace((ERTModule)module, pRenderer);
            pRenderer->AttachDevice(m_pDevice, m_pContext);
            pRenderer->DefineResources(*m_pResourceTable);
            pRenderer->SetupStages();
        }
    }
    return true;
}

std::shared_ptr<DrawingTarget> DrawingManager::CreateSwapChain()
{
    assert(m_window != nullptr);

    DrawingTargetDesc desc;
    desc.mHwnd = m_window;
    desc.mWidth = m_deviceSize.x;
    desc.mHeight = m_deviceSize.y;
    desc.mFormat = eFormat_R8G8B8A8_UNORM;
    //desc.mMultiSampleCount = 4;
    //desc.mMultiSampleQuality = 0;

    std::shared_ptr<DrawingTarget> pSwapChain;

    if (!m_pDevice->CreateTarget(desc, pSwapChain))
        return nullptr;

    return pSwapChain;
}

std::shared_ptr<DrawingDepthBuffer> DrawingManager::CreateDepthBuffer()
{
    DrawingDepthBufferDesc desc;
    desc.mWidth = m_deviceSize.x;
    desc.mHeight = m_deviceSize.y;
    desc.mFormat = eFormat_D32_FLOAT;

    std::shared_ptr<DrawingDepthBuffer> pDepthBuffer;

    if (!m_pDevice->CreateDepthBuffer(desc, pDepthBuffer))
        return nullptr;

    return pDepthBuffer;
}

bool DrawingManager::PostConfiguration()
{
    auto pSwapChain = CreateSwapChain();
    auto pDepthBuffer = CreateDepthBuffer();

    m_pContext->SetSwapChain(pSwapChain);
    m_pContext->SetDepthBuffer(pDepthBuffer);
    m_pContext->SetViewport(Box2(float2(0, 0), float2((float)gpGlobal->GetConfiguration().width, (float)gpGlobal->GetConfiguration().height)));

    m_pContext->UpdateTargets(*m_pResourceTable);

    if(!m_pResourceTable->BuildResources())
        return false;

    m_pDevice->Flush();

    std::for_each(m_rendererTable.begin(), m_rendererTable.end(), [this](RendererTable::value_type& aElem)
    {
        auto& pRenderer = aElem.second;
        if (pRenderer != nullptr)
            pRenderer->MapResources(*m_pResourceTable);
    });

    return true;
}