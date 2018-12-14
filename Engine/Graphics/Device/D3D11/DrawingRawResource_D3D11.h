#pragma once

#include <vector>
#include <unordered_map>
#include <array>
#include <string>
#include <assert.h>
#include <d3d11.h>
#include <dxgi.h>
#include <d3d11shader.h>

#include "DrawingDevice_D3D11.h"
#include "DrawingRawResource.h"

namespace Engine
{
    class DrawingRawBlendState_D3D11 : public DrawingRawBlendState
    {
    public:
        DrawingRawBlendState_D3D11(const DrawingDevice_D3D11& device, const D3D11_BLEND_DESC& desc) : m_device(device)
        {
            auto pRaw = m_pBlendState.get();
            HRESULT hr = m_device.GetDevice()->CreateBlendState(&desc, &pRaw);
            assert(SUCCEEDED(hr));
        }

        std::shared_ptr<ID3D11BlendState> Get() const
        {
            return m_pBlendState;
        }

    private:
        const DrawingDevice_D3D11& m_device;
        std::shared_ptr<ID3D11BlendState> m_pBlendState;
    };

    class DrawingRawDepthState_D3D11 : public DrawingRawDepthState
    {
    public:
        DrawingRawDepthState_D3D11(const DrawingDevice_D3D11& device, const D3D11_DEPTH_STENCIL_DESC& desc) : m_device(device)
        {
            auto pRaw = m_pDepthState.get();
            HRESULT hr = m_device.GetDevice()->CreateDepthStencilState(&desc, &pRaw);
            assert(SUCCEEDED(hr));
        }

        std::shared_ptr<ID3D11DepthStencilState> Get() const
        {
            return m_pDepthState;
        }

    private:
        const DrawingDevice_D3D11& m_device;
        std::shared_ptr<ID3D11DepthStencilState> m_pDepthState;
    };

    class DrawingRawRasterState_D3D11 : public DrawingRawRasterState
    {
    public:
        DrawingRawRasterState_D3D11(const DrawingDevice_D3D11& device, const D3D11_RASTERIZER_DESC& desc) : m_device(device)
        {
            auto pRaw = m_pRasterState.get();
            HRESULT hr = m_device.GetDevice()->CreateRasterizerState(&desc, &pRaw);
            assert(SUCCEEDED(hr));
        }

        std::shared_ptr<ID3D11RasterizerState> Get() const
        {
            return m_pRasterState;
        }

    private:
        const DrawingDevice_D3D11& m_device;
        std::shared_ptr<ID3D11RasterizerState> m_pRasterState;
    };

    class DrawingRawSamplerState_D3D11 : public DrawingRawSamplerState
    {
    public:
        DrawingRawSamplerState_D3D11(const DrawingDevice_D3D11& device, const D3D11_SAMPLER_DESC& desc) : m_device(device)
        {
            auto pRaw = m_pSamplerState.get();
            HRESULT hr = m_device.GetDevice()->CreateSamplerState(&desc, &pRaw);
            assert(SUCCEEDED(hr));
        }

        std::shared_ptr<ID3D11SamplerState> Get() const
        {
            return m_pSamplerState;
        }

    private:
        const DrawingDevice_D3D11& m_device;
        std::shared_ptr<ID3D11SamplerState> m_pSamplerState;
    };

    class DrawingRawTexture_D3D11 : public DrawingRawTexture
    {
    public:
        typedef ID3D11Resource TextureType;
        DrawingRawTexture_D3D11(const DrawingDevice_D3D11& device, uint32_t sizeInBytes = 0, uint32_t startOffset = 0) : m_device(device), m_sizeInBytes(sizeInBytes), m_startOffset(startOffset) {}
        DrawingRawTexture_D3D11(const DrawingDevice_D3D11& device, std::shared_ptr<ID3D11ShaderResourceView> pShaderResourceView, uint32_t sizeInBytes = 0, uint32_t startOffset = 0) :
            m_device(device), m_pShaderResourceView(pShaderResourceView), m_sizeInBytes(sizeInBytes), m_startOffset(startOffset) {}

