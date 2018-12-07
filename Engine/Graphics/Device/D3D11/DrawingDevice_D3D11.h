#pragma once

#include <d3d11.h>
#include <memory>

#include "DrawingDevice.h"

namespace Engine
{
    class DrawingDevice_D3D11 : public DrawingDevice
    {
    public:
        DrawingDevice_D3D11();
        virtual ~DrawingDevice_D3D11();

        bool CreateVertexFormat(const DrawingVertexFormatDesc& desc, std::shared_ptr<DrawingVertexFormat>& pRes) override;
        bool CreateVertexBuffer(const DrawingVertexBufferDesc& desc, std::shared_ptr<DrawingVertexBuffer>& pRes, const void* pData = nullptr, uint32_t size = 0) override;
        bool CreateIndexBuffer(const DrawingIndexBufferDesc& desc, std::shared_ptr<DrawingIndexBuffer>& pRes, const void* pData = nullptr, uint32_t size = 0) override;
        bool CreateTexture(const DrawingTextureDesc& desc, std::shared_ptr<DrawingTexture>& pRes, const void* pData = nullptr, uint32_t size = 0) override;

        bool CreateBlendState(const DrawingBlendStateDesc& desc, std::shared_ptr<DrawingBlendState>& pRes) override;
        bool CreateDepthState(const DrawingDepthStateDesc& desc, std::shared_ptr<DrawingDepthState>& pRes) override;
        bool CreateRasterState(const DrawingRasterStateDesc& desc, std::shared_ptr<DrawingRasterState>& pRes) override;
        bool CreateSamplerState(const DrawingSamplerStateDesc& desc, std::shared_ptr<DrawingSamplerState>& pRes) override;

        bool CreateVertexShaderFromFile(const DrawingVertexShaderDesc& desc, std::shared_ptr<DrawingVertexShader>& pRes) override;
        bool CreateVertexShaderFromString(const std::string& str, const DrawingVertexShaderDesc& desc, std::shared_ptr<DrawingVertexShader>& pRes) override;
        bool CreatePixelShaderFromFile(const DrawingPixelShaderDesc& desc, std::shared_ptr<DrawingPixelShader>& pRes) override;
        bool CreatePixelShaderFromString(const std::string& str, const DrawingPixelShaderDesc& desc, std::shared_ptr<DrawingPixelShader>& pRes) override;

        bool CreatePrimitiveInfo(const DrawingPrimitiveDesc& desc, std::shared_ptr<DrawingPrimitive>& pRes) override;

        std::shared_ptr<ID3D11Device> GetDevice() const;


    private:
        std::shared_ptr<ID3D11Device> m_pDevice;
    };
}