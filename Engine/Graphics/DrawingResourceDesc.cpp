#include "DrawingResourceDesc.h"

using namespace Engine;

DrawingResourceDesc::DrawingResourceDesc(const DrawingResourceDesc& desc)
{
    CloneFromNames(desc.mResourceDescNames);
}

DrawingResourceDesc::DrawingResourceDesc(DrawingResourceDesc&& desc)
{
    CloneFromNames(desc.mResourceDescNames);
    mResourceDescNames.clear();
}

DrawingResourceDesc::~DrawingResourceDesc()
{
    mResourceDescNames.clear();
}

DrawingResourceDesc& DrawingResourceDesc::operator= (const DrawingResourceDesc& rhs)
{
    if (this == &rhs)
        return *this;

    CloneFromNames(rhs.mResourceDescNames);
    return *this;
}

DrawingResourceDesc::ResourceDescNamesType DrawingResourceDesc::GetResourceDescNames() const
{
    return mResourceDescNames;
}

void DrawingResourceDesc::AddResourceDescName(uint32_t index, std::shared_ptr<std::string> name)
{
    auto it = mResourceDescNames.find(index);
    if (it != mResourceDescNames.cend())
        return;

    mResourceDescNames.emplace(index, name);
}

std::shared_ptr<std::string> DrawingResourceDesc::GetResourceDescName(uint32_t index) const
{
    auto it = mResourceDescNames.find(index);
    if (it == mResourceDescNames.cend())
        return nullptr;
    
    return it->second;
}

void DrawingResourceDesc::CloneFromNames(const ResourceDescNamesType& from)
{
    mResourceDescNames.clear();
    std::for_each(from.cbegin(), from.cend(), [this](const ResourceDescNamesType::value_type& aElem)
    {
        if (auto& lpName = aElem.second)
            mResourceDescNames.emplace(aElem.first, lpName);
    });
}

DrawingProgramDesc::DrawingProgramDesc() : DrawingResourceDesc(),
    mProgramType(eProgram_Shader), m_pName(nullptr), m_pSourceName(nullptr)
{
}

DrawingProgramDesc::DrawingProgramDesc(const DrawingProgramDesc& desc) : DrawingResourceDesc(desc),
    mProgramType(desc.mProgramType), m_pName(desc.m_pName), m_pSourceName(desc.m_pSourceName)
{
}

DrawingProgramDesc::DrawingProgramDesc(DrawingProgramDesc&& desc) : DrawingResourceDesc(std::move(desc)),
    mProgramType(std::move(desc.mProgramType)), m_pName(std::move(desc.m_pName)), m_pSourceName(std::move(desc.m_pSourceName))
{
}

DrawingProgramDesc::~DrawingProgramDesc()
{
    mProgramType = eProgram_Shader;
    m_pName = nullptr;
    m_pSourceName = nullptr;
}

DrawingProgramDesc& DrawingProgramDesc::operator= (const DrawingProgramDesc& rhs)
{
    if (this == &rhs)
        return *this;

    DrawingResourceDesc::operator= (rhs);
    mProgramType = rhs.mProgramType;
    m_pName = rhs.m_pName;
    m_pSourceName = rhs.m_pSourceName;
    return *this;
}

DrawingShaderDesc::DrawingShaderDesc() : DrawingProgramDesc(),
    m_pEntryName(nullptr), m_pIncludePath(nullptr)
{
}

DrawingShaderDesc::DrawingShaderDesc(const DrawingShaderDesc& desc) : DrawingProgramDesc(desc),
    m_pEntryName(desc.m_pEntryName), m_pIncludePath(desc.m_pIncludePath)
{
}

DrawingShaderDesc::DrawingShaderDesc(DrawingShaderDesc&& desc) : DrawingProgramDesc(std::move(desc)),
    m_pEntryName(std::move(desc.m_pEntryName)), m_pIncludePath(std::move(desc.m_pIncludePath))
{
}

DrawingShaderDesc::~DrawingShaderDesc()
{
    m_pEntryName = nullptr;
    m_pIncludePath = nullptr;
}

DrawingShaderDesc& DrawingShaderDesc::operator= (const DrawingShaderDesc& rhs)
{
    if (this == &rhs)
        return *this;

    DrawingProgramDesc::operator= (rhs);
    m_pEntryName = rhs.m_pEntryName;
    m_pIncludePath = rhs.m_pIncludePath;
    return *this;
}