        std::shared_ptr<ID3D11ShaderResourceView> GetShaderResourceView() const
        {
            return m_pShaderResourceView;
        }

        virtual TextureType* GetBuffer() const = 0;

    protected:
        uint32_t m_sizeInBytes;
        uint32_t m_startOffset;
        const DrawingDevice_D3D11& m_device;
        std::shared_ptr<ID3D11ShaderResourceView> m_pShaderResourceView; 
    };

    class DrawingRawTexture1D_D3D11 : public DrawingRawTexture_D3D11
    {
    public:
        typedef ID3D11Texture1D TextureType;
        DrawingRawTexture1D_D3D11(const DrawingDevice_D3D11& device, const D3D11_TEXTURE1D_DESC& desc, const D3D11_SUBRESOURCE_DATA& data) : DrawingRawTexture_D3D11(device, desc.Width)
        {
            auto pTextureRaw = m_pTexture1D.get();
            HRESULT hr = m_device.GetDevice()->CreateTexture1D(&desc, &data, &pTextureRaw);
            assert(SUCCEEDED(hr));

            auto pResourceViewRaw = m_pShaderResourceView.get();
            hr = m_device.GetDevice()->CreateShaderResourceView(pTextureRaw, nullptr, &pResourceViewRaw);
            assert(SUCCEEDED(hr));
        }

        TextureType* GetBuffer() const override
        {
            return m_pTexture1D.get();
        }

    private:
        std::shared_ptr<TextureType> m_pTexture1D;
    };

    class DrawingRawTexture2D_D3D11 : public DrawingRawTexture_D3D11
    {
    public:
        typedef ID3D11Texture2D TextureType;
        DrawingRawTexture2D_D3D11(const DrawingDevice_D3D11& device, const D3D11_TEXTURE2D_DESC& desc, const D3D11_SUBRESOURCE_DATA& data) : DrawingRawTexture_D3D11(device, desc.Width)
        {
            auto pTextureRaw = m_pTexture2D.get();
            HRESULT hr = m_device.GetDevice()->CreateTexture2D(&desc, &data, &pTextureRaw);
            assert(SUCCEEDED(hr));

            auto pResourceViewRaw = m_pShaderResourceView.get();
            hr = m_device.GetDevice()->CreateShaderResourceView(pTextureRaw, nullptr, &pResourceViewRaw);
            assert(SUCCEEDED(hr));
        }

        TextureType* GetBuffer() const override
        {
            return m_pTexture2D.get();
        }

    private:
        std::shared_ptr<TextureType> m_pTexture2D;
    };

    class DrawingRawTexture3D_D3D11 : public DrawingRawTexture_D3D11
    {
    public:
        typedef ID3D11Texture3D TextureType;
        DrawingRawTexture3D_D3D11(const DrawingDevice_D3D11& device, const D3D11_TEXTURE3D_DESC& desc, const D3D11_SUBRESOURCE_DATA& data) : DrawingRawTexture_D3D11(device, desc.Width)
        {
            auto pTextureRaw = m_pTexture3D.get();
            HRESULT hr = m_device.GetDevice()->CreateTexture3D(&desc, &data, &pTextureRaw);
            assert(SUCCEEDED(hr));

            auto pResourceViewRaw = m_pShaderResourceView.get();
            hr = m_device.GetDevice()->CreateShaderResourceView(pTextureRaw, nullptr, &pResourceViewRaw);
            assert(SUCCEEDED(hr));
        }

        TextureType* GetBuffer() const override
        {
            return m_pTexture3D.get();
        }

    private:
        std::shared_ptr<TextureType> m_pTexture3D;
    };

