
#pragma once

#include <d3d12.h>
#include <dxgi1_5.h>

#include "DrawingConstants.h"
#include "DrawingType.h"
#include "DrawingDevice.h"
#include "DrawingUtil_D3D12.h"

namespace Engine
{
    class DrawingDevice_D3D12;
    class DrawingCommandManager_D3D12
    {
    public:
        DrawingCommandManager_D3D12(const std::shared_ptr<DrawingDevice_D3D12> device);
        virtual ~DrawingCommandManager_D3D12();

        std::shared_ptr<ID3D12CommandQueue> GetCommandQueue(EDrawingCommandListType type) const;
        std::shared_ptr<ID3D12CommandAllocator> GetCommandAllocator(EDrawingCommandListType type) const;

        bool CreateCommandList(const DrawingCommandListDesc& desc, std::shared_ptr<DrawingCommandList>& pRes);
        std::shared_ptr<DrawingCommandList> GetCurrentCommandList();

    private:
        std::weak_ptr<DrawingDevice_D3D12> m_pDevice;

        std::shared_ptr<ID3D12CommandQueue> m_pCommandQueue[eCommandList_Count] = { nullptr };
        std::shared_ptr<ID3D12CommandAllocator> m_pCommandAllocator[eCommandList_Count] = { nullptr };

        std::vector<std::shared_ptr<DrawingCommandList>> m_commandLists;

        uint32_t m_size[eCommandList_Count] = { 0 };
    };


    class DrawingDevice_D3D12 : public DrawingDevice
    {
    public:
        DrawingDevice_D3D12(const std::shared_ptr<ID3D12Device> device);
        virtual ~DrawingDevice_D3D12();

        void Initialize() override;
        void Shutdown() override;

        bool CreateVertexFormat(const DrawingVertexFormatDesc& desc, std::shared_ptr<DrawingVertexFormat>& pRes) override;
        bool CreateVertexBuffer(const DrawingVertexBufferDesc& desc, std::shared_ptr<DrawingVertexBuffer>& pRes, std::shared_ptr<DrawingResource> pRefRes, const void* pData = nullptr, uint32_t size = 0) override;
        bool CreateIndexBuffer(const DrawingIndexBufferDesc& desc, std::shared_ptr<DrawingIndexBuffer>& pRes, std::shared_ptr<DrawingResource> pRefRes, const void* pData = nullptr, uint32_t size = 0) override;
        bool CreateTexture(const DrawingTextureDesc& desc, std::shared_ptr<DrawingTexture>& pRes, const void* pData = nullptr, uint32_t size = 0) override;
        bool CreateTarget(const DrawingTargetDesc& desc, std::shared_ptr<DrawingTarget>& pRes) override;
        bool CreateDepthBuffer(const DrawingDepthBufferDesc& desc, std::shared_ptr<DrawingDepthBuffer>& pRes) override;

        bool CreateBlendState(const DrawingBlendStateDesc& desc, std::shared_ptr<DrawingBlendState>& pRes) override;
        bool CreateDepthState(const DrawingDepthStateDesc& desc, std::shared_ptr<DrawingDepthState>& pRes) override;
        bool CreateRasterState(const DrawingRasterStateDesc& desc, std::shared_ptr<DrawingRasterState>& pRes) override;
        bool CreateSamplerState(const DrawingSamplerStateDesc& desc, std::shared_ptr<DrawingSamplerState>& pRes) override;

        bool CreateEffectFromFile(const DrawingEffectDesc& desc, std::shared_ptr<DrawingEffect>& pRes) override;
        bool CreateEffectFromString(const std::string& str, const DrawingEffectDesc& desc, std::shared_ptr<DrawingEffect>& pRes) override;
        bool CreateEffectFromBuffer(const void* pData, uint32_t length, const DrawingEffectDesc& desc, std::shared_ptr<DrawingEffect>& pRes) override;
        bool CreateEffectFromShader(const DrawingEffectDesc& desc, std::shared_ptr<DrawingVertexShader> pVSShader, std::shared_ptr<DrawingPixelShader> pPSShader, std::shared_ptr<DrawingEffect>& pRes) override;

        bool CreateVertexShaderFromFile(const DrawingVertexShaderDesc& desc, std::shared_ptr<DrawingVertexShader>& pRes) override;
        bool CreateVertexShaderFromString(const std::string& str, const DrawingVertexShaderDesc& desc, std::shared_ptr<DrawingVertexShader>& pRes) override;
        bool CreateVertexShaderFromBuffer(const void* pData, uint32_t length, const DrawingVertexShaderDesc& desc, std::shared_ptr<DrawingVertexShader>& pRes) override;
        bool CreatePixelShaderFromFile(const DrawingPixelShaderDesc& desc, std::shared_ptr<DrawingPixelShader>& pRes) override;
        bool CreatePixelShaderFromString(const std::string& str, const DrawingPixelShaderDesc& desc, std::shared_ptr<DrawingPixelShader>& pRes) override;
        bool CreatePixelShaderFromBuffer(const void* pData, uint32_t length, const DrawingPixelShaderDesc& desc, std::shared_ptr<DrawingPixelShader>& pRes) override;

