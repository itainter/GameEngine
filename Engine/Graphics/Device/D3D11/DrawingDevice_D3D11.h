#pragma once

#include <d3d11.h>
#include <dxgi.h>
#include <memory>

#include "DrawingDevice.h"

namespace Engine
{
    class DrawingRawVertexShader_D3D11;
    class DrawingRawPixelShader_D3D11;
    class DrawingDevice_D3D11 : public DrawingDevice
    {
    public:
        DrawingDevice_D3D11();
        virtual ~DrawingDevice_D3D11();

        bool CreateVertexFormat(const DrawingVertexFormatDesc& desc, std::shared_ptr<DrawingVertexFormat>& pRes) override;
        bool CreateVertexBuffer(const DrawingVertexBufferDesc& desc, std::shared_ptr<DrawingVertexBuffer>& pRes, std::shared_ptr<DrawingResource> pRefRes, const void* pData = nullptr, uint32_t size = 0) override;
        bool CreateIndexBuffer(const DrawingIndexBufferDesc& desc, std::shared_ptr<DrawingIndexBuffer>& pRes, std::shared_ptr<DrawingResource> pRefRes, const void* pData = nullptr, uint32_t size = 0) override;
        bool CreateTexture(const DrawingTextureDesc& desc, std::shared_ptr<DrawingTexture>& pRes, const void* pData = nullptr, uint32_t size = 0) override;

        bool CreateBlendState(const DrawingBlendStateDesc& desc, std::shared_ptr<DrawingBlendState>& pRes) override;
        bool CreateDepthState(const DrawingDepthStateDesc& desc, std::shared_ptr<DrawingDepthState>& pRes) override;
        bool CreateRasterState(const DrawingRasterStateDesc& desc, std::shared_ptr<DrawingRasterState>& pRes) override;
        bool CreateSamplerState(const DrawingSamplerStateDesc& desc, std::shared_ptr<DrawingSamplerState>& pRes) override;

        bool CreateVertexShaderFromFile(const DrawingVertexShaderDesc& desc, std::shared_ptr<DrawingVertexShader>& pRes) override;
        bool CreateVertexShaderFromString(const std::string& str, const DrawingVertexShaderDesc& desc, std::shared_ptr<DrawingVertexShader>& pRes) override;
        bool CreatePixelShaderFromFile(const DrawingPixelShaderDesc& desc, std::shared_ptr<DrawingPixelShader>& pRes) override;
        bool CreatePixelShaderFromString(const std::string& str, const DrawingPixelShaderDesc& desc, std::shared_ptr<DrawingPixelShader>& pRes) override;

        bool DrawPrimitive(std::shared_ptr<DrawingPrimitive> pRes) override;
        bool Present(const std::shared_ptr<DrawingTarget> pTarget, uint32_t syncInterval) override;

        std::shared_ptr<ID3D11Device> GetDevice() const;
        std::shared_ptr<IDXGIFactory> GetDXGIFactory() const;

        template<typename DescType>
        static uint32_t GetParamType(const DescType& type, uint32_t& size);

    private:
        bool DoCreateVertexShader(const DrawingVertexShaderDesc& desc, const void* pData, uint32_t size, std::shared_ptr<DrawingVertexShader>& pRes);
        bool DoCreatePixelShader(const DrawingPixelShaderDesc& desc, const void* pData, uint32_t size, std::shared_ptr<DrawingPixelShader>& pRes);

        std::shared_ptr<DrawingRawVertexShader_D3D11> CreateVertexShaderFromBuffer(std::shared_ptr<std::string> pName, std::shared_ptr<std::string> pEntryName, std::shared_ptr<std::string> pSourceName, const void* pData, uint32_t size);
        std::shared_ptr<DrawingRawPixelShader_D3D11> CreatePixelShaderFromBuffer(std::shared_ptr<std::string> pName, std::shared_ptr<std::string> pEntryName, std::shared_ptr<std::string> pSourceName, const void* pData, uint32_t size);

        std::shared_ptr<DrawingRawVertexShader_D3D11> CreateVertexShaderFromBlob(std::shared_ptr<std::string> pName, const void* pShaderByteCode, uint32_t length);
        std::shared_ptr<DrawingRawPixelShader_D3D11> CreatePixelShaderFromBlob(std::shared_ptr<std::string> pName, const void* pShaderByteCode, uint32_t length);

        std::shared_ptr<DrawingRawVertexShader_D3D11> CreateVertexShaderFromString(std::shared_ptr<std::string> pName, std::shared_ptr<std::string> pEntryName, std::shared_ptr<std::string> pSourceName, const char* pSrc, uint32_t size);
        std::shared_ptr<DrawingRawPixelShader_D3D11> CreatePixelShaderFromString(std::shared_ptr<std::string> pName, std::shared_ptr<std::string> pEntryName, std::shared_ptr<std::string> pSourceName, const char* pSrc, uint32_t size);

    private:
        std::shared_ptr<ID3D11Device> m_pDevice;
        std::shared_ptr<ID3D11DeviceContext> m_pDeviceContext;
        std::shared_ptr<IDXGIFactory> m_pDXGIFactory;
    };
}