    class DrawingRawShader_D3D11
    {
    public:
        DrawingRawShader_D3D11(const DrawingDevice_D3D11& device, std::shared_ptr<ID3D11ShaderReflection> pReflection) : m_device(device), m_pReflection(pReflection) {}
        virtual ~DrawingRawShader_D3D11()
        {
            mCBTable.clear();
            mTextureTable.clear();
            mTexBufferTable.clear();
            mUVATable.clear();
            mSamplerTable.clear();

            mVariableTable.clear();

            m_pReflection = nullptr;
        }

        struct ShaderResourceDesc
        {
            ShaderResourceDesc() : mpName(nullptr), mStartSlot(0), mCount(0), mSizeInBytes(0) {}

            std::shared_ptr<std::string> mpName;

            uint32_t mStartSlot;
            uint32_t mCount;
            uint32_t mSizeInBytes;
        };

        struct VariableDesc
        {
            VariableDesc() : mpName(nullptr), mpCBName(nullptr), mOffset(0), mSizeInBytes(0), mCBSizeInBytes(0), mParamType(0) {}

            std::shared_ptr<std::string> mpName;
            std::shared_ptr<std::string> mpCBName;

            uint32_t mOffset;
            uint32_t mSizeInBytes;
            uint32_t mCBSizeInBytes;
            uint32_t mParamType;
        };

        typedef std::unordered_map<std::shared_ptr<std::string>, ShaderResourceDesc> ShaderResourceTableType;
        typedef std::unordered_map<std::shared_ptr<std::string>, VariableDesc> VariableTableType;

        const ShaderResourceTableType& GetConstanceBufferTable() const
        {
            return mCBTable;
        }

        const ShaderResourceTableType& GetTextureTable() const
        {
            return mTextureTable;
        }

        const ShaderResourceTableType& GetTexBufferTable() const
        {
            return mTexBufferTable;
        }

        const ShaderResourceTableType& GetUVATable() const
        {
            return mUVATable;
        }

        const ShaderResourceTableType& GetSamplerTable() const
        {
            return mSamplerTable;
        }

        const VariableTableType& GetVariableTable() const
        {
            return mVariableTable;
        }

        void BuildResourceBindingTable(DrawingRawShader::DrawingRawShaderType type);

    private:
        void ProcessVariables(std::shared_ptr<std::string> pName, uint32_t size, ID3D11ShaderReflectionConstantBuffer* pBuffer, uint32_t count);

    protected:
        const DrawingDevice_D3D11& m_device;
        std::shared_ptr<ID3D11ShaderReflection> m_pReflection; 

        ShaderResourceTableType mCBTable;
        ShaderResourceTableType mTextureTable;
        ShaderResourceTableType mTexBufferTable;
        ShaderResourceTableType mUVATable;
        ShaderResourceTableType mSamplerTable;

        VariableTableType mVariableTable;
    };

    class DrawingRawVertexShader_D3D11 : public DrawingRawVertexShader
    {
    public:
        typedef ID3D11VertexShader ShaderType;
        DrawingRawVertexShader_D3D11(const DrawingDevice_D3D11& device, std::shared_ptr<const std::string> pShaderName, std::shared_ptr<ID3D11ShaderReflection> pReflection, std::shared_ptr<ShaderType> pShader) :
            DrawingRawVertexShader(pShaderName), m_pShader(pShader), m_pShaderImpl(new DrawingRawShader_D3D11(device, pReflection))
        {
            assert(m_pShaderImpl != nullptr);
            m_pShaderImpl->BuildResourceBindingTable(GetShaderType());
        }

        virtual ~DrawingRawVertexShader_D3D11()
        {
            m_pShader = nullptr;
            m_pShaderImpl = nullptr;
        }

        ShaderType* GetShader() const
        {
            return m_pShader.get();
        }

        DrawingRawShader_D3D11* GetShaderImpl() const
        {
            return m_pShaderImpl.get();
        }

        const DrawingRawShader_D3D11::ShaderResourceTableType& GetConstanceBufferTable() const
        {
            return m_pShaderImpl->GetConstanceBufferTable();
        }

