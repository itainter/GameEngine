#include <d3d11shader.h>

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

    pVertexFormat->SetDesc(std::shared_ptr<DrawingResourceDesc>(desc.Clone()));

    return true;
}

bool DrawingDevice_D3D11::CreateVertexBuffer(const DrawingVertexBufferDesc& desc, std::shared_ptr<DrawingVertexBuffer>& pRes, const void* pData, uint32_t size)
{
    return true;
}

bool DrawingDevice_D3D11::CreateIndexBuffer(const DrawingIndexBufferDesc& desc, std::shared_ptr<DrawingIndexBuffer>& pRes, const void* pData, uint32_t size)
{
    return true;
}

bool DrawingDevice_D3D11::CreateTexture(const DrawingTextureDesc& desc, std::shared_ptr<DrawingTexture>& pRes, const void* pData, uint32_t size)
{
    return true;
}

bool DrawingDevice_D3D11::CreateBlendState(const DrawingBlendStateDesc& desc, std::shared_ptr<DrawingBlendState>& pRes)
{
    return true;
}

bool DrawingDevice_D3D11::CreateDepthState(const DrawingDepthStateDesc& desc, std::shared_ptr<DrawingDepthState>& pRes)
{
    return true;
}

bool DrawingDevice_D3D11::CreateRasterState(const DrawingRasterStateDesc& desc, std::shared_ptr<DrawingRasterState>& pRes)
{
    return true;
}

bool DrawingDevice_D3D11::CreateSamplerState(const DrawingSamplerStateDesc& desc, std::shared_ptr<DrawingSamplerState>& pRes)
{
    return true;
}

bool DrawingDevice_D3D11::CreateVertexShaderFromFile(const DrawingVertexShaderDesc& desc, std::shared_ptr<DrawingVertexShader>& pRes)
{
    return true;
}

bool DrawingDevice_D3D11::CreateVertexShaderFromString(const std::string& str, const DrawingVertexShaderDesc& desc, std::shared_ptr<DrawingVertexShader>& pRes)
{
    return true;
}

bool DrawingDevice_D3D11::CreatePixelShaderFromFile(const DrawingPixelShaderDesc& desc, std::shared_ptr<DrawingPixelShader>& pRes)
{
    return true;
}

bool DrawingDevice_D3D11::CreatePixelShaderFromString(const std::string& str, const DrawingPixelShaderDesc& desc, std::shared_ptr<DrawingPixelShader>& pRes)
{
    return true;
}

bool DrawingDevice_D3D11::CreatePrimitiveInfo(const DrawingPrimitiveDesc& desc, std::shared_ptr<DrawingPrimitive>& pRes)
{
    return true;
}

std::shared_ptr<ID3D11Device> DrawingDevice_D3D11::GetDevice() const
{
    return m_pDevice;
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

}