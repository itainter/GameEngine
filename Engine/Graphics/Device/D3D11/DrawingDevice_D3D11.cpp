#include <fstream>
#include <memory>
#include <d3d11shader.h>
#include <d3dcompiler.h>

#include "DrawingUtil_D3D11.h"
#include "DrawingRawResource_D3D11.h"
#include "DrawingDevice_D3D11.h"
#include "DrawingParameter.h"

using namespace Engine;

DrawingDevice_D3D11::DrawingDevice_D3D11()
{
}

DrawingDevice_D3D11::~DrawingDevice_D3D11()
{
}

bool DrawingDevice_D3D11::CreateVertexFormat(const DrawingVertexFormatDesc& desc, std::shared_ptr<DrawingVertexFormat>& pRes)
{
    std::vector<D3D11_INPUT_ELEMENT_DESC> inputElementDesc;

    for (const auto& elem : desc.m_inputElements)
    {
        D3D11_INPUT_ELEMENT_DESC input;
        input.SemanticName = elem.mpName->c_str();
        input.SemanticIndex = elem.mIndex;
        input.Format = D3D11Enum(elem.mFormat);
        input.InputSlot = elem.mSlot;
        input.AlignedByteOffset = elem.mOffset;
        input.InputSlotClass = elem.mInstanceStepRate == 0 ? D3D11_INPUT_PER_VERTEX_DATA : D3D11_INPUT_PER_INSTANCE_DATA;
        input.InstanceDataStepRate = elem.mInstanceStepRate;

        inputElementDesc.push_back(input);
    }

    auto pVertexFormat = std::make_shared<DrawingVertexFormat>(std::shared_ptr<DrawingDevice>(this));

    auto pVertexFormatRaw = std::shared_ptr<DrawingRawVertexFormat>(new DrawingRawVertexFormat_D3D11(*this, inputElementDesc, nullptr, 0));
    pVertexFormat->SetDesc(std::shared_ptr<DrawingResourceDesc>(desc.Clone()));
    pVertexFormat->SetResource(pVertexFormatRaw);

    pRes = pVertexFormat;
    return true;
}

bool DrawingDevice_D3D11::CreateVertexBuffer(const DrawingVertexBufferDesc& desc, std::shared_ptr<DrawingVertexBuffer>& pRes, std::shared_ptr<DrawingResource> pRefRes, const void* pData, uint32_t size)
{
    if ((pData != nullptr) && (size < desc.mSizeInBytes))
        return false;

    D3D11_BUFFER_DESC bufferDesc;
    bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bufferDesc.ByteWidth = desc.mSizeInBytes;
    bufferDesc.Usage = D3D11Enum(desc.mUsage);
    bufferDesc.CPUAccessFlags = D3D11Enum(desc.mAccess);
    bufferDesc.MiscFlags = D3D11Enum(desc.mFlags);
    bufferDesc.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA subResData;
    ZeroMemory(&subResData, sizeof(D3D11_SUBRESOURCE_DATA));
    subResData.pSysMem = pData;

    auto pVertexBuffer = std::make_shared<DrawingVertexBuffer>(std::shared_ptr<DrawingDevice>(this));

    auto pVertexBufferRaw = std::shared_ptr<DrawingRawVertexBuffer>(new DrawingRawVertexBuffer_D3D11(*this, bufferDesc, subResData, desc.mStrideInBytes, 0));
    pVertexBuffer->SetDesc(std::shared_ptr<DrawingResourceDesc>(desc.Clone()));
    pVertexBuffer->SetResource(pVertexBufferRaw);

    pRes = pVertexBuffer;
    return true;
}

bool DrawingDevice_D3D11::CreateIndexBuffer(const DrawingIndexBufferDesc& desc, std::shared_ptr<DrawingIndexBuffer>& pRes, std::shared_ptr<DrawingResource> pRefRes, const void* pData, uint32_t size)
{
    if ((pData != nullptr) && (size < desc.mSizeInBytes))
        return false;

    D3D11_BUFFER_DESC bufferDesc;
    bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bufferDesc.ByteWidth = desc.mSizeInBytes;
    bufferDesc.Usage = D3D11Enum(desc.mUsage);
    bufferDesc.CPUAccessFlags = D3D11Enum(desc.mAccess);
    bufferDesc.MiscFlags = D3D11Enum(desc.mFlags);
    bufferDesc.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA subResData;
    ZeroMemory(&subResData, sizeof(D3D11_SUBRESOURCE_DATA));
    subResData.pSysMem = pData;

    auto pIndexBuffer = std::make_shared<DrawingIndexBuffer>(std::shared_ptr<DrawingDevice>(this));

    auto pIndexBufferRaw = std::shared_ptr<DrawingRawIndexBuffer>(new DrawingRawIndexBuffer_D3D11(*this, bufferDesc, subResData, desc.mStrideInBytes, 0));
    pIndexBuffer->SetDesc(std::shared_ptr<DrawingResourceDesc>(desc.Clone()));
    pIndexBuffer->SetResource(pIndexBufferRaw);

    pRes = pIndexBuffer;
    return true;
}

