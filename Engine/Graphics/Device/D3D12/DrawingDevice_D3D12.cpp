#include "DrawingRawResource_D3D12.h"
#include "DrawingDevice_D3D12.h"

using namespace Engine;

DrawingCommandManager_D3D12::DrawingCommandManager_D3D12(const std::shared_ptr<DrawingDevice_D3D12> device) : m_pDevice(device)
{
    ID3D12CommandQueue* pD3D12CommandQueueRaw[eCommandList_Count] = { nullptr };
    ID3D12CommandAllocator* pD3D12CommandAllocatorRaw[eCommandList_Count] = { nullptr };

    for (int i = 0; i < 1; ++i)
    {
        D3D12_COMMAND_QUEUE_DESC commandQueueDesc;
        commandQueueDesc.Type = D3D12Enum((EDrawingCommandListType)i);
        commandQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
        commandQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
        commandQueueDesc.NodeMask = 0;

        HRESULT hr = m_pDevice.lock()->GetDevice()->CreateCommandQueue(&commandQueueDesc, IID_PPV_ARGS(&pD3D12CommandQueueRaw[i]));
        assert(SUCCEEDED(hr));

        hr = m_pDevice.lock()->GetDevice()->CreateCommandAllocator(D3D12Enum((EDrawingCommandListType)i), IID_PPV_ARGS(&pD3D12CommandAllocatorRaw[i]));
        assert(SUCCEEDED(hr));

        m_pCommandQueue[i] = std::shared_ptr<ID3D12CommandQueue>(pD3D12CommandQueueRaw[i], D3D12Releaser<ID3D12CommandQueue>);
        m_pCommandAllocator[i] = std::shared_ptr<ID3D12CommandAllocator>(pD3D12CommandAllocatorRaw[i], D3D12Releaser<ID3D12CommandAllocator>);
    }
}

DrawingCommandManager_D3D12::~DrawingCommandManager_D3D12()
{
}

std::shared_ptr<ID3D12CommandQueue> DrawingCommandManager_D3D12::GetCommandQueue(EDrawingCommandListType type) const
{
    assert(m_pCommandQueue[type] != nullptr);
    return m_pCommandQueue[type];
}

std::shared_ptr<ID3D12CommandAllocator> DrawingCommandManager_D3D12::GetCommandAllocator(EDrawingCommandListType type) const
{
    assert(m_pCommandAllocator[type] != nullptr);
    return m_pCommandAllocator[type];
}

bool DrawingCommandManager_D3D12::CreateCommandList(const DrawingCommandListDesc& desc, std::shared_ptr<DrawingCommandList>& pRes)
{
    auto type = desc.mType;
    if (type < 0 || type >= eCommandList_Count)
        return false;

    auto pDevice = m_pDevice.lock();
    auto pCommandList = std::make_shared<DrawingCommandList>(pDevice);

    auto index = m_size[type];
    auto commandListType = D3D12Enum((EDrawingCommandListType)type);
    auto pAllocator = m_pCommandAllocator[type];

    std::shared_ptr<DrawingRawCommandList> pCommandListRaw = std::make_shared<DrawingRawCommandList_D3D12>(pDevice, index, commandListType, pAllocator);
    pCommandList->SetDesc(std::shared_ptr<DrawingResourceDesc>(desc.Clone()));
    pCommandList->SetResource(pCommandListRaw);

    m_commandLists.emplace_back(pCommandList);

    pRes = pCommandList;
    return true;
}

std::shared_ptr<DrawingCommandList> DrawingCommandManager_D3D12::GetCurrentCommandList()
{
    return m_commandLists[0];
}

DrawingDevice_D3D12::DrawingDevice_D3D12(const std::shared_ptr<ID3D12Device> device) : DrawingDevice(), m_pDevice(device)
{
    assert(m_pDevice != nullptr);

    IDXGIFactory4* pDXGIFactoryRaw;

    HRESULT hr = CreateDXGIFactory1(IID_PPV_ARGS(&pDXGIFactoryRaw));
    assert(SUCCEEDED(hr));

    m_pDXGIFactory = std::shared_ptr<IDXGIFactory4>(pDXGIFactoryRaw, D3D12Releaser<IDXGIFactory4>);

    // Tick to use shared_from_this().
    auto ptr = std::shared_ptr<DrawingDevice_D3D12>( this, [](DrawingDevice_D3D12*){} );
    m_pCommandManager = std::make_shared<DrawingCommandManager_D3D12>(std::static_pointer_cast<DrawingDevice_D3D12>(shared_from_this()));
}

