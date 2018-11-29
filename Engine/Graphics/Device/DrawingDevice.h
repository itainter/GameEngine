
#pragma once

#include <memory>
#include <string>

#include "DrawingRawResource.h"
#include "DrawingResourceDesc.h"

namespace Engine
{
    class DrawingDevice;
    class DrawingResource
    {
    public:
        DrawingResource(std::shared_ptr<DrawingDevice> pDevice);
        virtual ~DrawingResource() = default;

        const std::shared_ptr<DrawingDevice>& GetDevice();

        virtual const std::shared_ptr<std::string>& GetName() const;
        virtual void SetName(std::shared_ptr<std::string> name);
        virtual const std::shared_ptr<DrawingResourceDesc>& GetDesc() const;
        virtual void SetDesc(std::shared_ptr<DrawingResourceDesc> desc);

        virtual EDrawingResourceType GetType() const = 0;

    protected:
        std::shared_ptr<DrawingDevice> m_pDevice;
        std::shared_ptr<std::string> m_pName;
        std::shared_ptr<DrawingResourceDesc> m_pDesc;
    };

    template<typename T>
    class DrawingResourceWrapper : public DrawingResource
    {
    public:
        DrawingResourceWrapper(std::shared_ptr<DrawingDevice> pDevice) : DrawingResource(pDevice), m_pRes(nullptr) {}
        virtual ~DrawingResourceWrapper() { m_pRes = nullptr; }

        void SetResource(std::shared_ptr<T> pRes) { m_pRes = pRes; }
        const std::shared_ptr<T>& GetResource() { return m_pRes; }
 
    private:
        std::shared_ptr<T> m_pRes;
    };

    class DrawingTexture : public DrawingResourceWrapper<DrawingRawTexture>
    {
    public:
        DrawingTexture(std::shared_ptr<DrawingDevice> pDevice);
        virtual ~DrawingTexture();

        EDrawingResourceType GetType() const override;
    };

    class DrawingShader : public DrawingResourceWrapper<DrawingRawShader>
    {
    public:
        DrawingShader(std::shared_ptr<DrawingDevice> pDevice);
        virtual ~DrawingShader();
    };

    class DrawingVertexShader : public DrawingShader
    {
    public:
        EDrawingResourceType GetType() const override;
    };

    class DrawingPixelShader : public DrawingShader
    {
    public:
        EDrawingResourceType GetType() const override;
    };

    class DrawingBlendState : public DrawingResourceWrapper<DrawingRawBlendState>
    {
    public:
        DrawingBlendState(std::shared_ptr<DrawingDevice> pDevice);
        virtual ~DrawingBlendState();

        EDrawingResourceType GetType() const override;
    };

    class DrawingDepthState : public DrawingResourceWrapper<DrawingRawDepthState>
    {
    public:
        DrawingDepthState(std::shared_ptr<DrawingDevice> pDevice);
        virtual ~DrawingDepthState();

        EDrawingResourceType GetType() const override;
    };

    class DrawingRasterState : public DrawingResourceWrapper<DrawingRawRasterState>
    {
    public:
        DrawingRasterState(std::shared_ptr<DrawingDevice> pDevice);
        virtual ~DrawingRasterState();

        EDrawingResourceType GetType() const override;
    };

    class DrawingSamplerState : public DrawingResourceWrapper<DrawingRawSamplerState>
    {
    public:
        DrawingSamplerState(std::shared_ptr<DrawingDevice> pDevice);
        virtual ~DrawingSamplerState();

        EDrawingResourceType GetType() const override;
    };

    class DrawingVertexFormat : public DrawingResourceWrapper<DrawingRawVertexFormat>
    {
    public:
        DrawingVertexFormat(std::shared_ptr<DrawingDevice> pDevice);
        virtual ~DrawingVertexFormat();

        EDrawingResourceType GetType() const override;
    };

    class DrawingVertexBuffer : public DrawingResourceWrapper<DrawingRawVertexBuffer>
    {
    public:
        DrawingVertexBuffer(std::shared_ptr<DrawingDevice> pDevice);
        virtual ~DrawingVertexBuffer();

        EDrawingResourceType GetType() const override;
    };

    class DrawingIndexBuffer : public DrawingResourceWrapper<DrawingRawIndexBuffer>
    {
    public:
        DrawingIndexBuffer(std::shared_ptr<DrawingDevice> pDevice);
        virtual ~DrawingIndexBuffer();

        EDrawingResourceType GetType() const override;
    };