bool DrawingDevice_D3D11::CreateTexture(const DrawingTextureDesc& desc, std::shared_ptr<DrawingTexture>& pRes, const void* pData, uint32_t size)
{
    return true;
}

bool DrawingDevice_D3D11::CreateBlendState(const DrawingBlendStateDesc& desc, std::shared_ptr<DrawingBlendState>& pRes)
{
    D3D11_BLEND_DESC blendDesc;
    for (uint32_t i = 0; i < MAX_TARGETS; ++i)
    {
        blendDesc.RenderTarget[i].BlendEnable = desc.mTargets[i].mBlendEnable;
        blendDesc.RenderTarget[i].SrcBlend = D3D11Enum(desc.mTargets[i].mColorBlend.mBlendSrc);
        blendDesc.RenderTarget[i].DestBlend = D3D11Enum(desc.mTargets[i].mColorBlend.mBlendDst);
        blendDesc.RenderTarget[i].BlendOp = D3D11Enum(desc.mTargets[i].mColorBlend.mBlendOp);
        blendDesc.RenderTarget[i].SrcBlendAlpha = D3D11Enum(desc.mTargets[i].mAlphaBlend.mBlendSrc);
        blendDesc.RenderTarget[i].DestBlendAlpha = D3D11Enum(desc.mTargets[i].mAlphaBlend.mBlendDst);
        blendDesc.RenderTarget[i].BlendOpAlpha = D3D11Enum(desc.mTargets[i].mAlphaBlend.mBlendOp);
        blendDesc.RenderTarget[i].RenderTargetWriteMask = desc.mTargets[i].mRenderTargetWriteMask;
    }
    blendDesc.AlphaToCoverageEnable = desc.mAlphaToCoverageEnable;
    blendDesc.IndependentBlendEnable = desc.mIndependentBlendEnable;

    auto pBlendState = std::make_shared<DrawingBlendState>(std::shared_ptr<DrawingDevice>(this));

    auto pBlendStateRaw = std::shared_ptr<DrawingRawBlendState>(new DrawingRawBlendState_D3D11(*this, blendDesc));
    pBlendState->SetDesc(std::shared_ptr<DrawingResourceDesc>(desc.Clone()));
    pBlendState->SetResource(pBlendStateRaw);

    pRes = pBlendState;
    return true;
}

bool DrawingDevice_D3D11::CreateDepthState(const DrawingDepthStateDesc& desc, std::shared_ptr<DrawingDepthState>& pRes)
{
    D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
    depthStencilDesc.DepthEnable = desc.mDepthState.mDepthEnable;
    depthStencilDesc.DepthWriteMask = desc.mDepthState.mDepthWriteEnable ? D3D11_DEPTH_WRITE_MASK_ALL : D3D11_DEPTH_WRITE_MASK_ZERO;
    depthStencilDesc.DepthFunc = D3D11Enum(desc.mDepthState.mDepthFunc);
    depthStencilDesc.StencilEnable = desc.mStencilState.mStencilEnable;
    depthStencilDesc.StencilReadMask = desc.mStencilState.mStencilReadMask;
    depthStencilDesc.StencilWriteMask = desc.mStencilState.mStencilWriteMask;
    depthStencilDesc.FrontFace.StencilFailOp = D3D11Enum(desc.mStencilState.mFrontFace.mStencilFailOp);
    depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11Enum(desc.mStencilState.mFrontFace.mStencilDepthFailOp);
    depthStencilDesc.FrontFace.StencilPassOp = D3D11Enum(desc.mStencilState.mFrontFace.mStencilPassOp);
    depthStencilDesc.FrontFace.StencilFunc = D3D11Enum(desc.mStencilState.mFrontFace.mStencilFunc);
    depthStencilDesc.BackFace.StencilFailOp = D3D11Enum(desc.mStencilState.mBackFace.mStencilFailOp);
    depthStencilDesc.BackFace.StencilDepthFailOp = D3D11Enum(desc.mStencilState.mBackFace.mStencilDepthFailOp);
    depthStencilDesc.BackFace.StencilPassOp = D3D11Enum(desc.mStencilState.mBackFace.mStencilPassOp);
    depthStencilDesc.BackFace.StencilFunc = D3D11Enum(desc.mStencilState.mBackFace.mStencilFunc);
    
    auto pDepthState = std::make_shared<DrawingDepthState>(std::shared_ptr<DrawingDevice>(this));

    auto pDepthStateRaw = std::shared_ptr<DrawingRawDepthState>(new DrawingRawDepthState_D3D11(*this, depthStencilDesc));
    pDepthState->SetDesc(std::shared_ptr<DrawingResourceDesc>(desc.Clone()));
    pDepthState->SetResource(pDepthStateRaw);

    pRes = pDepthState;
    return true;
}