DrawingDevice_D3D12::~DrawingDevice_D3D12()
{
    Shutdown();
}

void DrawingDevice_D3D12::Initialize()
{
    assert(m_pDevice != nullptr);

    IDXGIFactory4* pDXGIFactoryRaw;

    HRESULT hr = CreateDXGIFactory1(IID_PPV_ARGS(&pDXGIFactoryRaw));
    assert(SUCCEEDED(hr));

    m_pDXGIFactory = std::shared_ptr<IDXGIFactory4>(pDXGIFactoryRaw, D3D12Releaser<IDXGIFactory4>);
    m_pCommandManager = std::make_shared<DrawingCommandManager_D3D12>(std::static_pointer_cast<DrawingDevice_D3D12>(shared_from_this()));
}

void DrawingDevice_D3D12::Shutdown()
{
}

bool DrawingDevice_D3D12::CreateVertexFormat(const DrawingVertexFormatDesc& desc, std::shared_ptr<DrawingVertexFormat>& pRes)
{
    return true;
}

bool DrawingDevice_D3D12::CreateVertexBuffer(const DrawingVertexBufferDesc& desc, std::shared_ptr<DrawingVertexBuffer>& pRes, std::shared_ptr<DrawingResource> pRefRes, const void* pData, uint32_t size)
{
    return true;
}

bool DrawingDevice_D3D12::CreateIndexBuffer(const DrawingIndexBufferDesc& desc, std::shared_ptr<DrawingIndexBuffer>& pRes, std::shared_ptr<DrawingResource> pRefRes, const void* pData, uint32_t size)
{
    return true;
}

bool DrawingDevice_D3D12::CreateTexture(const DrawingTextureDesc& desc, std::shared_ptr<DrawingTexture>& pRes, const void* pData, uint32_t size)
{
    return true;
}

bool DrawingDevice_D3D12::CreateTarget(const DrawingTargetDesc& desc, std::shared_ptr<DrawingTarget>& pRes)
{
    std::shared_ptr<DrawingRawTarget> pTargetRaw = nullptr;
    if (desc.mHwnd == nullptr)
    {

    }
    else
    {
        DXGI_SWAP_CHAIN_DESC SwapChainDesc;
        SwapChainDesc.BufferDesc.Width = desc.mWidth;
        SwapChainDesc.BufferDesc.Height = desc.mHeight;
        SwapChainDesc.BufferDesc.RefreshRate.Numerator = desc.mRefreshRate;
        SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
        SwapChainDesc.BufferDesc.Format = D3D12Enum(desc.mFormat);
        SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
        SwapChainDesc.SampleDesc.Count = desc.mMultiSampleCount;
        SwapChainDesc.SampleDesc.Quality = desc.mMultiSampleQuality;
        SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        SwapChainDesc.BufferCount = desc.mSwapBufferCount;
        SwapChainDesc.OutputWindow = (HWND)desc.mHwnd;
        SwapChainDesc.Windowed = true;
        SwapChainDesc.SwapEffect = D3D12Enum(desc.mSwapChain);
        SwapChainDesc.Flags = 0;

        pTargetRaw = std::make_shared<DrawingRawSwapChain_D3D12>(std::static_pointer_cast<DrawingDevice_D3D12>(shared_from_this()), SwapChainDesc);
    }

    auto pTarget = std::make_shared<DrawingTarget>(shared_from_this());
    pTarget->SetDesc(std::shared_ptr<DrawingResourceDesc>(desc.Clone()));
    pTarget->SetResource(pTargetRaw);

    pRes = pTarget;
    return true;
}

bool DrawingDevice_D3D12::CreateDepthBuffer(const DrawingDepthBufferDesc& desc, std::shared_ptr<DrawingDepthBuffer>& pRes)
{
    return true;
}

bool DrawingDevice_D3D12::CreateBlendState(const DrawingBlendStateDesc& desc, std::shared_ptr<DrawingBlendState>& pRes)
{
    return true;
}

bool DrawingDevice_D3D12::CreateDepthState(const DrawingDepthStateDesc& desc, std::shared_ptr<DrawingDepthState>& pRes)
{
    return true;
}

bool DrawingDevice_D3D12::CreateRasterState(const DrawingRasterStateDesc& desc, std::shared_ptr<DrawingRasterState>& pRes)
{
    return true;
}

bool DrawingDevice_D3D12::CreateSamplerState(const DrawingSamplerStateDesc& desc, std::shared_ptr<DrawingSamplerState>& pRes)
{
    return true;
}

bool DrawingDevice_D3D12::CreateEffectFromFile(const DrawingEffectDesc& desc, std::shared_ptr<DrawingEffect>& pRes)
{
    return true;
}