DrawingVertexShaderDesc::DrawingVertexShaderDesc() : DrawingShaderDesc()
{
}

DrawingVertexShaderDesc::DrawingVertexShaderDesc(const DrawingVertexShaderDesc& desc) : DrawingShaderDesc(desc)
{
}

DrawingVertexShaderDesc::DrawingVertexShaderDesc(DrawingVertexShaderDesc&& desc) : DrawingShaderDesc(std::move(desc))
{
}

DrawingVertexShaderDesc::~DrawingVertexShaderDesc()
{
}

DrawingVertexShaderDesc& DrawingVertexShaderDesc::operator= (const DrawingVertexShaderDesc& rhs)
{
    if (this == &rhs)
        return *this;

    DrawingShaderDesc::operator= (rhs);
    return *this;
}

EDrawingResourceType DrawingVertexShaderDesc::GetType() const
{
    return eResource_Vertex_Shader;
}

DrawingResourceDesc* DrawingVertexShaderDesc::Clone() const
{
    return new DrawingVertexShaderDesc(*this);
}

DrawingPixelShaderDesc::DrawingPixelShaderDesc() : DrawingShaderDesc()
{
}

DrawingPixelShaderDesc::DrawingPixelShaderDesc(const DrawingPixelShaderDesc& desc) : DrawingShaderDesc(desc)
{
}

DrawingPixelShaderDesc::DrawingPixelShaderDesc(DrawingPixelShaderDesc&& desc) : DrawingShaderDesc(std::move(desc))
{
}

DrawingPixelShaderDesc::~DrawingPixelShaderDesc()
{
}

DrawingPixelShaderDesc& DrawingPixelShaderDesc::operator= (const DrawingPixelShaderDesc& rhs)
{
    if (this == &rhs)
        return *this;

    DrawingShaderDesc::operator= (rhs);
    return *this;
}

EDrawingResourceType DrawingPixelShaderDesc::GetType() const
{
    return eResource_Pixel_Shader;
}

DrawingResourceDesc* DrawingPixelShaderDesc::Clone() const
{
    return new DrawingPixelShaderDesc(*this);
}

DrawingVertexFormatDesc::VertexInputElement::VertexInputElement() : mpName(nullptr),
    mIndex(0), mFormat(eFormat_R32G32B32_FLOAT), mSlot(0), mOffset(0), mInstanceStepRate(0)
{
}

DrawingVertexFormatDesc::VertexInputElement::VertexInputElement(const VertexInputElement& elem) : mpName(elem.mpName),
    mIndex(elem.mIndex), mFormat(elem.mFormat), mSlot(elem.mSlot), mOffset(elem.mOffset), mInstanceStepRate(elem.mInstanceStepRate)
{
}

DrawingVertexFormatDesc::VertexInputElement::VertexInputElement(VertexInputElement&& elem) : mpName(std::move(elem.mpName)),
    mIndex(std::move(elem.mIndex)), mFormat(std::move(elem.mFormat)), mSlot(std::move(elem.mSlot)), mOffset(std::move(elem.mOffset)), mInstanceStepRate(std::move(elem.mInstanceStepRate))
{
}

DrawingVertexFormatDesc::VertexInputElement::~VertexInputElement()
{
    mpName = nullptr;
    mIndex = 0;
    mFormat = eFormat_R32G32B32_FLOAT;
    mSlot = 0;
    mOffset = 0;
    mInstanceStepRate = 0;
}

DrawingVertexFormatDesc::VertexInputElement& DrawingVertexFormatDesc::VertexInputElement::operator= (const VertexInputElement& rhs)
{
    if (this == &rhs)
        return *this;

    mpName = rhs.mpName;
    mIndex = rhs.mIndex;
    mFormat = rhs.mFormat;
    mSlot = rhs.mSlot;
    mOffset = rhs.mOffset;
    mInstanceStepRate = rhs.mInstanceStepRate;
    return *this;
}

DrawingVertexFormatDesc::DrawingVertexFormatDesc() : DrawingResourceDesc()
{
}

DrawingVertexFormatDesc::DrawingVertexFormatDesc(const DrawingVertexFormatDesc& desc) : DrawingResourceDesc(desc)
{
    m_inputElements = desc.m_inputElements;
}

