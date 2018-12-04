
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
        DrawingResourceDesc(DrawingResourceDesc&& desc);
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

        ResourceDescNamesType m_resourceDescNames;
    };

    class DrawingProgramDesc : public DrawingResourceDesc
    {
    public:
        DrawingProgramDesc();
        DrawingProgramDesc(const DrawingProgramDesc& desc);
        DrawingProgramDesc(DrawingProgramDesc&& desc);
        virtual ~DrawingProgramDesc();

        DrawingProgramDesc& operator= (const DrawingProgramDesc& rhs);

    public:
        EDrawingProgramType mProgramType;
        std::shared_ptr<std::string> mpName;
        std::shared_ptr<std::string> mpSourceName;
    };

    class DrawingShaderDesc : public DrawingProgramDesc
    {
    public:
        DrawingShaderDesc();
        DrawingShaderDesc(const DrawingShaderDesc& desc);
        DrawingShaderDesc(DrawingShaderDesc&& desc);
        virtual ~DrawingShaderDesc();

        DrawingShaderDesc& operator= (const DrawingShaderDesc& rhs);

    public:
        std::shared_ptr<std::string> mpEntryName;
        std::shared_ptr<std::string> mpIncludePath;
    };

    class DrawingVertexShaderDesc : public DrawingShaderDesc
    {
    public:
        DrawingVertexShaderDesc();
        DrawingVertexShaderDesc(const DrawingVertexShaderDesc& desc);
        DrawingVertexShaderDesc(DrawingVertexShaderDesc&& desc);
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
        DrawingPixelShaderDesc(DrawingPixelShaderDesc&& desc);
        virtual ~DrawingPixelShaderDesc();

        DrawingPixelShaderDesc& operator= (const DrawingPixelShaderDesc& rhs);

        EDrawingResourceType GetType() const override;
        DrawingResourceDesc* Clone() const override;
    };

    class DrawingEffectDesc : public DrawingProgramDesc
    {
    public:
        enum EffectType
        {
            EffectType_General,
            EffectType_Compute,
            EffectType_Linked,
        };

        DrawingEffectDesc();
        DrawingEffectDesc(const DrawingEffectDesc& desc);
        DrawingEffectDesc(DrawingEffectDesc&& desc);
        virtual ~DrawingEffectDesc();

        DrawingEffectDesc& operator= (const DrawingEffectDesc& rhs);

        virtual EffectType GetEffectType() const = 0;
        EDrawingResourceType GetType() const override;
    };

    class DrawingGeneralEffectDesc : public DrawingEffectDesc
    {
    public:
        DrawingGeneralEffectDesc();
        DrawingGeneralEffectDesc(const DrawingGeneralEffectDesc& desc);
        DrawingGeneralEffectDesc(DrawingGeneralEffectDesc&& desc);
        virtual ~DrawingGeneralEffectDesc();

        DrawingGeneralEffectDesc& operator= (const DrawingGeneralEffectDesc& rhs);

        EffectType GetEffectType() const override;
        DrawingResourceDesc* Clone() const override;
    };

    class DrawingComputeEffectDesc : public DrawingEffectDesc
    {
    public:
        DrawingComputeEffectDesc();
        DrawingComputeEffectDesc(const DrawingComputeEffectDesc& desc);
        DrawingComputeEffectDesc(DrawingComputeEffectDesc&& desc);
        virtual ~DrawingComputeEffectDesc();

        DrawingComputeEffectDesc& operator= (const DrawingComputeEffectDesc& rhs);

        EffectType GetEffectType() const override;
        DrawingResourceDesc* Clone() const override;
    };

    class DrawingLinkedEffectDesc : public DrawingEffectDesc
    {
    public:
        DrawingLinkedEffectDesc();
        DrawingLinkedEffectDesc(const DrawingLinkedEffectDesc& desc);
        DrawingLinkedEffectDesc(DrawingLinkedEffectDesc&& desc);
        virtual ~DrawingLinkedEffectDesc();

        DrawingLinkedEffectDesc& operator= (const DrawingLinkedEffectDesc& rhs);

        EffectType GetEffectType() const override;
        DrawingResourceDesc* Clone() const override;
    };

    class DrawingVertexFormatDesc : public DrawingResourceDesc
    {
    public:
        DrawingVertexFormatDesc();
        DrawingVertexFormatDesc(const DrawingVertexFormatDesc& desc);
        DrawingVertexFormatDesc(DrawingVertexFormatDesc&& desc);
        virtual ~DrawingVertexFormatDesc();

        DrawingVertexFormatDesc& operator= (const DrawingVertexFormatDesc& rhs);

        EDrawingResourceType GetType() const override;
        DrawingResourceDesc* Clone() const override;

    public:
        struct VertexInputElement
        {
            VertexInputElement();
            VertexInputElement(const VertexInputElement& elem);
            VertexInputElement(VertexInputElement&& elem);
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
        DrawingBufferDesc(DrawingBufferDesc&& desc);
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
        DrawingVertexBufferDesc(DrawingVertexBufferDesc&& desc);
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
        DrawingIndexBufferDesc(DrawingIndexBufferDesc&& desc);
        virtual ~DrawingIndexBufferDesc();

        DrawingIndexBufferDesc& operator= (const DrawingIndexBufferDesc& rhs);

        EDrawingResourceType GetType() const override;
        DrawingResourceDesc* Clone() const override;
    };

    class DrawingBlendStateDesc : public DrawingResourceDesc
    {
    public:
        DrawingBlendStateDesc();
        DrawingBlendStateDesc(const DrawingBlendStateDesc& desc);
        DrawingBlendStateDesc(DrawingBlendStateDesc&& desc);
        virtual ~DrawingBlendStateDesc();

        DrawingBlendStateDesc& operator= (const DrawingBlendStateDesc& rhs);

        EDrawingResourceType GetType() const override;
        DrawingResourceDesc* Clone() const override;

        struct BlendDef
        {
            BlendDef();
            BlendDef(const BlendDef& blend);
            BlendDef(BlendDef&& blend);
            virtual ~BlendDef();

            BlendDef& operator= (const BlendDef& rhs);

            bool operator== (const BlendDef& rhs) const;
            bool operator!= (const BlendDef& rhs) const;

            EDrawingBlendType mBlendSrc;
            EDrawingBlendType mBlendDst;
            EDrawingBlendOpType mBlendOp;
        };
        struct BlendTarget
        {
            enum WriteMask
            {
                WriteMast_All = 0xf,
            };
            BlendTarget();
            BlendTarget(const BlendTarget& target);
            BlendTarget(BlendTarget&& target);
            virtual ~BlendTarget();

            BlendTarget& operator= (const BlendTarget& rhs);

            bool operator== (const BlendTarget& rhs) const;
            bool operator!= (const BlendTarget& rhs) const;

            bool mBlendEnable;
            BlendDef mAlphaBlend;
            BlendDef mColorBlend;
            uint8_t mRenderTargetWriteMask;
        };

    public:
        bool mAlphaToCoverageEnable;
        bool mIndependentBlendEnable;
        BlendTarget mTargets[MAX_TARGETS];
    };

    class DrawingDepthStateDesc : public DrawingResourceDesc
    {
    public:
        DrawingDepthStateDesc();
        DrawingDepthStateDesc(const DrawingDepthStateDesc& depth);
        DrawingDepthStateDesc(DrawingDepthStateDesc&& depth);
        virtual ~DrawingDepthStateDesc();

        DrawingDepthStateDesc& operator= (const DrawingDepthStateDesc& rhs);

        EDrawingResourceType GetType() const override;
        DrawingResourceDesc* Clone() const override;

        struct DepthState
        {
            DepthState();
            DepthState(const DepthState& depth);
            DepthState(DepthState&& depth);
            virtual ~DepthState();

            DepthState& operator= (const DepthState& rhs);

            bool operator== (const DepthState& rhs) const;
            bool operator!= (const DepthState& rhs) const;

            bool mDepthEnable;
            bool mDepthWriteEnable;
            EDrawingComparisonFuncType mDepthFunc;
        };

        struct StencilOp
        {
            StencilOp();
            StencilOp(const StencilOp& op);
            StencilOp(StencilOp&& op);
            virtual ~StencilOp();

            StencilOp& operator= (const StencilOp& rhs);

            bool operator== (const StencilOp& rhs) const;
            bool operator!= (const StencilOp& rhs) const;

            EDrawingStencilOpType mStencilFailOp;
            EDrawingStencilOpType mStencilDepthFailOp;
            EDrawingStencilOpType mStencilPassOp;
            EDrawingComparisonFuncType mStencilFunc;
        };

        struct StencilState
        {
            enum Mask
            {
                Mast_All = 0xf,
            };
            StencilState();
            StencilState(const StencilState& stencil);
            StencilState(StencilState&& stencil);
            virtual ~StencilState();

            StencilState& operator= (const StencilState& rhs);

            bool operator== (const StencilState& rhs) const;
            bool operator!= (const StencilState& rhs) const;

            bool mStencilEnable;
            uint8_t mStencilReadMask;
            uint8_t mStencilWriteMask;
            StencilOp mFrontFace;
            StencilOp mBackFace;
        };

    public:
        DepthState mDepthState;
        StencilState mStencilState;
    };

    class DrawingRasterStateDesc : public DrawingResourceDesc
    {
    public:
        DrawingRasterStateDesc();
        DrawingRasterStateDesc(const DrawingRasterStateDesc& desc);
        DrawingRasterStateDesc(DrawingRasterStateDesc&& desc);
        virtual ~DrawingRasterStateDesc();

        DrawingRasterStateDesc& operator= (const DrawingRasterStateDesc& rhs);

        EDrawingResourceType GetType() const override;
        DrawingResourceDesc* Clone() const override;

    public:
        EDrawingFillModeType mFillMode;
        EDrawingCullModeType mCullMode;

        bool mFrontCounterClockwise;
        int mDepthBias;

        float mDepthBiasClamp;
        float mSlopeScaledDepthBias;

        bool mDepthClipEnable;
        bool mScissorEnable;
        bool mMultisampleEnable;
        bool mAntialiasedLineEnable;
    };

    class DrawingSamplerStateDesc : public DrawingResourceDesc
    {
    public:
        DrawingSamplerStateDesc();
        DrawingSamplerStateDesc(const DrawingSamplerStateDesc& desc);
        DrawingSamplerStateDesc(DrawingSamplerStateDesc&& desc);
        virtual ~DrawingSamplerStateDesc();

        DrawingSamplerStateDesc& operator= (const DrawingSamplerStateDesc& rhs);

        EDrawingResourceType GetType() const override;
        DrawingResourceDesc* Clone() const override;

    public:
        EDrawingSamplerModeType mSamplerMode;

        EDrawingFilterModeType mMinFilter;
        EDrawingFilterModeType mMagFilter;
        EDrawingFilterModeType mMipFilter;

        EDrawingAddressModeType mAddressU;
        EDrawingAddressModeType mAddressV;
        EDrawingAddressModeType mAddressW;

        EDrawingComparisonFuncType mComparisonFunc;

        float mBorderColor[4];
        float mMinLOD;
        float mMaxLOD;
        float mMipLODBias;

        uint32_t mMaxAnisotropy;
    };

    class DrawingTextureDesc : public DrawingResourceDesc
    {
    public:
        DrawingTextureDesc();
        DrawingTextureDesc(const DrawingTextureDesc& desc);
        DrawingTextureDesc(DrawingTextureDesc&& desc);
        virtual ~DrawingTextureDesc();

        DrawingTextureDesc& operator= (const DrawingTextureDesc& rhs);

        EDrawingResourceType GetType() const override;
        DrawingResourceDesc* Clone() const override;

    public:
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

    class DrawingPrimitiveDesc : public DrawingResourceDesc
    {
    public:
        DrawingPrimitiveDesc();
        DrawingPrimitiveDesc(const DrawingPrimitiveDesc& desc);
        DrawingPrimitiveDesc(DrawingPrimitiveDesc&& desc);
        virtual ~DrawingPrimitiveDesc();

        DrawingPrimitiveDesc& operator= (const DrawingPrimitiveDesc& rhs);

        EDrawingResourceType GetType() const override;
        DrawingResourceDesc* Clone() const override;

    public:
        EDrawingPrimitiveType mPrimitive;
    };
}