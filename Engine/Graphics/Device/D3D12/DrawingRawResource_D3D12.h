#pragma once

#include <d3d12.h>
#include <dxgi.h>

#include "DrawingDevice_D3D12.h"
#include "DrawingRawResource.h"
#include "DrawingUtil_D3D12.h"

namespace Engine
{
    class DrawingRawTarget_D3D12 : public DrawingRawTarget
    {
    public:
        DrawingRawTarget_D3D12(std::shared_ptr<DrawingDevice_D3D12> pDevice) : m_pDevice(pDevice) {}

        virtual ~DrawingRawTarget_D3D12() = default;

        virtual ETargetType GetTargetType() const = 0;

    protected:
        std::shared_ptr<DrawingDevice_D3D12> m_pDevice;
        std::shared_ptr<ID3D12Resource> m_pTarget;
    };

    class DrawingRawFragmentTarget_D3D12 : public DrawingRawTarget_D3D12
    {
    public:
        using DrawingRawTarget_D3D12::DrawingRawTarget_D3D12;
        DrawingRawFragmentTarget_D3D12(std::shared_ptr<DrawingDevice_D3D12> pDevice) : DrawingRawTarget_D3D12(pDevice), m_bufferIndex(0), m_pRenderTargetViewHeap(nullptr) {}
        virtual ~DrawingRawFragmentTarget_D3D12() = default;

        std::shared_ptr<ID3D12DescriptorHeap> GetDescriptorHeap() const
        {
            return m_pRenderTargetViewHeap;
        }

        uint32_t GetCurrentIndex() const { return m_bufferIndex; }

    protected:
        std::shared_ptr<ID3D12DescriptorHeap> m_pRenderTargetViewHeap;
        uint32_t m_bufferIndex;
    };

    class DrawingRawSwapChain_D3D12 : public DrawingRawFragmentTarget_D3D12
    {
    public:
        DrawingRawSwapChain_D3D12(std::shared_ptr<DrawingDevice_D3D12> pDevice, DXGI_SWAP_CHAIN_DESC& desc) : DrawingRawFragmentTarget_D3D12(pDevice)
        {
            IDXGISwapChain* pDXGISwapChainRaw = nullptr;
            IDXGISwapChain3* pDXGISwapChain3Raw = nullptr;
            HRESULT hr = m_pDevice->GetDXGIFactory()->CreateSwapChain(m_pDevice->GetCommandManager()->GetCommandQueue(eCommandList_Direct).get(), &desc, &pDXGISwapChainRaw);
            assert(SUCCEEDED(hr));
            hr = pDXGISwapChainRaw->QueryInterface(IID_PPV_ARGS(&pDXGISwapChain3Raw));
            m_pDXGISwapChain = std::shared_ptr<IDXGISwapChain3>(pDXGISwapChain3Raw, D3D12Releaser<IDXGISwapChain>);

            D3D12_DESCRIPTOR_HEAP_DESC renderTargetViewHeapDesc;
            renderTargetViewHeapDesc.NumDescriptors = 2;
            renderTargetViewHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
            renderTargetViewHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
            renderTargetViewHeapDesc.NodeMask = 0;

            ID3D12DescriptorHeap* pRenderTargetViewHeapRaw = nullptr;
            hr = m_pDevice->GetDevice()->CreateDescriptorHeap(&renderTargetViewHeapDesc, IID_PPV_ARGS(&pRenderTargetViewHeapRaw));
            assert(SUCCEEDED(hr));

            ID3D12Resource* pTargetRaw[2] = { nullptr };
            auto renderTargetViewHandle = pRenderTargetViewHeapRaw->GetCPUDescriptorHandleForHeapStart();
            auto renderTargetViewDescriptorSize = m_pDevice->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

            hr = m_pDXGISwapChain->GetBuffer(0, IID_PPV_ARGS(&pTargetRaw[0]));
            assert(SUCCEEDED(hr));
            m_pTarget = std::shared_ptr<ID3D12Resource>(pTargetRaw[0], D3D12Releaser<ID3D12Resource>);
            
            m_pDevice->GetDevice()->CreateRenderTargetView(pTargetRaw[0], nullptr, renderTargetViewHandle);
            renderTargetViewHandle.ptr += renderTargetViewDescriptorSize;

            hr = m_pDXGISwapChain->GetBuffer(1, IID_PPV_ARGS(&pTargetRaw[1]));
            assert(SUCCEEDED(hr));
            m_pTarget2 = std::shared_ptr<ID3D12Resource>(pTargetRaw[1], D3D12Releaser<ID3D12Resource>);
            m_pDevice->GetDevice()->CreateRenderTargetView(pTargetRaw[1], nullptr, renderTargetViewHandle);

            m_pRenderTargetViewHeap = std::shared_ptr<ID3D12DescriptorHeap>(pRenderTargetViewHeapRaw, D3D12Releaser<ID3D12DescriptorHeap>);
            m_bufferIndex = m_pDXGISwapChain->GetCurrentBackBufferIndex();
        }

        virtual ~DrawingRawSwapChain_D3D12() = default;

        std::shared_ptr<IDXGISwapChain3> GetSwapChain() const
        {
            return m_pDXGISwapChain;
        }

        ETargetType GetTargetType() const override
        {
            return eTarget_SwapChain;
        }

        HRESULT Present(uint32_t syncInterval)
        {
            if (m_pDXGISwapChain != nullptr)
            {
                m_pDXGISwapChain->Present(syncInterval, 0);
                m_bufferIndex == 0 ? m_bufferIndex = 1 : m_bufferIndex = 0;
                return S_OK;
            }

            return S_FALSE;
        }

    private:
        std::shared_ptr<IDXGISwapChain3> m_pDXGISwapChain;
        std::shared_ptr<ID3D12Resource> m_pTarget2;
    };

    class DrawingRawCommandList_D3D12 : public DrawingRawCommandList
    {
    public:
        DrawingRawCommandList_D3D12(std::shared_ptr<DrawingDevice_D3D12> pDevice, uint32_t index, D3D12_COMMAND_LIST_TYPE type, std::shared_ptr<ID3D12CommandAllocator> pAllocator) : m_pDevice(pDevice)
        {
            ID3D12GraphicsCommandList* pGraphicsCommandListRaw = nullptr;
            HRESULT hr = m_pDevice->GetDevice()->CreateCommandList(index, type, pAllocator.get(), nullptr, IID_PPV_ARGS(&pGraphicsCommandListRaw));
            assert(SUCCEEDED(hr));
            m_pGraphicsCommandList = std::shared_ptr<ID3D12GraphicsCommandList>(pGraphicsCommandListRaw, D3D12Releaser<ID3D12GraphicsCommandList>);
        }

        std::shared_ptr<ID3D12GraphicsCommandList> GetCommandList() const
        {
            return m_pGraphicsCommandList;
        }

    private:
        std::shared_ptr<DrawingDevice_D3D12> m_pDevice;
        std::shared_ptr<ID3D12GraphicsCommandList> m_pGraphicsCommandList;
    };
}