bool DrawingDevice_D3D11::CreateRasterState(const DrawingRasterStateDesc& desc, std::shared_ptr<DrawingRasterState>& pRes)
{
    D3D11_RASTERIZER_DESC rasterizerDesc;
    rasterizerDesc.FillMode = D3D11Enum(desc.mFillMode);
    rasterizerDesc.CullMode = D3D11Enum(desc.mCullMode);
    rasterizerDesc.FrontCounterClockwise = desc.mFrontCounterClockwise;
    rasterizerDesc.DepthBias = desc.mDepthBias;
    rasterizerDesc.DepthBiasClamp = desc.mDepthBiasClamp;
    rasterizerDesc.SlopeScaledDepthBias = desc.mSlopeScaledDepthBias;
    rasterizerDesc.DepthClipEnable = desc.mDepthClipEnable;
    rasterizerDesc.ScissorEnable = desc.mScissorEnable;
    rasterizerDesc.MultisampleEnable = desc.mMultisampleEnable;
    rasterizerDesc.AntialiasedLineEnable = desc.mAntialiasedLineEnable;

    auto pRasterState = std::make_shared<DrawingRasterState>(std::shared_ptr<DrawingDevice>(this));

    auto pRasterStateRaw = std::shared_ptr<DrawingRawRasterState>(new DrawingRawRasterState_D3D11(*this, rasterizerDesc));
    pRasterState->SetDesc(std::shared_ptr<DrawingResourceDesc>(desc.Clone()));
    pRasterState->SetResource(pRasterStateRaw);

    pRes = pRasterState;
    return true;
}

bool DrawingDevice_D3D11::CreateSamplerState(const DrawingSamplerStateDesc& desc, std::shared_ptr<DrawingSamplerState>& pRes)
{
    D3D11_SAMPLER_DESC samplerDesc;
    samplerDesc.Filter = D3D11Enum(desc.mSamplerMode, desc.mMinFilter, desc.mMagFilter, desc.mMipFilter);
    samplerDesc.AddressU = D3D11Enum(desc.mAddressU);
    samplerDesc.AddressV = D3D11Enum(desc.mAddressV);
    samplerDesc.AddressW = D3D11Enum(desc.mAddressW);
    samplerDesc.MipLODBias = desc.mMipLODBias;
    samplerDesc.MaxAnisotropy = desc.mMaxAnisotropy;
    samplerDesc.ComparisonFunc = D3D11Enum(desc.mComparisonFunc);
    samplerDesc.BorderColor[0] = desc.mBorderColor[0];
    samplerDesc.BorderColor[1] = desc.mBorderColor[1];
    samplerDesc.BorderColor[2] = desc.mBorderColor[2];
    samplerDesc.BorderColor[3] = desc.mBorderColor[3];
    samplerDesc.MinLOD = desc.mMinLOD;
    samplerDesc.MaxLOD = desc.mMaxLOD;

    auto pSamplerState = std::make_shared<DrawingSamplerState>(std::shared_ptr<DrawingDevice>(this));

    auto pSamplerStateRaw = std::shared_ptr<DrawingRawSamplerState>(new DrawingRawSamplerState_D3D11(*this, samplerDesc));
    pSamplerState->SetDesc(std::shared_ptr<DrawingResourceDesc>(desc.Clone()));
    pSamplerState->SetResource(pSamplerStateRaw);

    pRes = pSamplerState;
    return true;
}

