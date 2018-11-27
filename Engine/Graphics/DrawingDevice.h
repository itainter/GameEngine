
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

    class DrawingDevice
    {
    public:
        DrawingDevice() = default;
        virtual ~DrawingDevice() = default;

        virtual bool CreateBlendState();
    };
}