bool DrawingDevice_D3D12::CreateEffectFromString(const std::string& str, const DrawingEffectDesc& desc, std::shared_ptr<DrawingEffect>& pRes)
{
    return true;
}

bool DrawingDevice_D3D12::CreateEffectFromBuffer(const void* pData, uint32_t length, const DrawingEffectDesc& desc, std::shared_ptr<DrawingEffect>& pRes)
{
    return true;
}

bool DrawingDevice_D3D12::CreateEffectFromShader(const DrawingEffectDesc& desc, std::shared_ptr<DrawingVertexShader> pVSShader, std::shared_ptr<DrawingPixelShader> pPSShader, std::shared_ptr<DrawingEffect>& pRes)
{
    return true;
}

bool DrawingDevice_D3D12::CreateVertexShaderFromFile(const DrawingVertexShaderDesc& desc, std::shared_ptr<DrawingVertexShader>& pRes)
{
    return true;
}

bool DrawingDevice_D3D12::CreateVertexShaderFromString(const std::string& str, const DrawingVertexShaderDesc& desc, std::shared_ptr<DrawingVertexShader>& pRes)
{
    return true;
}

bool DrawingDevice_D3D12::CreateVertexShaderFromBuffer(const void* pData, uint32_t length, const DrawingVertexShaderDesc& desc, std::shared_ptr<DrawingVertexShader>& pRes)
{
    return true;
}

bool DrawingDevice_D3D12::CreatePixelShaderFromFile(const DrawingPixelShaderDesc& desc, std::shared_ptr<DrawingPixelShader>& pRes)
{
    return true;
}

bool DrawingDevice_D3D12::CreatePixelShaderFromString(const std::string& str, const DrawingPixelShaderDesc& desc, std::shared_ptr<DrawingPixelShader>& pRes)
{
    return true;
}

bool DrawingDevice_D3D12::CreatePixelShaderFromBuffer(const void* pData, uint32_t length, const DrawingPixelShaderDesc& desc, std::shared_ptr<DrawingPixelShader>& pRes)
{
    return true;
}

bool DrawingDevice_D3D12::CreateCommandList(const DrawingCommandListDesc& desc, std::shared_ptr<DrawingCommandList>& pRes)
{
    assert(m_pCommandManager != nullptr);
    return m_pCommandManager->CreateCommandList(desc, pRes);
}

void DrawingDevice_D3D12::ClearTarget(std::shared_ptr<DrawingTarget> pTarget, const float4& color)
{
    auto pTargetRaw = std::dynamic_pointer_cast<DrawingRawFragmentTarget_D3D12>(pTarget->GetResource());
    assert(pTargetRaw != nullptr);

    auto pCommandListRaw = std::dynamic_pointer_cast<DrawingRawCommandList_D3D12>(m_pCommandManager->GetCurrentCommandList()->GetResource());
    assert(pCommandListRaw != nullptr);

    auto renderTargetViewHandle = pTargetRaw->GetDescriptorHeap()->GetCPUDescriptorHandleForHeapStart();
    auto renderTargetViewDescriptorSize = m_pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
    renderTargetViewHandle.ptr += (renderTargetViewDescriptorSize * pTargetRaw->GetCurrentIndex());

    auto commandList = pCommandListRaw->GetCommandList();
    auto commandQueue = m_pCommandManager->GetCommandQueue((EDrawingCommandListType)0);
    auto commandAllocator = m_pCommandManager->GetCommandAllocator((EDrawingCommandListType)0);

    commandList->ClearRenderTargetView(renderTargetViewHandle, color.mData, 0, nullptr);
    HRESULT hr = commandList->Close();
    if (FAILED(hr))
        return;

    ID3D12CommandList* ppCommandLists[1];
    ppCommandLists[0] = commandList.get();
    commandQueue->ExecuteCommandLists(1, ppCommandLists);
}

void DrawingDevice_D3D12::ClearDepthBuffer(std::shared_ptr<DrawingDepthBuffer> pDepthBuffer, float depth, uint8_t stencil, uint32_t flag)
{
}

void DrawingDevice_D3D12::SetVertexFormat(std::shared_ptr<DrawingVertexFormat> pFormat)
{
}

void DrawingDevice_D3D12::SetVertexBuffer(std::shared_ptr<DrawingVertexBuffer> pVB[], uint32_t count)
{
}

void DrawingDevice_D3D12::SetIndexBuffer(std::shared_ptr<DrawingIndexBuffer> pIB)
{
}

