#include "DrawingRawResource_D3D11.h"

using namespace Engine;

void DrawingRawShader_D3D11::ProcessVariables(std::shared_ptr<std::string> pName, uint32_t size, ID3D11ShaderReflectionConstantBuffer* pBuffer, uint32_t count)
{
    for (uint32_t i = 0; i < count; ++i)
    {
        ID3D11ShaderReflectionVariable* pD3D11Var = pBuffer->GetVariableByIndex(i);
        D3D11_SHADER_VARIABLE_DESC varDesc;
        pD3D11Var->GetDesc(&varDesc);

        if (0 == (varDesc.uFlags & D3D_SVF_USED))
            continue;

        VariableDesc imp;
        imp.mpName = std::shared_ptr<std::string>(new std::string(varDesc.Name));
        imp.mpCBName = pName;
        imp.mOffset = varDesc.StartOffset;
        imp.mSizeInBytes = varDesc.Size;
        imp.mCBSizeInBytes = size;

        ID3D11ShaderReflectionType* pD3D11Type = pD3D11Var->GetType();
        D3D11_SHADER_TYPE_DESC typeDesc;
        pD3D11Type->GetDesc(&typeDesc);

        uint32_t dataSize = 0;
        imp.mParamType = DrawingDevice_D3D11::GetParamType(typeDesc, dataSize);
        if (dataSize < 4)
            dataSize = 4;
        assert(dataSize == varDesc.Size);

        mVariableTable.emplace(imp.mpName, imp);
    }
}

void DrawingRawShader_D3D11::BuildResourceBindingTable(DrawingRawShader::DrawingRawShaderType type)
{
    D3D11_SHADER_DESC desc;
    m_pReflection->GetDesc(&desc);

    for (uint32_t i = 0; i < desc.BoundResources; ++i)
    {
        D3D11_SHADER_INPUT_BIND_DESC resDesc;
        m_pReflection->GetResourceBindingDesc(i, &resDesc);

        ShaderResourceDesc imp;
        imp.mStartSlot = resDesc.BindPoint;
        imp.mCount = resDesc.BindCount;
        imp.mpName = std::shared_ptr<std::string>(new std::string(resDesc.Name));

        switch(resDesc.Type)
        {
            case D3D_SIT_CBUFFER:
            {
                assert(imp.mCount == 1);
                assert(imp.mStartSlot < D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT);
                mCBTable.emplace(imp.mpName, imp);

                ID3D11ShaderReflectionConstantBuffer* pD3D11CB = m_pReflection->GetConstantBufferByName(resDesc.Name);
                D3D11_SHADER_BUFFER_DESC bufDesc;
                pD3D11CB->GetDesc(&bufDesc);
                imp.mSizeInBytes = bufDesc.Size;
                ProcessVariables(imp.mpName, bufDesc.Size, pD3D11CB, bufDesc.Variables);
                break;
            }
            case D3D_SIT_STRUCTURED:
            {
                assert(imp.mStartSlot + imp.mCount < D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT);
                mTexBufferTable.emplace(imp.mpName, imp);
                break;
            }
            case D3D_SIT_TBUFFER:
            case D3D_SIT_TEXTURE:
            case D3D_SIT_BYTEADDRESS:
            {
                assert(imp.mStartSlot + imp.mCount < D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT);
                mTextureTable.emplace(imp.mpName, imp);
                break;
            }
            case D3D_SIT_UAV_RWTYPED:
            case D3D_SIT_UAV_RWSTRUCTURED:
            case D3D_SIT_UAV_RWBYTEADDRESS:
            case D3D_SIT_UAV_APPEND_STRUCTURED:
            case D3D_SIT_UAV_CONSUME_STRUCTURED:
            case D3D_SIT_UAV_RWSTRUCTURED_WITH_COUNTER:
            {
                assert(imp.mStartSlot + imp.mCount < D3D11_PS_CS_UAV_REGISTER_COUNT);
                mUVATable.emplace(imp.mpName, imp);
                break;
            }
            case D3D_SIT_SAMPLER:
            {
                assert(imp.mStartSlot + imp.mCount < D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT);
                mSamplerTable.emplace(imp.mpName, imp);
                break;
            }
            default:
                break;
        }
    }
}