DrawingVertexFormatDesc::DrawingVertexFormatDesc(DrawingVertexFormatDesc&& desc) : DrawingResourceDesc(std::move(desc))
{
    m_inputElements = std::move(desc.m_inputElements);
}

DrawingVertexFormatDesc::~DrawingVertexFormatDesc()
{
    m_inputElements.clear();
}

DrawingVertexFormatDesc& DrawingVertexFormatDesc::operator= (const DrawingVertexFormatDesc& rhs)
{
    if (this == &rhs)
        return *this;

    DrawingResourceDesc::operator= (rhs);
    m_inputElements = rhs.m_inputElements;

    return *this;
}

EDrawingResourceType DrawingVertexFormatDesc::GetType() const
{
    return eResource_Vertex_Format;
}

DrawingResourceDesc* DrawingVertexFormatDesc::Clone() const
{
    return new DrawingVertexFormatDesc(*this);
}

DrawingBufferDesc::DrawingBufferDesc() : DrawingResourceDesc(),
    mSizeInByte(0), mStrideInByte(0), mUsage(eUsage_Default), mAccess(eAccess_No_Access), mFlags(0)
{
}

DrawingBufferDesc::DrawingBufferDesc(const DrawingBufferDesc& desc) : DrawingResourceDesc(desc),
    mSizeInByte(desc.mSizeInByte), mStrideInByte(desc.mStrideInByte), mUsage(desc.mUsage), mAccess(desc.mAccess), mFlags(desc.mFlags)
{
}

DrawingBufferDesc::DrawingBufferDesc(DrawingBufferDesc&& desc) : DrawingResourceDesc(std::move(desc)),
    mSizeInByte(std::move(desc.mSizeInByte)), mStrideInByte(std::move(desc.mStrideInByte)), mUsage(std::move(desc.mUsage)), mAccess(std::move(desc.mAccess)), mFlags(std::move(mFlags))
{
}

DrawingBufferDesc::~DrawingBufferDesc()
{
    mSizeInByte = 0;
    mStrideInByte = 0;
    mUsage = eUsage_Default;
    mAccess = eAccess_No_Access;
    mFlags = 0;
}

DrawingBufferDesc& DrawingBufferDesc::operator= (const DrawingBufferDesc& rhs)
{
    if (this == &rhs)
        return *this;

    DrawingResourceDesc::operator= (rhs);
    mSizeInByte = rhs.mSizeInByte;
    mStrideInByte = rhs.mStrideInByte;
    mUsage = rhs.mUsage;
    mAccess = rhs.mAccess;
    mFlags = rhs.mFlags;

    return *this;
}

DrawingVertexBufferDesc::DrawingVertexBufferDesc() : DrawingBufferDesc()
{
}

DrawingVertexBufferDesc::DrawingVertexBufferDesc(const DrawingVertexBufferDesc& desc) : DrawingBufferDesc(desc)
{
}

DrawingVertexBufferDesc::DrawingVertexBufferDesc(DrawingVertexBufferDesc&& desc) : DrawingBufferDesc(std::move(desc))
{
}

DrawingVertexBufferDesc::~DrawingVertexBufferDesc()
{
}

DrawingVertexBufferDesc& DrawingVertexBufferDesc::operator= (const DrawingVertexBufferDesc& rhs)
{
    if (this == &rhs)
        return *this;

    DrawingResourceDesc::operator= (rhs);

    return *this;
}

EDrawingResourceType DrawingVertexBufferDesc::GetType() const
{
    return eResource_Vertex_Buffer;
}

DrawingResourceDesc* DrawingVertexBufferDesc::Clone() const
{
    return new DrawingVertexBufferDesc(*this);
}

DrawingIndexBufferDesc::DrawingIndexBufferDesc() : DrawingBufferDesc()
{
}

DrawingIndexBufferDesc::DrawingIndexBufferDesc(const DrawingIndexBufferDesc& desc) : DrawingBufferDesc(desc)
{
}

DrawingIndexBufferDesc::DrawingIndexBufferDesc(DrawingIndexBufferDesc&& desc) : DrawingBufferDesc(std::move(desc))
{
}

DrawingIndexBufferDesc::~DrawingIndexBufferDesc()
{
}