        const DrawingRawShader_D3D11::ShaderResourceTableType& GetTextureTable() const
        {
            return m_pShaderImpl->GetTextureTable();
        }

        const DrawingRawShader_D3D11::ShaderResourceTableType& GetTexBufferTable() const
        {
            return m_pShaderImpl->GetTexBufferTable();
        }

        const DrawingRawShader_D3D11::ShaderResourceTableType& GetUVATable() const
        {
            return m_pShaderImpl->GetUVATable();
        }

        const DrawingRawShader_D3D11::ShaderResourceTableType& GetSamplerTable() const
        {
            return m_pShaderImpl->GetSamplerTable();
        }

        const DrawingRawShader_D3D11::VariableTableType& GetVariableTable() const
        {
            return m_pShaderImpl->GetVariableTable();
        }

    private:
        std::shared_ptr<ShaderType> m_pShader;
        std::shared_ptr<DrawingRawShader_D3D11> m_pShaderImpl;
    };

    class DrawingRawPixelShader_D3D11 : public DrawingRawPixelShader
    {
    public:
        typedef ID3D11PixelShader ShaderType;
        DrawingRawPixelShader_D3D11(const DrawingDevice_D3D11& device, std::shared_ptr<const std::string> pShaderName, std::shared_ptr<ID3D11ShaderReflection> pReflection, std::shared_ptr<ShaderType> pShader) :
            DrawingRawPixelShader(pShaderName), m_pShader(pShader), m_pShaderImpl(new DrawingRawShader_D3D11(device, pReflection))
        {
            assert(m_pShaderImpl != nullptr);
            m_pShaderImpl-> BuildResourceBindingTable(GetShaderType());
        }

        virtual ~DrawingRawPixelShader_D3D11()
        {
            m_pShader = nullptr;
            m_pShaderImpl = nullptr;
        }

        ShaderType* GetShader() const
        {
            return m_pShader.get();
        }

        DrawingRawShader_D3D11* GetShaderImpl() const
        {
            return m_pShaderImpl.get();
        }

        const DrawingRawShader_D3D11::ShaderResourceTableType& GetConstanceBufferTable() const
        {
            return m_pShaderImpl->GetConstanceBufferTable();
        }

        const DrawingRawShader_D3D11::ShaderResourceTableType& GetTextureTable() const
        {
            return m_pShaderImpl->GetTextureTable();
        }

        const DrawingRawShader_D3D11::ShaderResourceTableType& GetTexBufferTable() const
        {
            return m_pShaderImpl->GetTexBufferTable();
        }

        const DrawingRawShader_D3D11::ShaderResourceTableType& GetUVATable() const
        {
            return m_pShaderImpl->GetUVATable();
        }

        const DrawingRawShader_D3D11::ShaderResourceTableType& GetSamplerTable() const
        {
            return m_pShaderImpl->GetSamplerTable();
        }

        const DrawingRawShader_D3D11::VariableTableType& GetVariableTable() const
        {
            return m_pShaderImpl->GetVariableTable();
        }

    private:
        std::shared_ptr<ShaderType> m_pShader;
        std::shared_ptr<DrawingRawShader_D3D11> m_pShaderImpl;
    };

    class DrawingRawEffect_D3D11 : public DrawingRawEffect
    {
    public:
        DrawingRawEffect_D3D11(const DrawingDevice_D3D11& device, std::shared_ptr<const std::string> pEffectName) :
            DrawingRawEffect(pEffectName), m_device(device), m_pInputSignature(nullptr), m_byteCodeLength(0) {}

        const void* GetInputSignature() const
        {
            return m_pInputSignature;
        }

        uint32_t GetByteCodeLength() const
        {
            return m_byteCodeLength;
        }

    private:
        const DrawingDevice_D3D11& m_device;
        const void* m_pInputSignature;
        uint32_t m_byteCodeLength;
    };

