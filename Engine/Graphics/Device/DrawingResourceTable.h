#pragma once

#include <memory>
#include <stdint.h>
#include <unordered_map>

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

        bool CreateResource(const std::shared_ptr<DrawingResourceDesc>& pDesc, std::shared_ptr<DrawingResource>& pRes, const void* pData = nullptr, uint32_t size = 0) const;

        bool CreateVertexFormat(const std::shared_ptr<DrawingResourceDesc>& pDesc, std::shared_ptr<DrawingResource>& pRes) const;
        bool CreateVertexBuffer(const std::shared_ptr<DrawingResourceDesc>& pDesc, std::shared_ptr<DrawingResource>& pRes, const void* pData = nullptr, uint32_t size = 0) const;
        bool CreateIndexBuffer(const std::shared_ptr<DrawingResourceDesc>& pDesc, std::shared_ptr<DrawingResource>& pRes, const void* pData = nullptr, uint32_t size = 0) const;
        bool CreateTexture(const std::shared_ptr<DrawingResourceDesc>& pDesc, std::shared_ptr<DrawingResource>& pRes, const void* pData = nullptr, uint32_t size = 0) const;

        bool CreateBlendState(const std::shared_ptr<DrawingResourceDesc>& pDesc, std::shared_ptr<DrawingResource>& pRes) const;
        bool CreateDepthState(const std::shared_ptr<DrawingResourceDesc>& pDesc, std::shared_ptr<DrawingResource>& pRes) const;
        bool CreateRasterState(const std::shared_ptr<DrawingResourceDesc>& pDesc, std::shared_ptr<DrawingResource>& pRes) const;
        bool CreateSamplerState(const std::shared_ptr<DrawingResourceDesc>& pDesc, std::shared_ptr<DrawingResource>& pRes) const;

        bool CreateVertexShader(const std::shared_ptr<DrawingResourceDesc>& pDesc, std::shared_ptr<DrawingResource>& pRes) const;
        bool CreatePixelShader(const std::shared_ptr<DrawingResourceDesc>& pDesc, std::shared_ptr<DrawingResource>& pRes) const;

        bool CreatePrimitiveInfo(const std::shared_ptr<DrawingResourceDesc>& pDesc, std::shared_ptr<DrawingResource>& pRes) const;

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
            friend class DrawingResourceTable;
        public:
            virtual ~ResourceEntry();
            bool CreateResource();

            std::shared_ptr<DrawingResource> GetResource();
            const std::shared_ptr<DrawingResourceDesc> GetDesc() const;

            void SetDesc(std::shared_ptr<DrawingResourceDesc> pDesc);

        private:
            ResourceEntry(std::shared_ptr<DrawingResourceDesc> pDesc, const DrawingResourceFactory& factory, DrawingResourceTable& table);

        private:
            std::shared_ptr<DrawingResourceDesc> m_pDesc;
            std::shared_ptr<DrawingResource> m_pRes;

            const void* m_pData;
            uint32_t m_size;

            const DrawingResourceFactory& m_factory;
        };

        std::shared_ptr<ResourceEntry> GetResourceEntry(std::shared_ptr<std::string> pName) const;
        bool AddResourceEntry(std::shared_ptr<std::string> pName, std::shared_ptr<DrawingResourceDesc> pDesc);
        bool RemoveResourceEntry(std::shared_ptr<std::string> pName);
        void ClearResourceEntries();
        bool BuildResources();

    private:
        typedef std::unordered_map<std::shared_ptr<std::string>, std::shared_ptr<ResourceEntry>> ResourceTableType;
        ResourceTableType m_resourceTable;
        const DrawingResourceFactory& m_factory;
    };
}