DrawingIndexBufferDesc& DrawingIndexBufferDesc::operator= (const DrawingIndexBufferDesc& rhs)
{
    if (this == &rhs)
        return *this;

    DrawingResourceDesc::operator= (rhs);

    return *this;
}

EDrawingResourceType DrawingIndexBufferDesc::GetType() const
{
    return eResource_Index_Buffer;
}

DrawingResourceDesc* DrawingIndexBufferDesc::Clone() const
{
    return new DrawingIndexBufferDesc(*this);
}

DrawingBlendStateDesc::BlendDef::BlendDef() : mBlendSrc(eBlend_SrcAlpha), mBlendDst(eBlend_InvSrcAlpha), mBlendOp(eBlendOp_Add)
{
}

DrawingBlendStateDesc::BlendDef::BlendDef(const BlendDef& blend) : mBlendSrc(blend.mBlendSrc), mBlendDst(blend.mBlendDst)
{
}

DrawingBlendStateDesc::BlendDef::BlendDef(BlendDef&& blend) : mBlendSrc(std::move(blend.mBlendSrc)), mBlendDst(std::move(blend.mBlendDst)), mBlendOp(std::move(blend.mBlendOp))
{
}

DrawingBlendStateDesc::BlendDef::~BlendDef()
{
    mBlendSrc = eBlend_SrcAlpha;
    mBlendDst = eBlend_InvSrcAlpha;
    mBlendOp = eBlendOp_Add;
}

DrawingBlendStateDesc::BlendDef& DrawingBlendStateDesc::BlendDef::operator= (const BlendDef& rhs)
{
    if (this == &rhs)
        return *this;

    mBlendSrc = rhs.mBlendSrc;
    mBlendDst = rhs.mBlendDst;
    mBlendOp = rhs.mBlendOp;

    return *this;
}

bool DrawingBlendStateDesc::BlendDef::operator== (const BlendDef& rhs) const
{
    if (this == &rhs)
        return true;

    return (mBlendSrc == rhs.mBlendSrc) && (mBlendDst == rhs.mBlendDst) && (mBlendOp == rhs.mBlendOp);
}

bool DrawingBlendStateDesc::BlendDef::operator!= (const BlendDef& rhs) const
{
    return !((*this) == rhs);
}

DrawingBlendStateDesc::BlendTarget::BlendTarget() : mBlendEnable(true), mRenderTargetWriteMask(WriteMast_All)
{
}

DrawingBlendStateDesc::BlendTarget::BlendTarget(const BlendTarget& target) : mBlendEnable(target.mBlendEnable), mRenderTargetWriteMask(target.mRenderTargetWriteMask)
{
}

DrawingBlendStateDesc::BlendTarget::BlendTarget(BlendTarget&& target) : mBlendEnable(std::move(target.mBlendEnable)), mRenderTargetWriteMask(std::move(target.mRenderTargetWriteMask))
{
}

DrawingBlendStateDesc::BlendTarget::~BlendTarget()
{
    mBlendEnable = true;
    mRenderTargetWriteMask = WriteMast_All;
}

DrawingBlendStateDesc::BlendTarget& DrawingBlendStateDesc::BlendTarget::operator= (const BlendTarget& rhs)
{
    if (this == &rhs)
        return *this;

    mBlendEnable = rhs.mBlendEnable;
    mAlphaBlend = rhs.mAlphaBlend;
    mColorBlend = rhs.mColorBlend;
    mRenderTargetWriteMask = rhs.mRenderTargetWriteMask;

    return *this;
}

bool DrawingBlendStateDesc::BlendTarget::operator== (const BlendTarget& rhs) const
{
    if (this == &rhs)
        return true;

    return (mBlendEnable == rhs.mBlendEnable) &&
           (mAlphaBlend == rhs.mAlphaBlend) &&
           (mColorBlend == rhs.mColorBlend) &&
           (mRenderTargetWriteMask == rhs.mRenderTargetWriteMask);
}

bool DrawingBlendStateDesc::BlendTarget::operator!= (const BlendTarget& rhs) const
{
    return !((*this) == rhs);
}

DrawingBlendStateDesc::DrawingBlendStateDesc() : DrawingResourceDesc(), mAlphaToCoverageEnable(true), mIndependentBlendEnable(false)
{
}