void DrawingDevice_D3D12::SetBlendState(std::shared_ptr<DrawingBlendState> pBlend, float4 blendFactor, uint32_t sampleMask)
{
}

void DrawingDevice_D3D12::SetDepthState(std::shared_ptr<DrawingDepthState> pDepth, uint32_t stencilRef)
{
}

void DrawingDevice_D3D12::SetRasterState(std::shared_ptr<DrawingRasterState> pRaster)
{
}

void DrawingDevice_D3D12::PushBlendState()
{
}

void DrawingDevice_D3D12::PopBlendState()
{
}

void DrawingDevice_D3D12::PushDepthState()
{
}

void DrawingDevice_D3D12::PopDepthState()
{
}

void DrawingDevice_D3D12::PushRasterState()
{
}

void DrawingDevice_D3D12::PopRasterState()
{
}

void DrawingDevice_D3D12::SetViewport(Box2* vp)
{
}

void DrawingDevice_D3D12::SetTargets(std::shared_ptr<DrawingTarget> pTarget[], uint32_t maxTargets, std::shared_ptr<DrawingDepthBuffer> pDepthBuffer, std::shared_ptr<DrawingRWBuffer> pRWBuffer[], uint32_t maxRWBuffers)
{
}

bool DrawingDevice_D3D12::UpdateEffectParameter(std::shared_ptr<DrawingParameter> pParam, std::shared_ptr<DrawingEffect> pEffect)
{
    return true;
}

bool DrawingDevice_D3D12::UpdateEffectTexture(std::shared_ptr<DrawingTexture> pTex, std::shared_ptr<std::string> pName, std::shared_ptr<DrawingEffect> pEffect)
{
    return true;
}

bool DrawingDevice_D3D12::UpdateEffectBuffer(std::shared_ptr<DrawingTexBuffer> pBuffer, std::shared_ptr<std::string> pName, std::shared_ptr<DrawingEffect> pEffect)
{
    return true;
}

bool DrawingDevice_D3D12::UpdateEffectSampler(std::shared_ptr<DrawingSamplerState> pSampler, std::shared_ptr<std::string> pName, std::shared_ptr<DrawingEffect> pEffect)
{
    return true;
}

bool DrawingDevice_D3D12::UpdateEffectTexBuffer(std::shared_ptr<DrawingTexBuffer> pTexBuffer, std::shared_ptr<std::string> pName, std::shared_ptr<DrawingEffect> pEffect)
{
    return true;
}

bool DrawingDevice_D3D12::UpdateEffectRWBuffer(std::shared_ptr<DrawingRWBuffer> pRWBuffer, std::shared_ptr<std::string> pName, std::shared_ptr<DrawingEffect> pEffect)
{
    return true;
}

bool DrawingDevice_D3D12::UpdateEffectInputRWBuffer(std::shared_ptr<DrawingRWBuffer> pRWBuffer, std::shared_ptr<std::string> pName, std::shared_ptr<DrawingEffect> pEffect)
{
    return true;
}

bool DrawingDevice_D3D12::UpdateEffectOutputRWBuffer(std::shared_ptr<DrawingRWBuffer> pRWBuffer, std::shared_ptr<std::string> pName, std::shared_ptr<DrawingEffect> pEffect)
{
    return true;
}

void DrawingDevice_D3D12::BeginEffect(DrawingContext& dc, std::shared_ptr<DrawingEffect> pEffect)
{
}

void DrawingDevice_D3D12::EndEffect(DrawingContext& dc, std::shared_ptr<DrawingEffect> pEffect)
{
}

bool DrawingDevice_D3D12::DrawPrimitive(std::shared_ptr<DrawingPrimitive> pRes)
{
    return true;
}

bool DrawingDevice_D3D12::Present(const std::shared_ptr<DrawingTarget> pTarget, uint32_t syncInterval)
{
    auto pSwapChainRaw = std::static_pointer_cast<DrawingRawSwapChain_D3D12>(pTarget->GetResource());
    assert(pSwapChainRaw != nullptr);

    HRESULT hr = pSwapChainRaw->Present(syncInterval);
    if (!SUCCEEDED(hr))
        return false;

    return true;
}


std::shared_ptr<ID3D12Device> DrawingDevice_D3D12::GetDevice() const
{
    return m_pDevice;
}

std::shared_ptr<IDXGIFactory4> DrawingDevice_D3D12::GetDXGIFactory() const
{
    return m_pDXGIFactory;
}

std::shared_ptr<DrawingCommandManager_D3D12> DrawingDevice_D3D12::GetCommandManager() const
{
    return m_pCommandManager;
}