    class DrawingRawShaderEffect_D3D11 : public DrawingRawEffect_D3D11
    {
    public:
        DrawingRawShaderEffect_D3D11(const DrawingDevice_D3D11& device, std::shared_ptr<const std::string> pEffectName, const std::vector<std::shared_ptr<DrawingRawShader>>& shaders);
        DrawingRawShaderEffect_D3D11(const DrawingDevice_D3D11& device, std::shared_ptr<const std::string> pEffectName, std::shared_ptr<DrawingRawVertexShader_D3D11> pVertexShader, std::shared_ptr<DrawingRawPixelShader_D3D11> pPixelShader);

        void Apply() override;
        void Terminate() override;

    private:
        struct ShaderBlock
        {
            std::shared_ptr<DrawingRawShader> mpShader;
            uint32_t mCBSlotsCount;
            uint32_t mSRVSlotsCount;
            uint32_t mSamplerSlotsCount;
            uint32_t mUVASlotsCount;

            std::array<ID3D11Buffer*, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT> mCBSlots;
            std::array<ID3D11ShaderResourceView*, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT> mSRVSlots;
            std::array<ID3D11SamplerState*, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT> mSamplerSlots;
            std::array<ID3D11UnorderedAccessView*, D3D11_PS_CS_UAV_REGISTER_COUNT> mUVASlots;

            ShaderBlock()
            {
                mCBSlotsCount = 0;
                mSRVSlotsCount = 0;
                mSamplerSlotsCount = 0;
                mUVASlotsCount = 0;

                mCBSlots.fill(nullptr);
                mSRVSlots.fill(nullptr);
                mSamplerSlots.fill(nullptr);
                mUVASlots.fill(nullptr);
            }
        };

        std::array<std::shared_ptr<ShaderBlock>, DrawingRawShader::RawShader_Count> m_shaderBlocks;
    };

    class DrawingRawVertexFormat_D3D11 : public DrawingRawVertexFormat
    {
    public:
        DrawingRawVertexFormat_D3D11(const DrawingDevice_D3D11& device, const std::vector<D3D11_INPUT_ELEMENT_DESC>& desc,
                                     const void* pShaderBytecodeWithInputSignature, uint32_t byteCodeLength) : m_device(device)
        {
            auto pRaw = m_pInputLayout.get();
            HRESULT hr = m_device.GetDevice()->CreateInputLayout(desc.data(), static_cast<UINT>(desc.size()), pShaderBytecodeWithInputSignature, byteCodeLength, &pRaw);
            assert(SUCCEEDED(hr));
        }

        std::shared_ptr<ID3D11InputLayout> Get() const
        {
            return m_pInputLayout;
        }

    private:
        const DrawingDevice_D3D11& m_device;
        std::shared_ptr<ID3D11InputLayout> m_pInputLayout;
    };

    class DrawingRawBuffer_D3D11
    {
    public:
        DrawingRawBuffer_D3D11(const DrawingDevice_D3D11& device, const D3D11_BUFFER_DESC& desc, uint32_t stride, uint32_t offset) :
            m_device(device), m_sizeInBytes(desc.ByteWidth), m_stride(stride), m_startOffset(offset)
        {
            auto pRaw = m_pBuffer.get();
            HRESULT hr = m_device.GetDevice()->CreateBuffer(&desc, nullptr, &pRaw);
            assert(SUCCEEDED(hr));
        }

        DrawingRawBuffer_D3D11(const DrawingDevice_D3D11& device, const D3D11_BUFFER_DESC& desc, const D3D11_SUBRESOURCE_DATA& data, uint32_t stride, uint32_t offset) :
            m_device(device), m_sizeInBytes(desc.ByteWidth), m_stride(stride), m_startOffset(offset)
        {
            auto pRaw = m_pBuffer.get();
            HRESULT hr = m_device.GetDevice()->CreateBuffer(&desc, &data, &pRaw);
            assert(SUCCEEDED(hr));
        }

        std::shared_ptr<ID3D11Buffer> Get() const
        {
            return m_pBuffer;
        }

        uint32_t GetSizeInBytes() const
        {
            return m_sizeInBytes;
        }