DrawingBlendStateDesc::DrawingBlendStateDesc(const DrawingBlendStateDesc& desc) : DrawingResourceDesc(desc), mAlphaToCoverageEnable(desc.mAlphaToCoverageEnable), mIndependentBlendEnable(desc.mIndependentBlendEnable)
{
    for (uint32_t i = 0; i < MAX_TARGETS; i++)
        mTargets[i] = desc.mTargets[i];
}

DrawingBlendStateDesc::DrawingBlendStateDesc(DrawingBlendStateDesc&& desc) : DrawingResourceDesc(std::move(desc)), mAlphaToCoverageEnable(std::move(desc.mAlphaToCoverageEnable)), mIndependentBlendEnable(std::move(desc.mIndependentBlendEnable))
{
    for (uint32_t i = 0; i < MAX_TARGETS; i++)
        mTargets[i] = std::move(desc.mTargets[i]);
}

DrawingBlendStateDesc::~DrawingBlendStateDesc()
{
    mAlphaToCoverageEnable = true;
    mIndependentBlendEnable = true;
}

DrawingBlendStateDesc& DrawingBlendStateDesc::operator= (const DrawingBlendStateDesc& rhs)
{
    if (this == &rhs)
        return *this;

    mAlphaToCoverageEnable = rhs.mAlphaToCoverageEnable;
    mIndependentBlendEnable = rhs.mIndependentBlendEnable;

    for (uint32_t i = 0; i < MAX_TARGETS; i++)
        mTargets[i] = rhs.mTargets[i];

    return *this;
}

EDrawingResourceType DrawingBlendStateDesc::GetType() const
{
    return eResource_Blend_State;
}

DrawingResourceDesc* DrawingBlendStateDesc::Clone() const
{
    return new DrawingBlendStateDesc(*this);
}

DrawingDepthStateDesc::DepthState::DepthState() : mDepthEnable(true), mDepthWriteEnable(true), mDepthFunc(eComparison_LessEqual)
{
}

DrawingDepthStateDesc::DepthState::DepthState(const DepthState& depth) : mDepthEnable(depth.mDepthEnable), mDepthWriteEnable(depth.mDepthWriteEnable), mDepthFunc(depth.mDepthFunc)
{
}

DrawingDepthStateDesc::DepthState::DepthState(DepthState&& depth) : mDepthEnable(std::move(depth.mDepthEnable)), mDepthWriteEnable(std::move(depth.mDepthWriteEnable)), mDepthFunc(std::move(depth.mDepthFunc))
{
}

DrawingDepthStateDesc::DepthState::~DepthState()
{
    mDepthEnable = true;
    mDepthWriteEnable = true;
    mDepthFunc = eComparison_LessEqual;
}

DrawingDepthStateDesc::DepthState& DrawingDepthStateDesc::DepthState::operator= (const DepthState& rhs)
{
    if (this == &rhs)
        return *this;

    mDepthEnable = rhs.mDepthEnable;
    mDepthWriteEnable = rhs.mDepthWriteEnable;
    mDepthFunc = rhs.mDepthFunc;

    return *this;
}

bool DrawingDepthStateDesc::DepthState::operator== (const DepthState& rhs) const
{
    if (this == &rhs)
        return true;

    return (mDepthEnable == rhs.mDepthEnable) &&
           (mDepthWriteEnable == rhs.mDepthWriteEnable) &&
           (mDepthFunc == rhs.mDepthFunc);
}

bool DrawingDepthStateDesc::DepthState::operator!= (const DepthState& rhs) const
{
    return !((*this) == rhs);
}

DrawingDepthStateDesc::StencilOp::StencilOp() : mStencilFailOp(eStencilOp_Keep), mStencilDepthFailOp(eStencilOp_Keep), mStencilPassOp(eStencilOp_Keep), mStencilFunc(eComparison_Always)
{
}

DrawingDepthStateDesc::StencilOp::StencilOp(const StencilOp& op) : mStencilFailOp(op.mStencilFailOp), mStencilDepthFailOp(op.mStencilDepthFailOp), mStencilPassOp(op.mStencilPassOp), mStencilFunc(op.mStencilFunc)
{
}

DrawingDepthStateDesc::StencilOp::StencilOp(StencilOp&& op) : mStencilFailOp(std::move(op.mStencilFailOp)), mStencilDepthFailOp(std::move(op.mStencilDepthFailOp)), mStencilPassOp(std::move(op.mStencilPassOp)), mStencilFunc(std::move(op.mStencilFunc))
{
}