bool DrawingDevice_D3D11::CreateVertexShaderFromFile(const DrawingVertexShaderDesc& desc, std::shared_ptr<DrawingVertexShader>& pRes)
{
    assert(desc.mProgramType == eProgram_File);

    std::ifstream fstream(desc.mpSourceName->c_str(), std::ios::binary);
    if (!fstream)
        return false;

    std::string content((std::istreambuf_iterator<char>(fstream)), std::istreambuf_iterator<char>());

    return DoCreateVertexShader(desc, content.data(), (uint32_t)content.length(), pRes);
}

bool DrawingDevice_D3D11::CreateVertexShaderFromString(const std::string& str, const DrawingVertexShaderDesc& desc, std::shared_ptr<DrawingVertexShader>& pRes)
{
    assert(desc.mProgramType == eProgram_String);

    return DoCreateVertexShader(desc, str.data(), (uint32_t)str.length(), pRes);
}

bool DrawingDevice_D3D11::CreatePixelShaderFromFile(const DrawingPixelShaderDesc& desc, std::shared_ptr<DrawingPixelShader>& pRes)
{
    assert(desc.mProgramType == eProgram_File);

    std::ifstream fstream(desc.mpSourceName->c_str(), std::ios::binary);
    if (!fstream)
        return false;

    std::string content((std::istreambuf_iterator<char>(fstream)), std::istreambuf_iterator<char>());

    return DoCreatePixelShader(desc, content.data(), (uint32_t)content.length(), pRes);
}

bool DrawingDevice_D3D11::CreatePixelShaderFromString(const std::string& str, const DrawingPixelShaderDesc& desc, std::shared_ptr<DrawingPixelShader>& pRes)
{
    assert(desc.mProgramType == eProgram_String);

    return DoCreatePixelShader(desc, str.data(), (uint32_t)str.length(), pRes);
}

std::shared_ptr<ID3D11Device> DrawingDevice_D3D11::GetDevice() const
{
    return m_pDevice;
}

std::shared_ptr<IDXGIFactory> DrawingDevice_D3D11::GetDXGIFactory() const
{
    return m_pDXGIFactory;
}

template <typename DescType>
static bool GetBasicTypeInfo(const DescType& descType, uint32_t& dataSetType, uint32_t& rowSize, uint32_t& colSize, uint32_t& arraySize, uint32_t& structSize)
{
    bool isValid = true;
    switch (descType.Class)
    {
        case D3D_SVC_SCALAR:
        {
            dataSetType = eDataSet_Scalar;
            arraySize = descType.Elements;
            break;
        }
        case D3D_SVC_VECTOR:
        {
            dataSetType = eDataSet_Vector;
            rowSize = descType.Columns;
            arraySize = descType.Elements;
            break;
        }
        case D3D_SVC_MATRIX_COLUMNS:
        {
            dataSetType = eDataSet_Matrix;
            rowSize = descType.Columns;
            colSize = descType.Rows;
            arraySize = descType.Elements;
            break;
        }
        case D3D_SVC_MATRIX_ROWS:
        {
            dataSetType = eDataSet_Matrix;
            rowSize = descType.Rows;
            colSize = descType.Columns;
            arraySize = descType.Elements;
            break;
        }
        case D3D_SVC_OBJECT:
        {
            dataSetType = eDataSet_Object;
            arraySize = descType.Elements;
            break;
        }
        case D3D_SVC_STRUCT:
        {
            GetStructInfo(descType, dataSetType, structSize, arraySize);
            break;
        }
        default:
        {
            dataSetType = 0xffffffff;
            rowSize = 0;
            colSize = 0;
            arraySize = 0;
            structSize = 0;

            isValid = false;

        }
    }

    return isValid;
}

static void GetStructInfo(const D3D11_SHADER_TYPE_DESC& descType, uint32_t& dataSetType, uint32_t& arraySize, uint32_t& structSize)
{
    dataSetType = eDataSet_Struct;
    structSize = 0;
    arraySize = descType.Elements;
}

