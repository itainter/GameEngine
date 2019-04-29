#pragma once

#include <d3d12.h>
#include <deque>
#include <memory>
#include <mutex>

namespace Engine
{
    class DrawingDevice_D3D12;
    class DrawingUploadAllocator_D3D12
    {
    public:
        DrawingUploadAllocator_D3D12(const std::shared_ptr<DrawingDevice_D3D12> device, uint64_t pageSizeInBytes);
        virtual ~DrawingUploadAllocator_D3D12();

        struct Allocation
        {
            Allocation() : pCPUData(nullptr), pGPUAddr(D3D12_GPU_VIRTUAL_ADDRESS(0)) {}
            Allocation(void* CPUData, D3D12_GPU_VIRTUAL_ADDRESS GPUAddr) : pCPUData(CPUData), pGPUAddr(GPUAddr) {}

            void* pCPUData;
            D3D12_GPU_VIRTUAL_ADDRESS pGPUAddr;
        };

        Allocation Allocate(uint64_t sizeInBytes, uint64_t alignment);
        void Reset();

    private:
        struct Page
        {
            Page(const std::weak_ptr<DrawingDevice_D3D12> device, uint64_t sizeInBytes);
            ~Page();

            bool HasEnoughSpace(uint64_t sizeInBytes, uint64_t alignment);
            Allocation Allocate(uint64_t sizeInBytes, uint64_t alignment);
            void Reset();

        private:
            std::weak_ptr<DrawingDevice_D3D12> m_pDevice;
            std::shared_ptr<ID3D12Resource> m_pResource;

            Allocation m_startPtr;
            uint64_t m_offset;
            uint64_t m_sizeInBytes;

            mutable std::mutex m_mutex;
        };

        std::shared_ptr<Page> GetNewPool();

    private:
        typedef std::deque<std::shared_ptr<Page>> PagePool;

        std::weak_ptr<DrawingDevice_D3D12> m_pDevice;

        PagePool m_pagePool;
        PagePool m_pagePoolAvail;

        std::shared_ptr<Page> m_pPageCur;

        uint64_t m_pageSizeInBytes;
    };
}