        bool CreateCommandList(const DrawingCommandListDesc& desc, std::shared_ptr<DrawingCommandList>& pRes) override;

        void ClearTarget(std::shared_ptr<DrawingTarget> pTarget, const float4& color) override;
        void ClearDepthBuffer(std::shared_ptr<DrawingDepthBuffer> pDepthBuffer, float depth, uint8_t stencil, uint32_t flag) override;

        void SetVertexFormat(std::shared_ptr<DrawingVertexFormat> pFormat) override;
        void SetVertexBuffer(std::shared_ptr<DrawingVertexBuffer> pVB[], uint32_t count) override;
        void SetIndexBuffer(std::shared_ptr<DrawingIndexBuffer> pIB) override;

        void SetBlendState(std::shared_ptr<DrawingBlendState> pBlend, float4 blendFactor, uint32_t sampleMask) override;
        void SetDepthState(std::shared_ptr<DrawingDepthState> pDepth, uint32_t stencilRef) override;
        void SetRasterState(std::shared_ptr<DrawingRasterState> pRaster) override;

        void PushBlendState() override;
        void PopBlendState() override;
        void PushDepthState() override;
        void PopDepthState() override;
        void PushRasterState() override;
        void PopRasterState() override;

        void SetViewport(Box2* vp) override;

        void SetTargets(std::shared_ptr<DrawingTarget> pTarget[], uint32_t maxTargets, std::shared_ptr<DrawingDepthBuffer> pDepthBuffer, std::shared_ptr<DrawingRWBuffer> pRWBuffer[], uint32_t maxRWBuffers) override;

        bool UpdateEffectParameter(std::shared_ptr<DrawingParameter> pParam, std::shared_ptr<DrawingEffect> pEffect) override;
        bool UpdateEffectTexture(std::shared_ptr<DrawingTexture> pTex, std::shared_ptr<std::string> pName, std::shared_ptr<DrawingEffect> pEffect) override;
        bool UpdateEffectBuffer(std::shared_ptr<DrawingTexBuffer> pBuffer, std::shared_ptr<std::string> pName, std::shared_ptr<DrawingEffect> pEffect) override;
        bool UpdateEffectSampler(std::shared_ptr<DrawingSamplerState> pSampler, std::shared_ptr<std::string> pName, std::shared_ptr<DrawingEffect> pEffect) override;
        bool UpdateEffectTexBuffer(std::shared_ptr<DrawingTexBuffer> pTexBuffer, std::shared_ptr<std::string> pName, std::shared_ptr<DrawingEffect> pEffect) override;
        bool UpdateEffectRWBuffer(std::shared_ptr<DrawingRWBuffer> pRWBuffer, std::shared_ptr<std::string> pName, std::shared_ptr<DrawingEffect> pEffect) override;
        bool UpdateEffectInputRWBuffer(std::shared_ptr<DrawingRWBuffer> pRWBuffer, std::shared_ptr<std::string> pName, std::shared_ptr<DrawingEffect> pEffect) override;
        bool UpdateEffectOutputRWBuffer(std::shared_ptr<DrawingRWBuffer> pRWBuffer, std::shared_ptr<std::string> pName, std::shared_ptr<DrawingEffect> pEffect) override;

        void BeginEffect(DrawingContext& dc, std::shared_ptr<DrawingEffect> pEffect) override;
        void EndEffect(DrawingContext& dc, std::shared_ptr<DrawingEffect> pEffect) override;

        bool DrawPrimitive(std::shared_ptr<DrawingPrimitive> pRes) override;
        bool Present(const std::shared_ptr<DrawingTarget> pTarget, uint32_t syncInterval) override;

        std::shared_ptr<ID3D12Device> GetDevice() const;
        std::shared_ptr<IDXGIFactory4> GetDXGIFactory() const;

        std::shared_ptr<DrawingCommandManager_D3D12> GetCommandManager() const;

    private:
        std::shared_ptr<ID3D12Device> m_pDevice;
        std::shared_ptr<IDXGIFactory4> m_pDXGIFactory;

        std::shared_ptr<DrawingCommandManager_D3D12> m_pCommandManager;
    };

    template<>
    static std::shared_ptr<DrawingDevice> CreateNativeDevice<eDevice_D3D12>()
    {
        uint32_t adaptorIndex = 0;
        ID3D12Device* pDevice = nullptr;
        IDXGIFactory4* pDxgiFactory = nullptr;
        IDXGIAdapter1* pAdapter = nullptr; 
        std::vector<IDXGIAdapter1*> adapterList;
        HRESULT hr = CreateDXGIFactory1(IID_PPV_ARGS(&pDxgiFactory));
        if (FAILED(hr))
            return nullptr;

        while (pDxgiFactory->EnumAdapters1(adaptorIndex, &pAdapter) != DXGI_ERROR_NOT_FOUND)
        {
            hr = D3D12CreateDevice(pAdapter, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&pDevice));
            if (SUCCEEDED(hr))
            {
                std::shared_ptr<ID3D12Device> pDevicePtr(pDevice, D3D12Releaser<ID3D12Device>);
                return std::make_shared<DrawingDevice_D3D12>(pDevicePtr);
            }
            adapterList.push_back(pAdapter);
            ++adaptorIndex;
        }

        return nullptr;
    }
}