DrawingDepthStateDesc::StencilOp::~StencilOp()
{
    mStencilFailOp = eStencilOp_Keep;
    mStencilDepthFailOp = eStencilOp_Keep;
    mStencilPassOp = eStencilOp_Keep;
    mStencilFunc = eComparison_Always;
}

DrawingDepthStateDesc::StencilOp& DrawingDepthStateDesc::StencilOp::operator= (const StencilOp& rhs)
{
    if (this == &rhs)
        return *this;

    mStencilFailOp = rhs.mStencilFailOp;
    mStencilDepthFailOp = rhs.mStencilDepthFailOp;
    mStencilPassOp = rhs.mStencilPassOp;
    mStencilFunc = rhs.mStencilFunc;

    return *this;
}

bool DrawingDepthStateDesc::StencilOp::operator== (const StencilOp& rhs) const
{
    if (this == &rhs)
        return true;

    return (mStencilFailOp == rhs.mStencilFailOp) &&
           (mStencilDepthFailOp == rhs.mStencilDepthFailOp) &&
           (mStencilPassOp == rhs.mStencilPassOp) &&
           (mStencilFunc == rhs.mStencilFunc);
}

bool DrawingDepthStateDesc::StencilOp::operator!= (const StencilOp& rhs) const
{
    return !((*this) == rhs);
}

DrawingDepthStateDesc::StencilState::StencilState() : mStencilEnable(false), mStencilReadMask(Mast_All), mStencilWriteMask(Mast_All)
{
}

DrawingDepthStateDesc::StencilState::StencilState(const StencilState& stencil) : mStencilEnable(stencil.mStencilEnable),
    mStencilReadMask(stencil.mStencilReadMask), mStencilWriteMask(stencil.mStencilWriteMask),
    mFrontFace(stencil.mFrontFace), mBackFace(stencil.mBackFace)
{
}

DrawingDepthStateDesc::StencilState::StencilState(StencilState&& stencil) : mStencilEnable(std::move(stencil.mStencilEnable)),
    mStencilReadMask(std::move(stencil.mStencilReadMask)), mStencilWriteMask(std::move(stencil.mStencilWriteMask)),
    mFrontFace(std::move(stencil.mFrontFace)), mBackFace(std::move(stencil.mBackFace))
{
}

DrawingDepthStateDesc::StencilState::~StencilState()
{
    mStencilEnable = false;
    mStencilReadMask = Mast_All;
    mStencilWriteMask = Mast_All;
}

DrawingDepthStateDesc::StencilState& DrawingDepthStateDesc::StencilState::operator= (const StencilState& rhs)
{
    if (this == &rhs)
        return *this;

    mStencilEnable = rhs.mStencilEnable;
    mStencilReadMask = rhs.mStencilReadMask;
    mStencilWriteMask = rhs.mStencilWriteMask;
    mFrontFace = rhs.mFrontFace;
    mBackFace = rhs.mBackFace;

    return *this;
}

bool DrawingDepthStateDesc::StencilState::operator== (const StencilState& rhs) const
{
    if (this == &rhs)
        return true;

    return (mStencilEnable == rhs.mStencilEnable) &&
           (mStencilReadMask == rhs.mStencilReadMask) &&
           (mStencilWriteMask == rhs.mStencilWriteMask) &&
           (mFrontFace == rhs.mFrontFace) &&
           (mBackFace == rhs.mBackFace);
}

bool DrawingDepthStateDesc::StencilState::operator!= (const StencilState& rhs) const
{
    return !((*this) == rhs);
}

DrawingDepthStateDesc::DrawingDepthStateDesc() : DrawingResourceDesc()
{
}

DrawingDepthStateDesc::DrawingDepthStateDesc(const DrawingDepthStateDesc& desc) : DrawingResourceDesc(desc),
    mDepthState(desc.mDepthState), mStencilState(desc.mStencilState)
{
}

DrawingDepthStateDesc::DrawingDepthStateDesc(DrawingDepthStateDesc&& desc) : DrawingResourceDesc(std::move(desc)),
    mDepthState(std::move(desc.mDepthState)), mStencilState(std::move(desc.mStencilState))
{
}

DrawingDepthStateDesc::~DrawingDepthStateDesc()
{
}

