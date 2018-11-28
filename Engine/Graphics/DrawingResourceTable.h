#pragma once

#include <memory>
#include <stdint.h>

namespace Engine
{
    class DrawingDevice;
    class DrawingResource;
    class DrawingResourceDesc;
    class DrawingResourceFactory
    {
    public:
        DrawingResourceFactory(std::shared_ptr<DrawingDevice> pDevice);
        virtual ~DrawingResourceFactory();

        bool CreateResource(const DrawingResourceDesc& desc, std::shared_ptr<DrawingResource>& pRes, const void* pData = nullptr, uint32_t size = 0) const;

        bool CreateVertexFormat(const DrawingResourceDesc& desc, std::shared_ptr<DrawingResource>& pRes) const;
        bool CreateVertexBuffer(const DrawingResourceDesc& desc, std::shared_ptr<DrawingResource>& pRes, const void* pData = nullptr, uint32_t size = 0) const;
        bool CreateIndexBuffer(const DrawingResourceDesc& desc, std::shared_ptr<DrawingResource>& pRes, const void* pData = nullptr, uint32_t size = 0) const;
        bool CreateTexture(const DrawingResourceDesc& desc, std::shared_ptr<DrawingResource>& pRes, const void* pData = nullptr, uint32_t size = 0) const;

        bool CreateBlendState(const DrawingResourceDesc& desc, std::shared_ptr<DrawingResource>& pRes) const;
        bool CreateDepthState(const DrawingResourceDesc& desc, std::shared_ptr<DrawingResource>& pRes) const;
        bool CreateRasterState(const DrawingResourceDesc& desc, std::shared_ptr<DrawingResource>& pRes) const;
        bool CreateSamplerState(const DrawingResourceDesc& desc, std::shared_ptr<DrawingResource>& pRes) const;

        bool CreateVertexShader(const DrawingResourceDesc& desc, std::shared_ptr<DrawingResource>& pRes) const;
        bool CreatePixelShader(const DrawingResourceDesc& desc, std::shared_ptr<DrawingResource>& pRes) const;

        bool CreatePrimitiveInfo(const DrawingResourceDesc& desc, std::shared_ptr<DrawingResource>& pRes) const;

    private:
        std::shared_ptr<DrawingDevice> m_pDevice;
    };

    class DrawingResourceTable
    {
    public:
        DrawingResourceTable(const DrawingResourceFactory& factory);
        virtual ~DrawingResourceTable();

        class ResourceEntry
        {
        public:
            bool CreateResource();

            std::shared_ptr<DrawingResource> GetResource();
            const std::shared_ptr<DrawingResourceDesc> GetDesc() const;

            void SetDesc(std::shared_ptr<DrawingResourceDesc> pDesc);

        private:
            ResourceEntry(const DrawingResourceDesc& desc, const DrawingResourceFactory& factory, DrawingResourceTable& table);
            virtual ~ResourceEntry();

        private:
            std::shared_ptr<DrawingResourceDesc> m_pDesc;
            std::shared_ptr<DrawingResource> m_pRes;

            const void* m_pData;
            uint32_t m_size;

            const DrawingResourceFactory& m_factory;
        };
    };
}