template <class DescType>
static uint32_t GenerateParamType(const DescType& descType, uint32_t dataSetType, uint32_t rowSize, uint32_t colSize, uint32_t arraySize, uint32_t structSize, uint32_t& dataSize)
{
    uint32_t paramType = (uint32_t)EParam_Invalid;

    if (dataSetType == eDataSet_Object)
    {
        switch (descType.Type)
        {
            case D3D_SVT_TEXTURE:
            case D3D_SVT_TEXTURE1D:
            case D3D_SVT_TEXTURE2D:
            case D3D_SVT_TEXTURE2DARRAY:
            case D3D_SVT_TEXTURE2DMS:
            case D3D_SVT_TEXTURE3D:
            case D3D_SVT_TEXTURECUBE:
            {
                paramType = COMPOSE_TYPE(eObject_Texture, eDataSet_Object, eBasic_FP32, 0, 0, 0);
                break;
            }
            case D3D_SVT_BYTEADDRESS_BUFFER:
            case D3D_SVT_STRUCTURED_BUFFER:
            {
                paramType = COMPOSE_TYPE(eObject_TexBuffer, eDataSet_Object, eBasic_FP32, 0, 0, 0);
                break;
            }
            case D3D_SVT_BUFFER:
            {
                paramType = COMPOSE_TYPE(eObject_Buffer, eDataSet_Object, eBasic_FP32, 0, 0, 0);
                break;
            }
            case D3D_SVT_RWBYTEADDRESS_BUFFER:
            case D3D_SVT_RWSTRUCTURED_BUFFER:
            {
                paramType = COMPOSE_TYPE(eObject_RWBuffer, eDataSet_Object, eBasic_FP32, 0, 0, 0);
                break;
            }
            case D3D_SVT_SAMPLER:
            case D3D_SVT_SAMPLER1D:
            case D3D_SVT_SAMPLER2D:
            case D3D_SVT_SAMPLER3D:
            case D3D_SVT_SAMPLERCUBE:
            {
                paramType = COMPOSE_TYPE(eObject_Sampler, eDataSet_Object, eBasic_FP32, 0, 0, 0);
                break;
            }
            default:
            {
                return (uint32_t)EParam_Invalid;
            }
        }
        dataSize = sizeof(void *);

    }
    else if (dataSetType == eDataSet_Struct)
    {
        paramType = COMPOSE_STRUCT_TYPE(eObject_Value, eDataSet_Struct, eBasic_FP32, 0, structSize);
        dataSize = structSize * arraySize;
    }
    else
    {
        uint32_t basicType = eBasic_FP32;
        switch (descType.Type)
        {
            case D3D_SVT_BOOL:
                basicType = eBasic_Bool;
                break;
            case D3D_SVT_INT:
                basicType = eBasic_Int32;
                break;
            case D3D_SVT_UINT:
                basicType = eBasic_UInt32;
                break;
            case D3D_SVT_FLOAT:
                basicType = eBasic_FP32;
                break;
            case D3D_SVT_DOUBLE:
                basicType = eBasic_FP64;
                break;
            default:
            {
                return (uint32_t)EParam_Invalid;
            }

        }

        paramType = COMPOSE_TYPE(eObject_Value, dataSetType, basicType, arraySize, colSize, rowSize);

        uint32_t t_array_size = arraySize == 0 ? 1 : arraySize;
        uint32_t t_row_size = rowSize == 0 ? 1 : rowSize;
        uint32_t t_col_size = colSize == 0 ? 1 : colSize;

        dataSize = GIParameter::BasicTypeSize[basicType] * t_row_size * t_col_size * t_array_size;
    }

    return paramType;
}

template<typename DescType>
uint32_t DrawingDevice_D3D11::GetParamType(const DescType& type, uint32_t& size)
{
    uint32_t dataSetType = eDataSet_Scalar;
    uint32_t rowSize = 0;
    uint32_t colSize = 0;
    uint32_t arraySize = 0;
    uint32_t structSize = 0;

    bool isValidType = GetBasicTypeInfo(descType, ataSetType, rowSize, colSize, arraySize, structSize);

    if (!isValidType)
        return (uint32_t)EParam_Invalid;

    return GenerateParamType(descType, dataSetType, rowSize, colSize, arraySize, structSize, dataSize);
}