DrawingDepthStateDesc& DrawingDepthStateDesc::operator= (const DrawingDepthStateDesc& rhs)
{
    if (this == &rhs)
        return *this;

    DrawingResourceDesc::operator= (rhs);

    mDepthState = rhs.mDepthState;
    mStencilState = rhs.mStencilState;

    return *this;
}

EDrawingResourceType DrawingDepthStateDesc::GetType() const
{
    return eResource_Depth_State;
}

DrawingResourceDesc* DrawingDepthStateDesc::Clone() const
{
    return new DrawingDepthStateDesc(*this);
}

DrawingRasterStateDesc::DrawingRasterStateDesc() : DrawingResourceDesc(),
    mFillMode(eFillMode_Solid), mCullMode(eCullMode_None), mFrontCounterClockwise(true), mDepthBias(0),
    mDepthBiasClamp(0.0f), mSlopeScaledDepthBias(0.0f),
    mDepthClipEnable(true), mScissorEnable(false), mMultisampleEnable(false), mAntialiasedLineEnable(false)
{
}

DrawingRasterStateDesc::DrawingRasterStateDesc(const DrawingRasterStateDesc& desc) : DrawingResourceDesc(desc),
    mFillMode(desc.mFillMode), mCullMode(desc.mCullMode), mFrontCounterClockwise(desc.mFrontCounterClockwise), mDepthBias(desc.mDepthBias),
    mDepthBiasClamp(desc.mDepthBiasClamp), mSlopeScaledDepthBias(desc.mSlopeScaledDepthBias),
    mDepthClipEnable(desc.mDepthClipEnable), mScissorEnable(desc.mScissorEnable), mMultisampleEnable(desc.mMultisampleEnable), mAntialiasedLineEnable(desc.mAntialiasedLineEnable)
{
}

DrawingRasterStateDesc::DrawingRasterStateDesc(DrawingRasterStateDesc&& desc) : DrawingResourceDesc(std::move(desc)),
    mFillMode(std::move(desc.mFillMode)), mCullMode(std::move(desc.mCullMode)), mFrontCounterClockwise(std::move(desc.mFrontCounterClockwise)), mDepthBias(std::move(desc.mDepthBias)),
    mDepthBiasClamp(std::move(desc.mDepthBiasClamp)), mSlopeScaledDepthBias(std::move(desc.mSlopeScaledDepthBias)),
    mDepthClipEnable(std::move(desc.mDepthClipEnable)), mScissorEnable(std::move(desc.mScissorEnable)), mMultisampleEnable(std::move(desc.mMultisampleEnable)), mAntialiasedLineEnable(std::move(desc.mAntialiasedLineEnable))
{
}

DrawingRasterStateDesc::~DrawingRasterStateDesc()
{
    mFillMode = eFillMode_Solid;
    mCullMode = eCullMode_None;
    mFrontCounterClockwise = true;
    mDepthBias = 0;
    mDepthBiasClamp = 0.0f;
    mSlopeScaledDepthBias = 0.0f;
    mDepthClipEnable = true;
    mScissorEnable = false;
    mMultisampleEnable = false;
    mAntialiasedLineEnable = false;
}

DrawingRasterStateDesc& DrawingRasterStateDesc::operator= (const DrawingRasterStateDesc& rhs)
{
    if (this == &rhs)
        return *this;

    DrawingResourceDesc::operator= (rhs);

    mFillMode = rhs.mFillMode;
    mCullMode = rhs.mCullMode;
    mFrontCounterClockwise = rhs.mFrontCounterClockwise;
    mDepthBias = rhs.mDepthBias;
    mDepthBiasClamp = rhs.mDepthBiasClamp;
    mSlopeScaledDepthBias = rhs.mSlopeScaledDepthBias;
    mDepthClipEnable = rhs.mDepthClipEnable;
    mScissorEnable = rhs.mScissorEnable;
    mMultisampleEnable = rhs.mMultisampleEnable;
    mAntialiasedLineEnable = rhs.mAntialiasedLineEnable;

    return *this;
}

EDrawingResourceType DrawingRasterStateDesc::GetType() const
{
    return eResource_Raster_State;
}

DrawingResourceDesc* DrawingRasterStateDesc::Clone() const
{
    return new DrawingRasterStateDesc(*this);
}