        uint32_t GetStride() const
        {
            return m_stride;
        }

        uint32_t GetStartOffset() const
        {
            return m_startOffset;
        }

    private:
        const DrawingDevice_D3D11& m_device;
        uint32_t m_sizeInBytes;
        uint32_t m_stride;
        uint32_t m_startOffset;
        std::shared_ptr<ID3D11Buffer> m_pBuffer;
    };

    class DrawingRawVertexBuffer_D3D11 : public DrawingRawVertexBuffer
    {
    public:
        DrawingRawVertexBuffer_D3D11(const DrawingDevice_D3D11& device, const D3D11_BUFFER_DESC& desc, const D3D11_SUBRESOURCE_DATA& data, uint32_t stride, uint32_t offset) :
            m_device(device), m_pBufferImpl(new DrawingRawBuffer_D3D11(device, desc, data, stride, offset)) {}

        DrawingRawBuffer_D3D11* GetBufferImpl()
        {
            return m_pBufferImpl.get();
        }

        uint32_t GetSizeInBytes() const
        {
            return m_pBufferImpl->GetSizeInBytes();
        }

        uint32_t GetStride() const
        {
            return m_pBufferImpl->GetStride();
        }

        uint32_t GetStartOffset() const
        {
            return m_pBufferImpl->GetStartOffset();
        }

    private:
        const DrawingDevice_D3D11& m_device;
        std::shared_ptr<DrawingRawBuffer_D3D11> m_pBufferImpl;
    };

    class DrawingRawIndexBuffer_D3D11 : public DrawingRawIndexBuffer
    {
    public:
        DrawingRawIndexBuffer_D3D11(const DrawingDevice_D3D11& device, const D3D11_BUFFER_DESC& desc, const D3D11_SUBRESOURCE_DATA& data, uint32_t stride, uint32_t offset) :
            m_device(device), m_pBufferImpl(new DrawingRawBuffer_D3D11(device, desc, data, stride, offset)) {}

        DrawingRawBuffer_D3D11* GetBufferImpl()
        {
            return m_pBufferImpl.get();
        }

        uint32_t GetSizeInBytes() const
        {
            return m_pBufferImpl->GetSizeInBytes();
        }

        uint32_t GetStride() const
        {
            return m_pBufferImpl->GetStride();
        }

        uint32_t GetStartOffset() const
        {
            return m_pBufferImpl->GetStartOffset();
        }

        DXGI_FORMAT GetBufferFormat() const
        {
            return (sizeof(uint16_t) == GetStride()) ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT;
        }

    private:
        const DrawingDevice_D3D11& m_device;
        std::shared_ptr<DrawingRawBuffer_D3D11> m_pBufferImpl;
    };

    class DrawingRawTarget_D3D11 : public DrawingRawTarget
    {
    public:
        DrawingRawTarget_D3D11(const DrawingDevice_D3D11& device) : m_device(device) {}

        DrawingRawTarget_D3D11(const DrawingDevice_D3D11& device, const D3D11_TEXTURE2D_DESC& desc) : m_device(device)
        {
            auto pRaw = m_pTarget.get();
            HRESULT hr = m_device.GetDevice()->CreateTexture2D(&desc, nullptr, &pRaw);
            assert(SUCCEEDED(hr));
        }

        virtual ~DrawingRawTarget_D3D11() = default;

        std::shared_ptr<ID3D11Texture2D> GetTarget() const
        {
            return m_pTarget;
        }

        virtual ETargetType GetTargetType() const = 0;

    protected:
        const DrawingDevice_D3D11& m_device;
        std::shared_ptr<ID3D11Texture2D> m_pTarget;
    };