bool DrawingDevice_D3D11::DoCreateVertexShader(const DrawingVertexShaderDesc& desc, const void* pData, uint32_t size, std::shared_ptr<DrawingVertexShader>& pRes)
{
    std::shared_ptr<std::string> pShaderName = desc.mpName;
    std::shared_ptr<std::string> pSourceName = desc.mpSourceName;

    auto pVertexShaderRaw = CreateVertexShaderFromBuffer(pShaderName, pSourceName, nullptr, pData, size);
    if (pVertexShaderRaw == nullptr)
        return false;

    auto pVertexShader = std::make_shared<DrawingVertexShader>(std::shared_ptr<DrawingDevice>(this));
    pVertexShader->SetDesc(std::shared_ptr<DrawingResourceDesc>(desc.Clone()));
    pVertexShader->SetResource(pVertexShaderRaw);
    
    pRes = pVertexShader;
    return true;
}

bool DrawingDevice_D3D11::DoCreatePixelShader(const DrawingPixelShaderDesc& desc, const void* pData, uint32_t size, std::shared_ptr<DrawingPixelShader>& pRes)
{
    std::shared_ptr<std::string> pShaderName = desc.mpName;
    std::shared_ptr<std::string> pSourceName = desc.mpSourceName;

    auto pPixelShaderRaw = CreatePixelShaderFromBuffer(pShaderName, pSourceName, nullptr, pData, size);
    if (pPixelShaderRaw == nullptr)
        return false;

    auto pPixelShader = std::make_shared<DrawingPixelShader>(std::shared_ptr<DrawingDevice>(this));
    pPixelShader->SetDesc(std::shared_ptr<DrawingResourceDesc>(desc.Clone()));
    pPixelShader->SetResource(pPixelShaderRaw);
    
    pRes = pPixelShader;
    return true;
}

std::shared_ptr<DrawingRawVertexShader_D3D11> DrawingDevice_D3D11::CreateVertexShaderFromBuffer(std::shared_ptr<std::string> pName, std::shared_ptr<std::string> pEntryName, std::shared_ptr<std::string> pSourceName, const void* pData, uint32_t size)
{
    assert(pName != nullptr && pData != nullptr);
    auto pVertexShader = CreateVertexShaderFromBlob(pName, pData, size);

    if (pVertexShader != nullptr)
        return pVertexShader;

    assert(pEntryName != nullptr);
    return CreateVertexShaderFromString(pName, pEntryName, pSourceName, static_cast<const char*>(pData), size);
}

std::shared_ptr<DrawingRawPixelShader_D3D11> DrawingDevice_D3D11::CreatePixelShaderFromBuffer(std::shared_ptr<std::string> pName, std::shared_ptr<std::string> pEntryName, std::shared_ptr<std::string> pSourceName, const void* pData, uint32_t size)
{
    assert(pName != nullptr && pData != nullptr);
    auto pPixelShader = CreatePixelShaderFromBlob(pName, pData, size);

    if (pPixelShader != nullptr)
        return pPixelShader;

    assert(pEntryName != nullptr);
    return CreatePixelShaderFromString(pName, pEntryName, pSourceName, static_cast<const char*>(pData), size);
}

std::shared_ptr<DrawingRawVertexShader_D3D11> DrawingDevice_D3D11::CreateVertexShaderFromBlob(std::shared_ptr<std::string> pName, const void* pShaderByteCode, uint32_t length)
{
    assert(pName != nullptr && pShaderByteCode != nullptr);

    ID3D11VertexShader* pVertexShader;
    ID3D11ShaderReflection* pReflection;

    HRESULT hr = m_pDevice->CreateVertexShader(pShaderByteCode, length, nullptr, &pVertexShader);
    if (!SUCCEEDED(hr))
        return nullptr;

    hr = D3DReflect(pShaderByteCode, length, IID_ID3D11ShaderReflection, (void**)&pReflection);
    if (!SUCCEEDED(hr))
        return nullptr;

    return std::shared_ptr<DrawingRawVertexShader_D3D11>(new DrawingRawVertexShader_D3D11(*this, pName, std::shared_ptr<ID3D11ShaderReflection>(pReflection), std::shared_ptr<ID3D11VertexShader>(pVertexShader)));
}

std::shared_ptr<DrawingRawPixelShader_D3D11> DrawingDevice_D3D11::CreatePixelShaderFromBlob(std::shared_ptr<std::string> pName, const void* pShaderByteCode, uint32_t length)
{
    assert(pName != nullptr && pShaderByteCode != nullptr);

    ID3D11PixelShader* pPixelShader;
    ID3D11ShaderReflection* pReflection;

    HRESULT hr = m_pDevice->CreatePixelShader(pShaderByteCode, length, nullptr, &pPixelShader);
    if (!SUCCEEDED(hr))
        return nullptr;

    hr = D3DReflect(pShaderByteCode, length, IID_ID3D11ShaderReflection, (void**)&pReflection);
    if (!SUCCEEDED(hr))
        return nullptr;

    return std::shared_ptr<DrawingRawPixelShader_D3D11>(new DrawingRawPixelShader_D3D11(*this, pName, std::shared_ptr<ID3D11ShaderReflection>(pReflection), std::shared_ptr<ID3D11PixelShader>(pPixelShader)));
}