    class DrawingTarget : public DrawingResourceWrapper<DrawingRawTarget>
    {
    public:
        DrawingTarget(std::shared_ptr<DrawingDevice> pDevice);
        virtual ~DrawingTarget();

        EDrawingResourceType GetType() const override;
    };

    class DrawingPrimitive : public DrawingResource
    {
    public:
        DrawingPrimitive(std::shared_ptr<DrawingDevice> pDevice);
        virtual ~DrawingPrimitive();

        EDrawingPrimitiveType GetPrimitiveType() const;
        void SetPrimitiveType(EDrawingPrimitiveType type);

        uint32_t GetVertexCount() const;
        void SetVertexCount(uint32_t count);

        uint32_t GetIndexCount() const;
        void SetIndexCount(uint32_t count);

        uint32_t GetInstanceCount() const;
        void SetInstanceCount(uint32_t count);

        uint32_t GetVertexOffset() const;
        void SetVertexOffset(uint32_t offset);

        uint32_t GetIndexOffset() const;
        void SetIndexoffset(uint32_t offset);

        uint32_t GetInstanceOffset() const;
        void SetInstanceOffset(uint32_t offset);

        EDrawingResourceType GetType() const override;

    private:
        EDrawingPrimitiveType m_primitiveType;
        uint32_t m_vertexCount;
        uint32_t m_indexCount;
        uint32_t m_instanceCount;

        uint32_t m_vertexOffset;
        uint32_t m_indexOffset;
        uint32_t m_instanceOffset;
    };

    class DrawingContext
    {
    public:
        DrawingContext(std::shared_ptr<DrawingDevice> pDevice);
        virtual ~DrawingContext();

        std::shared_ptr<DrawingNativeContext> GetNativeContext();
        void SetNativeContext(std::shared_ptr<DrawingNativeContext> context);

        virtual void UpdateResourceTable() = 0;
        virtual void Reset() = 0;
    protected:
        std::shared_ptr<DrawingNativeContext> m_pNativeContext;
        std::shared_ptr<DrawingDevice> m_pDevice;
    };

    class DrawingDevice
    {
    public:
        DrawingDevice() = default;
        virtual ~DrawingDevice() = default;

        virtual bool CreateVertexFormat(const DrawingVertexFormatDesc& desc, std::shared_ptr<DrawingVertexFormat>& pRes) = 0;
        virtual bool CreateVertexBuffer(const DrawingVertexBufferDesc& desc, std::shared_ptr<DrawingVertexBuffer>& pRes, const void* pData = nullptr, uint32_t size = 0) = 0;
        virtual bool CreateIndexBuffer(const DrawingIndexBufferDesc& desc, std::shared_ptr<DrawingIndexBuffer>& pRes, const void* pData = nullptr, uint32_t size = 0) =  0;
        virtual bool CreateTexture(const DrawingTextureDesc& desc, std::shared_ptr<DrawingTexture>& pRes, const void* pData = nullptr, uint32_t size = 0) = 0;

        virtual bool CreateBlendState(const DrawingBlendStateDesc& desc, std::shared_ptr<DrawingBlendState>& pRes) = 0;
        virtual bool CreateDepthState(const DrawingDepthStateDesc& desc, std::shared_ptr<DrawingDepthState>& pRes) = 0;
        virtual bool CreateRasterState(const DrawingRasterStateDesc& desc, std::shared_ptr<DrawingRasterState>& pRes) = 0;
        virtual bool CreateSamplerState(const DrawingSamplerStateDesc& desc, std::shared_ptr<DrawingSamplerState>& pRes) = 0;

        virtual bool CreateVertexShaderFromFile(const DrawingVertexShaderDesc& desc, std::shared_ptr<DrawingVertexShader>& pRes) = 0;
        virtual bool CreateVertexShaderFromString(const std::string& str, const DrawingVertexShaderDesc& desc, std::shared_ptr<DrawingVertexShader>& pRes) = 0;
        virtual bool CreatePixelShaderFromFile(const DrawingPixelShaderDesc& desc, std::shared_ptr<DrawingPixelShader>& pRes) = 0;
        virtual bool CreatePixelShaderFromString(const std::string& str, const DrawingPixelShaderDesc& desc, std::shared_ptr<DrawingPixelShader>& pRes) = 0;

        virtual bool CreatePrimitiveInfo(const DrawingPrimitiveDesc& desc, std::shared_ptr<DrawingPrimitive>& pRes) = 0;
    };
}