    class DrawingRawFragmentTarget_D3D11 : public DrawingRawTarget_D3D11
    {
    public:
        using DrawingRawTarget_D3D11::DrawingRawTarget_D3D11;
        DrawingRawFragmentTarget_D3D11(const DrawingDevice_D3D11& device, const D3D11_TEXTURE2D_DESC& desc) : DrawingRawTarget_D3D11(device, desc)
        {
            auto pTargetRaw = m_pTarget.get();
            auto pRenderTargetViewRaw = m_pRenderTargetView.get();
            HRESULT hr = m_device.GetDevice()->CreateRenderTargetView(pTargetRaw, nullptr, &pRenderTargetViewRaw);
            assert(SUCCEEDED(hr));
        }

        std::shared_ptr<ID3D11RenderTargetView> GetRenderTargetView() const
        {
            return m_pRenderTargetView;
        }

    protected:
        std::shared_ptr<ID3D11RenderTargetView> m_pRenderTargetView;
    };

    class DrawingRawRenderTarget_D3D11 : public DrawingRawFragmentTarget_D3D11
    {
    public:
        DrawingRawRenderTarget_D3D11(const DrawingDevice_D3D11& device, const D3D11_TEXTURE2D_DESC& desc) : DrawingRawFragmentTarget_D3D11(device, desc)
        {
            auto pTargetRaw = m_pTarget.get();
            auto pShaderResourceViewRaw = m_pShaderResourceView.get();
            HRESULT hr = m_device.GetDevice()->CreateShaderResourceView(pTargetRaw, nullptr, &pShaderResourceViewRaw);
            assert(SUCCEEDED(hr));
        }

        std::shared_ptr<ID3D11ShaderResourceView> GetShaderResourceView() const
        {
            return m_pShaderResourceView;
        }

        ETargetType GetTargetType() const override
        {
            return eTarget_OffScreen;
        }

    protected:
        std::shared_ptr<ID3D11ShaderResourceView> m_pShaderResourceView;
    };

    class DrawingRawSwapChain_D3D11 : public DrawingRawFragmentTarget_D3D11
    {
    public:
        DrawingRawSwapChain_D3D11(const DrawingDevice_D3D11& device, DXGI_SWAP_CHAIN_DESC& desc) : DrawingRawFragmentTarget_D3D11(device)
        {
            auto pDXGIFactoryRaw = m_pDXGISwapChain.get();
            HRESULT hr = m_device.GetDXGIFactory()->CreateSwapChain(m_device.GetDevice().get(), &desc, &pDXGIFactoryRaw);
            assert(SUCCEEDED(hr));

            auto pTargetRaw = m_pTarget.get();
            hr = m_pDXGISwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pTargetRaw));
            assert(SUCCEEDED(hr));

            auto pRenderTargetViewRaw = m_pRenderTargetView.get();
            hr = m_device.GetDevice()->CreateRenderTargetView(pTargetRaw, nullptr, &pRenderTargetViewRaw);
            assert(SUCCEEDED(hr));
        }

        std::shared_ptr<IDXGISwapChain> GetSwapChain() const
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
                return m_pDXGISwapChain->Present(syncInterval, 0);

            return S_OK;
        }

    private:
        std::shared_ptr<IDXGISwapChain> m_pDXGISwapChain;
    };

    class DrawingRawDepthTarget_D3D11 : public DrawingRawTarget_D3D11
    {
    public:
        DrawingRawDepthTarget_D3D11(const DrawingDevice_D3D11& device, const D3D11_TEXTURE2D_DESC& desc) : DrawingRawTarget_D3D11(device, desc)
        {
            auto pTargetRaw = m_pTarget.get();
            auto pDepthStencilViewRaw = m_pDepthStencilView.get();
            HRESULT hr = m_device.GetDevice()->CreateDepthStencilView(pTargetRaw, nullptr, &pDepthStencilViewRaw);
            assert(SUCCEEDED(hr));
        }

        std::shared_ptr<ID3D11DepthStencilView> GetDepthStencilView()
        {
            return m_pDepthStencilView;
        }

        ETargetType GetTargetType() const override
        {
            return eTarget_Depth;
        }

    private:
        std::shared_ptr<ID3D11DepthStencilView> m_pDepthStencilView;
    };
}