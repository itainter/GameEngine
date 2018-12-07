#include "DrawingUtil_D3D11.h"
#include "DrawingRawResource_D3D11.h"
#include "DrawingDevice_D3D11.h"

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