DrawingSamplerStateDesc::DrawingSamplerStateDesc() : DrawingResourceDesc(),
    mSamplerMode(eSamplerMode_Normal), mMinFilter(eFilterMode_Point), mMagFilter(eFilterMode_Point), mMipFilter(eFilterMode_Point),
    mAddressU(eAddressMode_Clamp), mAddressV(eAddressMode_Clamp), mAddressW(eAddressMode_Clamp),
    mComparisonFunc(eComparison_Always), mBorderColor(), mMinLOD(0.0f), mMaxLOD(0.0f), mMipLODBias(0.0f), mMaxAnisotropy(1)
{
}

DrawingTextureDesc::DrawingTextureDesc() : DrawingResourceDesc(),
    mType(eTexture_2D), mFormat(eFormat_R8G8B8A8_UNORM), mUsage(eUsage_Default), mAccess(eAccess_No_Access),
    mWidth(0), mHeight(0), mDepth(0), mArraySize(1), mMipLevels(1), mBytesPerRow(0), mBytesPerSlice(0), mFlags(0),
    mSampleCount(1), mSampleQuality(0)
{
}

DrawingTextureDesc::DrawingTextureDesc(const DrawingTextureDesc& desc) : DrawingResourceDesc(desc),
    mType(desc.mType), mFormat(desc.mFormat), mUsage(desc.mUsage), mAccess(desc.mAccess),
    mWidth(desc.mWidth), mHeight(desc.mHeight), mDepth(desc.mDepth), mArraySize(desc.mArraySize), mMipLevels(desc.mMipLevels), mBytesPerRow(desc.mBytesPerRow), mBytesPerSlice(desc.mBytesPerSlice), mFlags(desc.mFlags),
    mSampleCount(desc.mSampleCount), mSampleQuality(desc.mSampleQuality) 
{
}

DrawingTextureDesc::DrawingTextureDesc(DrawingTextureDesc&& desc) : DrawingResourceDesc(std::move(desc)),
    mType(std::move(desc.mType)), mFormat(std::move(desc.mFormat)), mUsage(std::move(desc.mUsage)), mAccess(std::move(desc.mAccess)),
    mWidth(std::move(desc.mWidth)), mHeight(std::move(desc.mHeight)), mDepth(std::move(desc.mDepth)), mArraySize(std::move(desc.mArraySize)), mMipLevels(std::move(desc.mMipLevels)), mBytesPerRow(std::move(desc.mBytesPerRow)), mBytesPerSlice(std::move(desc.mBytesPerSlice)), mFlags(std::move(desc.mFlags)),
    mSampleCount(std::move(desc.mSampleCount)), mSampleQuality(std::move(desc.mSampleQuality))
{
}

DrawingTextureDesc::~DrawingTextureDesc()
{
    mType = eTexture_2D;
    mFormat = eFormat_R8G8B8A8_UNORM;
    mUsage = eUsage_Default;
    mAccess = eAccess_No_Access;
    mWidth = 0;
    mHeight = 0;
    mDepth = 0;
    mArraySize = 1;
    mMipLevels = 1;
    mBytesPerRow = 0;
    mBytesPerSlice = 0;
    mFlags = 0;
    mSampleCount = 1;
    mSampleQuality = 0;
}

DrawingTextureDesc& DrawingTextureDesc::operator= (const DrawingTextureDesc& rhs)
{
    if (this == &rhs)
        return *this;

    DrawingResourceDesc::operator= (rhs);
    mType = rhs.mType;
    mFormat = rhs.mFormat;
    mUsage = rhs.mUsage;
    mAccess = rhs.mAccess;
    mWidth = rhs.mWidth;
    mHeight = rhs.mHeight;
    mDepth = rhs.mDepth;
    mArraySize = rhs.mArraySize;
    mMipLevels = rhs.mMipLevels;
    mBytesPerRow = rhs.mBytesPerRow;
    mBytesPerSlice = rhs.mBytesPerSlice;
    mFlags = rhs.mFlags;
    mSampleCount = rhs.mSampleCount;
    mSampleQuality = rhs.mSampleQuality;

    return *this;
}

EDrawingResourceType DrawingTextureDesc::GetType() const
{
    return eResource_Texture;
}

DrawingResourceDesc* DrawingTextureDesc::Clone() const
{
    return new DrawingTextureDesc(*this);
}