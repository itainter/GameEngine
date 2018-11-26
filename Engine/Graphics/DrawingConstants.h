#pragma once

namespace Engine
{
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
        eResource_Samplar_State,

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

    enum EBlendType
    {
        eBlend_Zero,
        eBlend_One,
        eBlend_SrcColor,
        eBlend_InvSrcColor,
        eBlend_SrcAlpha,
        eBlend_InvSrcAlpha,
        eBlend_DestAlpha,
        eBlend_InvDestAlpha,
        eBlend_DestColor,
        eBlend_InvDestColor,
        eBlend_SrcAlphaSat,
        eBlend_BlendFactor,
        eBlend_InvBlendFactor,
        eBlend_Src1Color,
        eBlend_InvSrc1Color,
        eBlend_Src1Alpha,
        eBlend_InvSrc1Alpha,
    };

    enum EBlendOpType
    {
        eBlendOp_Add,
        eBlendOp_Subtract,
        eBlendOp_RevSubtract,
        eBlendOp_Min,
        eBlendOp_Max,
    };
}