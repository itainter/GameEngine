#pragma once

#include <d3d11.h>

#include "DrawingConstants.h"

namespace Engine
{
    class DrawingToD3DEnum
    {
    public:
        DXGI_FORMAT operator[](EDrawingFormatType format) const
        {
            switch(format)
            {
            case eFormat_Unknown:
                return DXGI_FORMAT_UNKNOWN;
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

        DXGI_USAGE operator[](EDrawingUsageType usage) const
        {
            switch(usage)
            {
            case eUsage_Default:
                return D3D11_USAGE_DEFAULT;
            case eUsage_Dynamic:
                return D3D11_USAGE_DYNAMIC;
            case eUsage_Staging:
                return D3D11_USAGE_STAGING;
            case eUsage_Immutable:
                return D3D11_USAGE_IMMUTABLE;
            }
            return D3D11_USAGE_DEFAULT;
        }

        UINT operator[](EDrawingAccessType access) const
        {
            switch(access)
            {
            case eAccess_No_Access:
                return 0;
            case eAccess_Read:
                return D3D11_CPU_ACCESS_READ;
            case eAccess_Write:
                return D3D11_CPU_ACCESS_WRITE;
            case eAccess_RW:
                return D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
            }
            return eAccess_No_Access;
        }

        D3D11_BLEND operator[](EDrawingBlendType blend) const
        {
            switch(blend)
            {
            case eBlend_Zero:
                return D3D11_BLEND_ZERO;
            case eBlend_One:
                return D3D11_BLEND_ONE;
            case eBlend_SrcColor:
                return D3D11_BLEND_SRC_COLOR;
            case eBlend_InvSrcColor:
                return D3D11_BLEND_INV_SRC_COLOR;
            case eBlend_SrcAlpha:
                return D3D11_BLEND_SRC_ALPHA;
            case eBlend_InvSrcAlpha:
                return D3D11_BLEND_INV_SRC_ALPHA;
            case eBlend_DstAlpha:
                return D3D11_BLEND_DEST_ALPHA;
            case eBlend_InvDstAlpha:
                return D3D11_BLEND_INV_DEST_ALPHA;
            case eBlend_DstColor:
                return D3D11_BLEND_DEST_COLOR;
            case eBlend_InvDstColor:
                return D3D11_BLEND_INV_DEST_COLOR;
            case eBlend_SrcAlphaSat:
                return D3D11_BLEND_SRC_ALPHA_SAT;
            case eBlend_BlendFactor:
                return D3D11_BLEND_BLEND_FACTOR;
            case eBlend_InvBlendFactor:
                return D3D11_BLEND_INV_BLEND_FACTOR;
            case eBlend_Src1Color:
                return D3D11_BLEND_SRC1_COLOR;
            case eBlend_InvSrc1Color:
                return D3D11_BLEND_INV_SRC1_COLOR;
            case eBlend_Src1Alpha:
                return D3D11_BLEND_SRC1_ALPHA;
            case eBlend_InvSrc1Alpha:
                return D3D11_BLEND_INV_SRC1_ALPHA;
            }
            return D3D11_BLEND_ZERO;
        }
    };

    inline const DrawingToD3DEnum& D3D11Enum(void)
    {
        const static DrawingToD3DEnum d3dEnum;
        return d3dEnum;
    }

    template<typename T>
    inline auto D3D11Enum(const T& t) -> decltype(D3D11Enum()[t])
    {
        return D3D11Enum()[t];
    }
}