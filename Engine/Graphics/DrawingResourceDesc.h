#pragma once

#include <stdint.h>
#include <memory>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <string>

#include "DrawingConstants.h"

namespace Engine
{
    class DrawingResourceDesc
    {
    public:
        DrawingResourceDesc() = default;
        DrawingResourceDesc(const DrawingResourceDesc& desc);
        DrawingResourceDesc(const DrawingResourceDesc&& desc);
        virtual ~DrawingResourceDesc();

        DrawingResourceDesc& operator= (const DrawingResourceDesc& rhs);

        virtual EDrawingResourceType GetType() const = 0;
        virtual DrawingResourceDesc* Clone() const = 0;

        typedef std::unordered_map<uint32_t, std::shared_ptr<std::string>> ResourceDescNamesType;

        ResourceDescNamesType GetResourceDescNames() const;
        void AddResourceDescName(uint32_t index, std::shared_ptr<std::string> name);
        std::shared_ptr<std::string> GetResourceDescName(uint32_t index) const;

    private:
        void CloneFromNames(const ResourceDescNamesType& from);

        ResourceDescNamesType mResourceDescNames;
    };

    class DrawingProgramDesc : public DrawingResourceDesc
    {
    public:
        DrawingProgramDesc();
        DrawingProgramDesc(const DrawingProgramDesc& desc);
        DrawingProgramDesc(const DrawingProgramDesc&& desc);
        virtual ~DrawingProgramDesc();

        DrawingProgramDesc& operator= (const DrawingProgramDesc& rhs);

    public:
        EDrawingProgramType mProgramType;
        std::shared_ptr<std::string> m_pName;
        std::shared_ptr<std::string> m_pSourceName;
    };

    class DrawingShaderDesc : public DrawingProgramDesc
    {
    public:
        DrawingShaderDesc();
        DrawingShaderDesc(const DrawingShaderDesc& desc);
        DrawingShaderDesc(const DrawingShaderDesc&& desc);
        virtual ~DrawingShaderDesc();

        DrawingShaderDesc& operator= (const DrawingShaderDesc& rhs);

    public:
        std::shared_ptr<std::string> m_pEntryName;
        std::shared_ptr<std::string> m_pIncludePath;
    };

    class DrawingVertexShaderDesc : public DrawingShaderDesc
    {
    public:
        DrawingVertexShaderDesc();
        DrawingVertexShaderDesc(const DrawingVertexShaderDesc& desc);
        DrawingVertexShaderDesc(const DrawingVertexShaderDesc&& desc);
        virtual ~DrawingVertexShaderDesc();

        DrawingVertexShaderDesc& operator= (const DrawingVertexShaderDesc& rhs);

        EDrawingResourceType GetType() const override;
        DrawingResourceDesc* Clone() const override;
    };

    class DrawingPixelShaderDesc : public DrawingShaderDesc
    {
    public:
        DrawingPixelShaderDesc();
        DrawingPixelShaderDesc(const DrawingPixelShaderDesc& desc);
        DrawingPixelShaderDesc(const DrawingPixelShaderDesc&& desc);
        virtual ~DrawingPixelShaderDesc();

        DrawingPixelShaderDesc& operator= (const DrawingPixelShaderDesc& rhs);

        EDrawingResourceType GetType() const override;
        DrawingResourceDesc* Clone() const override;
    };

    class DrawingVertexFormatDesc : public DrawingResourceDesc
    {
    public:
        DrawingVertexFormatDesc();
        DrawingVertexFormatDesc(const DrawingVertexFormatDesc& desc);
        DrawingVertexFormatDesc(const DrawingVertexFormatDesc&& desc);
        virtual ~DrawingVertexFormatDesc();

        DrawingVertexFormatDesc& operator= (const DrawingVertexFormatDesc& rhs);

        EDrawingResourceType GetType() const override;
        DrawingResourceDesc* Clone() const override;

    public:
        struct VertexInputElement
        {
            VertexInputElement();
            VertexInputElement(const VertexInputElement& elem);
            VertexInputElement(const VertexInputElement&& elem);
            ~VertexInputElement();

            VertexInputElement& operator= (const VertexInputElement& rhs);

            std::shared_ptr<std::string> mpName;
            uint32_t mIndex; 
            EDrawingFormatType mFormat;
            uint32_t mSlot;
            uint32_t mOffset;
            uint32_t mInstanceStepRate; // This value needs to be 0 for per-vertex data.
                                        // Other value for per-instance data
        };

        std::vector<VertexInputElement> m_inputElements;
    };

    class DrawingBufferDesc : public DrawingResourceDesc
    {
    public:
        DrawingBufferDesc();
        DrawingBufferDesc(const DrawingBufferDesc& desc);
        DrawingBufferDesc(const DrawingBufferDesc&& desc);
        virtual ~DrawingBufferDesc();

        DrawingBufferDesc& operator= (const DrawingBufferDesc& rhs);

    public:
        uint32_t mSizeInByte;
        uint32_t mStrideInByte;
        EDrawingUsageType mUsage;
        EDrawingAccessType mAccess;
        uint32_t mFlags;
    };

    class DrawingVertexBufferDesc : public DrawingBufferDesc
    {
    public:
        DrawingVertexBufferDesc();
        DrawingVertexBufferDesc(const DrawingVertexBufferDesc& desc);
        DrawingVertexBufferDesc(const DrawingVertexBufferDesc&& desc);
        virtual ~DrawingVertexBufferDesc();

        DrawingVertexBufferDesc& operator= (const DrawingVertexBufferDesc& rhs);

        EDrawingResourceType GetType() const override;
        DrawingResourceDesc* Clone() const override;
    };

    class DrawingIndexBufferDesc : public DrawingBufferDesc
    {
    public:
        DrawingIndexBufferDesc();
        DrawingIndexBufferDesc(const DrawingIndexBufferDesc& desc);
        DrawingIndexBufferDesc(const DrawingIndexBufferDesc&& desc);
        virtual ~DrawingIndexBufferDesc();

        DrawingIndexBufferDesc& operator= (const DrawingIndexBufferDesc& rhs);

        EDrawingResourceType GetType() const override;
        DrawingResourceDesc* Clone() const override;
    };

    class DrawingTextureDesc : public DrawingResourceDesc
    {
    public:
        DrawingTextureDesc();
        DrawingTextureDesc(const DrawingTextureDesc& desc);
        DrawingTextureDesc(const DrawingTextureDesc&& desc);
        virtual ~DrawingTextureDesc();

        DrawingTextureDesc& operator= (const DrawingTextureDesc& rhs);

        EDrawingResourceType GetType() const override;
        DrawingResourceDesc* Clone() const override;

    private:
        EDrawingTextureType mType;
        EDrawingFormatType mFormat;
        EDrawingUsageType mUsage;
        EDrawingAccessType mAccess;
        uint32_t mWidth;
        uint32_t mHeight;
        uint32_t mDepth;
        uint32_t mArraySize;
        uint32_t mMipLevels;
        uint32_t mBytesPerRow;
        uint32_t mBytesPerSlice;
        uint32_t mFlags;

        uint32_t mSampleCount;
        uint32_t mSampleQuality;
    };
}