std::shared_ptr<DrawingRawVertexShader_D3D11> DrawingDevice_D3D11::CreateVertexShaderFromString(std::shared_ptr<std::string> pName, std::shared_ptr<std::string> pEntryName, std::shared_ptr<std::string> pSourceName, const char* pSrc, uint32_t size)
{
    assert(pName != nullptr && pEntryName != nullptr && pSrc != nullptr);

    ID3DInclude* pInclude = (pSourceName == nullptr) ? nullptr : D3D_COMPILE_STANDARD_FILE_INCLUDE;
    DWORD flags = 0;
    ID3DBlob* pShaderBlob = nullptr;
    ID3DBlob* pErrorBlob = nullptr;

    HRESULT hr = D3DCompile(pSrc, size, pSourceName.get()->c_str(), nullptr, pInclude, pEntryName.get()->c_str(), "vs_5_0", flags, 0, &pShaderBlob, &pErrorBlob);
    if (!SUCCEEDED(hr))
        return nullptr;

    return CreateVertexShaderFromBlob(pName, pShaderBlob->GetBufferPointer(), (uint32_t)pShaderBlob->GetBufferSize());
}

std::shared_ptr<DrawingRawPixelShader_D3D11> DrawingDevice_D3D11::CreatePixelShaderFromString(std::shared_ptr<std::string> pName, std::shared_ptr<std::string> pEntryName, std::shared_ptr<std::string> pSourceName, const char* pSrc, uint32_t size)
{
    assert(pName != nullptr && pEntryName != nullptr && pSrc != nullptr);

    ID3DInclude* pInclude = (pSourceName == nullptr) ? nullptr : D3D_COMPILE_STANDARD_FILE_INCLUDE;
    DWORD flags = 0;
    ID3DBlob* pShaderBlob = nullptr;
    ID3DBlob* pErrorBlob = nullptr;

    HRESULT hr = D3DCompile(pSrc, size, pSourceName.get()->c_str(), nullptr, pInclude, pEntryName.get()->c_str(), "ps_5_0", flags, 0, &pShaderBlob, &pErrorBlob);
    if (!SUCCEEDED(hr))
        return nullptr;

    return CreatePixelShaderFromBlob(pName, pShaderBlob->GetBufferPointer(), (uint32_t)pShaderBlob->GetBufferSize());
}

bool DrawingDevice_D3D11::DrawPrimitive(std::shared_ptr<DrawingPrimitive> pRes)
{
    assert(pRes != nullptr);

    auto primType = D3D11Enum(pRes->GetPrimitiveType());
    auto indexCount = pRes->GetIndexCount();
    auto instanceCount = pRes->GetInstanceCount();

    m_pDeviceContext->IASetPrimitiveTopology(primType);

    if (instanceCount != 0)
    {
        if (indexCount != 0)
            m_pDeviceContext->DrawIndexedInstanced(indexCount, instanceCount, pRes->GetIndexOffset(), 0, pRes->GetInstanceOffset());
        else
            m_pDeviceContext->DrawInstanced(pRes->GetVertexCount(), pRes->GetInstanceCount(), pRes->GetVertexOffset(), pRes->GetInstanceOffset());
    }
    else
    {
        if (indexCount != 0)
            m_pDeviceContext->DrawIndexed(indexCount, pRes->GetIndexOffset(), 0);
        else
            m_pDeviceContext->Draw(pRes->GetVertexCount(), pRes->GetVertexOffset());
    }

    return true;
}

bool DrawingDevice_D3D11::Present(const std::shared_ptr<DrawingTarget> pTarget, uint32_t syncInterval)
{
    auto pSwapChainRaw = std::static_pointer_cast<DrawingRawSwapChain_D3D11>(pTarget->GetResource());
    assert(pSwapChainRaw != nullptr);

    HRESULT hr = pSwapChainRaw->Present(syncInterval);
    if (!SUCCEEDED(hr))
        return false;

    return true;
}
