#pragma once

namespace Engine
{
    const uint32_t MAX_TARGETS = 8;


    enum EDrawingResourceType
    {
        eResource_Vertex_Buffer = 1,
        eResource_Index_Buffer,

        eResource_Vertex_Format,

        eResource_Vertex_Shader,
        eResource_Pixel_Shader,

        eResource_Texture,

        eResource_Blend_State,
        eResource_Depth_State,
        eResource_Raster_State,
        eResource_Sampler_State,

        eResource_Target,
    };

    enum EDrawingProgramType
    {
        // This is used for shader
        eProgram_Shader = 1,
        // This is used for effect
        eProgram_Binary,
        eProgram_Src,
        eProgram_File,
    };

    enum EDrawingFormatType
    {
        eFormat_Unknown = 0,
        eFormat_R8G8B8A8_UNORM,
        eFormat_R8G8B8A8_SNORM,
        eFormat_R8G8B8A8_UINT,
        eFormat_R8G8B8A8_SINT,

        eFormat_R32G32B32_FLOAT,
        eFormat_R32G32B32_UINT,
        eFormat_R32G32B32_SINT,
        eFormat_R32G32B32A32_FLOAT,
        eFormat_R32G32B32A32_UINT,
        eFormat_R32G32B32A32_SINT,
    };

    enum EDrawingUsageType
    {
        eUsage_Default = 0,
        eUsage_Dynamic,
        eUsage_Staging,
        eUsage_Immutable,
    };

    enum EDrawingAccessType
    {
        eAccess_No_Access = 0,
        eAccess_Read,
        eAccess_Write,
        eAccess_RW,
    };

    enum EDrawingTextureType
    {
        eTexture_Unknown = 0,
        eTexture_1D,
        eTexture_1DArray,
        eTexture_2D,
        eTexture_2DArray,
        eTexture_Cube,
        eTexture_3D,
    };

    enum EDrawingBlendType
    {
        eBlend_Zero,
        eBlend_One,
        eBlend_SrcColor,
        eBlend_InvSrcColor,
        eBlend_SrcAlpha,
        eBlend_InvSrcAlpha,
        eBlend_DstAlpha,
        eBlend_InvDstAlpha,
        eBlend_DstColor,
        eBlend_InvDstColor,
        eBlend_SrcAlphaSat,
        eBlend_BlendFactor,
        eBlend_InvBlendFactor,
        eBlend_Src1Color,
        eBlend_InvSrc1Color,
        eBlend_Src1Alpha,
        eBlend_InvSrc1Alpha,
    };

    enum EDrawingBlendOpType
    {
        eBlendOp_Add,
        eBlendOp_Subtract,
        eBlendOp_RevSubtract,
        eBlendOp_Min,
        eBlendOp_Max,
    };

    enum EDrawingComparisonFuncType
    {
        eComparison_Never,
        eComparison_Less,
        eComparison_Equal,
        eComparison_LessEqual,
        eComparison_Greater,
        eComparison_NotEqual,
        eComparison_GreaterEqual,
        eComparison_Always,
    };

    enum EDrawingStencilOpType
    {
        eStencilOp_Keep,
        eStencilOp_Zero,
        eStencilOp_Replace,
        eStencilOp_IncrSat,
        eStencilOp_DecrSat,
        eStencilOp_Invert,
        eStencilOp_Incr,
        eStencilOp_Decr,
    };

    enum EDrawingFillModeType
    {
        eFillMode_Solid,
        eFillMode_WireFrame,
    };

    enum EDrawingCullModeType
    {
        eCullMode_None,
        eCullMode_Front,
        eCullMode_Back,
    };

    enum EDrawingSamplerModeType
    {
        eSamplerMode_Normal,
        eSamplerMode_Compare,
        eSamplerMode_Max,
        eSamplerMode_Min,
    };

    enum EDrawingFilterModeType
    {
        eFilterMode_Point,
        eFilterMode_Linear,
        eFilterMode_Anisotropic,
    };

    enum EDrawingAddressModeType
    {
        eAddressMode_Wrap,
        eAddressMode_Mirror,
        eAddressMode_Clamp,
        eAddressMode_Border,
        eAddressMode_MirrorOnce,
    };
}