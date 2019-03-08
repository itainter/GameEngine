#pragma once

#include <d3d12.h>

namespace Engine
{
    class DrawingToD3DEnum_D3D12
    {
    public:
        DXGI_SWAP_EFFECT operator[](EDrawingSwapChainType type) const
        {
            switch (type)
            {
            case eSwapChain_Discard:
                return DXGI_SWAP_EFFECT_FLIP_DISCARD;
            case eSwapChain_Seq:
                return DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
            }
            return DXGI_SWAP_EFFECT_FLIP_DISCARD;
        }

        DXGI_FORMAT operator[](EDrawingFormatType format) const
        {
            switch (format)
            {
            case eFormat_Unknown:
                return DXGI_FORMAT_UNKNOWN;
            case eFormat_D24S8:
            case eFormat_D24X8:
                return DXGI_FORMAT_D24_UNORM_S8_UINT;
            case eFormat_D32_FLOAT:
                return DXGI_FORMAT_D32_FLOAT;
            case eFormat_R8_UNORM:
                return DXGI_FORMAT_R8_UNORM;
            case eFormat_R8_SNORM:
                return DXGI_FORMAT_R8_SNORM;
            case eFormat_R8_UINT:
                return DXGI_FORMAT_R8_UINT;
            case eFormat_R8_SINT:
                return DXGI_FORMAT_R8_SINT;
            case eFormat_R32_FLOAT:
                return DXGI_FORMAT_R32_FLOAT;
            case eFormat_R32_UINT:
                return DXGI_FORMAT_R32_UINT;
            case eFormat_R32_SINT:
                return DXGI_FORMAT_R32_SINT;
            case eFormat_R32G32_FLOAT:
                return DXGI_FORMAT_R32G32_FLOAT;
            case eFormat_R32G32_UINT:
                return DXGI_FORMAT_R32G32_UINT;
            case eFormat_R32G32_SINT:
                return DXGI_FORMAT_R32G32_SINT;
            case eFormat_R8G8B8A8_UNORM:
                return DXGI_FORMAT_R8G8B8A8_UNORM;
            case eFormat_R8G8B8A8_SNORM:
                return DXGI_FORMAT_R8G8B8A8_SNORM;
            case eFormat_R8G8B8A8_UINT:
                return DXGI_FORMAT_R8G8B8A8_UINT;
            case eFormat_R8G8B8A8_SINT:
                return DXGI_FORMAT_R8G8B8A8_SINT;
            case eFormat_R32G32B32_FLOAT:
                return DXGI_FORMAT_R32G32B32_FLOAT;
            case eFormat_R32G32B32_UINT:
                return DXGI_FORMAT_R32G32B32_UINT;
            case eFormat_R32G32B32_SINT:
                return DXGI_FORMAT_R32G32B32_SINT;
            case eFormat_R32G32B32A32_FLOAT:
                return DXGI_FORMAT_R32G32B32A32_FLOAT;
            case eFormat_R32G32B32A32_UINT:
                return DXGI_FORMAT_R32G32B32A32_UINT;
            case eFormat_R32G32B32A32_SINT:
                return DXGI_FORMAT_R32G32B32A32_SINT;
            }
            return DXGI_FORMAT_UNKNOWN;
        }

        D3D12_COMMAND_LIST_TYPE operator[](EDrawingCommandListType type) const
        {
            switch (type)
            {
            case eCommandList_Direct:
                return D3D12_COMMAND_LIST_TYPE_DIRECT;
            case eCommandList_Bundle:
                return D3D12_COMMAND_LIST_TYPE_BUNDLE;
            case eCommandList_Compute:
                return D3D12_COMMAND_LIST_TYPE_COMPUTE;
            case eCommandList_Copy:
                return D3D12_COMMAND_LIST_TYPE_COPY;
            }
            return D3D12_COMMAND_LIST_TYPE_DIRECT;
        }
    };

    inline const DrawingToD3DEnum_D3D12& D3D12Enum(void)
    {
        const static DrawingToD3DEnum_D3D12 d3dEnum;
        return d3dEnum;
    }

    template<typename T>
    inline auto D3D12Enum(const T& t) -> decltype(D3D12Enum()[t])
    {
        return D3D12Enum()[t];
    }

    template<typename T>
    inline void D3D12Releaser(T* p)
    {
        p->Release();
    }
}