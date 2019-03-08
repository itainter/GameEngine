#include <array>

#include "Macros.h"
#include "DrawingRawResource_D3D11.h"

using namespace Engine;

static void UpdateValue(DrawingParameter* pParam, ID3DX11EffectVariable* pVar)
{
    auto pData = pParam->GetValuePtr();
    auto dataSize = pParam->GetValueSize();

    pVar->SetRawValue(pData, 0, dataSize);
}

static void UpdateTexture(DrawingParameter* pParam, ID3DX11EffectVariable* pVar)
{
    ID3DX11EffectShaderResourceVariable* pTexVar = pVar->AsShaderResource();
    if (pTexVar == nullptr) return;

    auto pTex = static_cast<const DrawingRawTexture_D3D11*>(pParam->AsTexture());
    pTexVar->SetResource(pTex != nullptr ? pTex->GetShaderResourceView().get() : nullptr);
}

static void UpdateBuffer(DrawingParameter* pParam, ID3DX11EffectVariable* pVar)
{
    ID3DX11EffectShaderResourceVariable* pTexVar = pVar->AsShaderResource();
    if (pTexVar == nullptr) return;

    auto pBuffer = static_cast<const DrawingRawTexBuffer_D3D11*>(pParam->AsBuffer());
    pTexVar->SetResource(pBuffer != nullptr ? pBuffer->GetShaderResourceView().get() : nullptr);
}

static void UpdateOutputRWBuffer(DrawingParameter* pParam, ID3DX11EffectVariable* pVar)
{
    ID3DX11EffectUnorderedAccessViewVariable* pUAV = pVar->AsUnorderedAccessView();
    if (pUAV == nullptr) return;

    auto pRWBuffer = static_cast<const DrawingRawRWBuffer_D3D11*>(pParam->AsRWBuffer());
    pUAV->SetUnorderedAccessView(pRWBuffer != nullptr ? pRWBuffer->GetUnorderedAccessView().get() : nullptr);
}

static void UpdateInputRWBuffer(DrawingParameter* pParam, ID3DX11EffectVariable* pVar)
{
    auto pSRV = pVar->AsShaderResource();
    if (pSRV == nullptr) return;

    auto pRWBuffer = static_cast<const DrawingRawRWBuffer_D3D11*>(pParam->AsRWBuffer());
    pSRV->SetResource(pRWBuffer != nullptr ? pRWBuffer->GetShaderResourceView().get() : nullptr);
}

static void UpdateTexBuffer(DrawingParameter* apParam, ID3DX11EffectVariable* apVar)
{
    auto* lpTexBufferVar = apVar->AsShaderResource();
    if (nullptr == lpTexBufferVar) return;

    auto pTexBuffer = static_cast<const DrawingRawTexBuffer_D3D11*>(apParam->AsTexBuffer());
    lpTexBufferVar->SetResource(pTexBuffer != nullptr ? pTexBuffer->GetShaderResourceView().get() : nullptr);
}

static void UpdateSampler(DrawingParameter* pParam, ID3DX11EffectVariable* pVar)
{
    ID3DX11EffectSamplerVariable* pSampler = pVar->AsSampler();
    if (pSampler == nullptr) return;

    auto pState = static_cast<const DrawingRawSamplerState_D3D11*>(pParam->AsSampler());
    pSampler->SetSampler(0, pState != nullptr ? pState->Get().get() : nullptr);
}

void DrawingRawFxEffect_D3D11::SParamVar::UpdateParamValue(const DrawingRawFxEffect_D3D11* apEffect)
{
    assert(m_pParam != nullptr);
    assert(mpVar != nullptr);

    auto paramType = m_pParam->GetType();
    auto objType = DrawingParameter::GetObjectType(paramType);

    switch (objType)
    {
        case EObjectType::eObject_Value: UpdateValue(m_pParam.get(), mpVar); break;
        case EObjectType::eObject_Texture: UpdateTexture(m_pParam.get(), mpVar); break;
        case EObjectType::eObject_Buffer: UpdateBuffer(m_pParam.get(), mpVar); break;
        case EObjectType::eObject_TexBuffer: UpdateTexBuffer(m_pParam.get(), mpVar); break;

        case EObjectType::eObject_RWBuffer:
        {
            if (apEffect->m_inputRWBufferNames.find(m_pParam->GetName()) != apEffect->m_inputRWBufferNames.cend())
                UpdateInputRWBuffer(m_pParam.get(), mpVar);
            else if (apEffect->m_outputRWBufferNames.find(m_pParam->GetName()) != apEffect->m_outputRWBufferNames.cend())
                UpdateOutputRWBuffer(m_pParam.get(), mpVar);
            break;
        }
    }
}

void DrawingRawFxEffect_D3D11::Apply()
{
    std::for_each(mVarList.begin(), mVarList.end(), [this](SParamVar& aVar) { aVar.UpdateParamValue(this); });

    if (m_bComputeShaderPass)
    {
        m_pPass->Apply(0, m_pDevice->GetDeviceContext().get());
        return;
    }

    std::array<ID3D11UnorderedAccessView*, DrawingDevice_D3D11::MAX_UAV_SLOT_COUNT> lpUAView;
    m_pDevice->GetDeviceContext()->OMGetRenderTargetsAndUnorderedAccessViews(0, nullptr, nullptr, 0, DrawingDevice_D3D11::MAX_UAV_SLOT_COUNT, lpUAView.data());
    m_pPass->Apply(0, m_pDevice->GetDeviceContext().get());

    auto lpFirtUAView = std::find_if(lpUAView.cbegin(), lpUAView.cend(), [](const ID3D11UnorderedAccessView* apUAView) { return apUAView != nullptr; });
    if (lpFirtUAView != lpUAView.cend())
    {
        UINT lUAVStartSlot = static_cast<UINT>(lpFirtUAView - lpUAView.cbegin());
        UINT lNumUAVs = DrawingDevice_D3D11::MAX_UAV_SLOT_COUNT - lUAVStartSlot;
        m_pDevice->GetDeviceContext()->OMSetRenderTargetsAndUnorderedAccessViews(D3D11_KEEP_RENDER_TARGETS_AND_DEPTH_STENCIL, nullptr, nullptr, lUAVStartSlot, lNumUAVs, &(*lpFirtUAView), nullptr);
        std::for_each(lpUAView.begin(), lpUAView.end(), [](ID3D11UnorderedAccessView* apUAView) {if (apUAView != nullptr) apUAView->Release(); });
    }
}

void DrawingRawFxEffect_D3D11::Terminate()
{
}

void DrawingRawFxEffect_D3D11::BuildEffect()
{
    LoadTechAndPass();
    BuildParameterSet();
}

void DrawingRawFxEffect_D3D11::LoadTechAndPass()
{
    m_pTech = std::shared_ptr<ID3DX11EffectTechnique>(m_pEffect->GetTechniqueByName(m_pTechName->c_str()), D3D11Releaser<ID3DX11EffectTechnique>);
    if (m_pTech != nullptr)
    {
        m_pPass = std::shared_ptr<ID3DX11EffectPass>(m_pTech->GetPassByIndex(0), D3D11Releaser<ID3DX11EffectPass>);

        if (m_pPass != nullptr)
        {
            D3DX11_PASS_DESC passDesc;
            m_pPass->GetDesc(&passDesc);

            m_pInputSignature = passDesc.pIAInputSignature;
            m_byteCodeLength = passDesc.IAInputSignatureSize;

            D3DX11_PASS_SHADER_DESC lCSDesc;
            if (SUCCEEDED(m_pPass->GetComputeShaderDesc(&lCSDesc)))
            {
                ID3D11ComputeShader* lpCS;
                lCSDesc.pShaderVariable->GetComputeShader(lCSDesc.ShaderIndex, &lpCS);
                m_bComputeShaderPass = lpCS != nullptr;
            }
        }
    }
}

void DrawingRawFxEffect_D3D11::BuildParameterSet()
{
    D3DX11_EFFECT_DESC desc;
    m_pEffect->GetDesc(&desc);

    m_pParamSet->Clear();
    mVarList.clear();

    for (unsigned int i = 0; i < desc.GlobalVariables; i++)
    {
        ID3DX11EffectVariable* pVar = m_pEffect->GetVariableByIndex(i);
        ProcessVariable(pVar);
    }
}

void DrawingRawFxEffect_D3D11::ProcessVariable(ID3DX11EffectVariable* pVar)
{
    D3DX11_EFFECT_VARIABLE_DESC desc;
    pVar->GetDesc(&desc);

    D3DX11_EFFECT_TYPE_DESC descType;
    pVar->GetType()->GetDesc(&descType);

    uint32_t dataSize = 0;
    auto paramType = DrawingDevice_D3D11::GetParamType(descType, dataSize);

    if (paramType != EParamType::EParam_Invalid)
    {
        void* pInitData{ nullptr };

        if (paramType != EParamType::EParam_Texture &&
            paramType != EParamType::EParam_Buffer &&
            paramType != EParamType::EParam_RWBuffer &&
            paramType != EParamType::EParam_Sampler &&
            paramType != EParamType::EParam_TexBuffer)
        {
            static std::vector<char> initData;
            initData.resize(dataSize);
            pInitData = &initData[0];
            pVar->GetRawValue(pInitData, 0, dataSize);
        }

        auto pParam = std::make_shared<DrawingParameter>(std::make_shared<std::string>(desc.Name), paramType, pInitData, std::make_shared<std::string>(desc.Semantic));
        m_pParamSet->Add(pParam);
        mVarList.emplace_back(SParamVar(pParam, pVar));
    }
}

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
        imp.mpName = strPtr(varDesc.Name);
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
        imp.mpName = strPtr(resDesc.Name);

        switch (resDesc.Type)
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

DrawingRawShaderEffect_D3D11::DrawingRawShaderEffect_D3D11(std::shared_ptr<DrawingDevice_D3D11> pDevice, std::shared_ptr<std::string> pEffectName, const std::vector<std::shared_ptr<DrawingRawShader>>& shaders) :
    DrawingRawEffect_D3D11(pDevice, pEffectName)
{
    for (auto& shader : shaders)
    {
        const auto type = shader->GetShaderType();
        m_shaderBlocks[type] = std::make_shared<ShaderBlock>();

        DrawingRawShader_D3D11* shaderImpl = nullptr;
        switch (type)
        {
            case DrawingRawShader::RawShader_VS:
            {
                auto vsShader = std::static_pointer_cast<DrawingRawVertexShader_D3D11>(shader);
                assert(vsShader != nullptr);

                shaderImpl = vsShader->GetShaderImpl();
                m_shaderBlocks[type]->mpShader = shader;
                break;
            }
            case DrawingRawShader::RawShader_PS:
            {
                auto psShader = std::static_pointer_cast<DrawingRawPixelShader_D3D11>(shader);
                assert(psShader != nullptr);

                shaderImpl = psShader->GetShaderImpl();
                m_shaderBlocks[type]->mpShader = shader;
                break;
            }
            default:
                break;
        }
    }
}

DrawingRawShaderEffect_D3D11::DrawingRawShaderEffect_D3D11(std::shared_ptr<DrawingDevice_D3D11> pDevice, std::shared_ptr<std::string> pEffectName, std::shared_ptr<DrawingRawVertexShader_D3D11> pVertexShader, std::shared_ptr<DrawingRawPixelShader_D3D11> pPixelShader) :
    DrawingRawEffect_D3D11(pDevice, pEffectName)
{
    assert(pVertexShader != nullptr && pPixelShader != nullptr);

    auto vsShaderImpl = pVertexShader->GetShaderImpl();
    auto psShaderImpl = pPixelShader->GetShaderImpl();

    if (vsShaderImpl != nullptr)
    {
        m_shaderBlocks[DrawingRawShader::RawShader_VS] = std::make_shared<ShaderBlock>();
        m_shaderBlocks[DrawingRawShader::RawShader_VS]->mpShader = pVertexShader;
    }
    if (psShaderImpl != nullptr)
    {
        m_shaderBlocks[DrawingRawShader::RawShader_PS] = std::make_shared<ShaderBlock>();
        m_shaderBlocks[DrawingRawShader::RawShader_PS]->mpShader = pPixelShader;
    }
}

void DrawingRawShaderEffect_D3D11::Apply()
{
    UpdateParameterValues();
    UpdateConstantBuffers();
    UpdateDevice();
}

void DrawingRawShaderEffect_D3D11::Terminate()
{
}

void DrawingRawShaderEffect_D3D11::SParamVar::UpdateValues(void)
{
}

void DrawingRawShaderEffect_D3D11::UpdateParameterValues()
{
    for (auto& item : mVarTable)
        item.second.UpdateValues();
}

void DrawingRawShaderEffect_D3D11::UpdateConstantBuffers()
{
}

void DrawingRawShaderEffect_D3D11::UpdateDevice()
{
    for (auto& shaderBlock : m_shaderBlocks)
    {
        if (!shaderBlock)
            continue;

        auto type = shaderBlock->mpShader->GetShaderType();
        SetConstBufferSlots(*shaderBlock, type);
        SetTextureSlots(*shaderBlock, type);
        SetSamplerSlots(*shaderBlock, type);
        SetTexBufferSlots(*shaderBlock, type);
        SetRWBufferSlots(*shaderBlock, type);

        switch (type)
        {
        case DrawingRawShader::RawShader_CS:
            UpdateComputeShader(*shaderBlock);
            break;
        case DrawingRawShader::RawShader_VS:
            UpdateVertexShader(*shaderBlock);
            break;
        case DrawingRawShader::RawShader_PS:
            UpdatePixelShader(*shaderBlock);
            break;
        default:
            assert(false);
            break;
        }
    }
}

void DrawingRawShaderEffect_D3D11::UpdateComputeShader(const ShaderBlock& shaderBlock) const
{
    auto context = m_pDevice->GetDeviceContext();

    context->CSSetConstantBuffers(0, shaderBlock.mCBSlotsCount + 1, shaderBlock.mCBSlots.data());
    context->CSSetSamplers(0, shaderBlock.mSamplerSlotsCount + 1, shaderBlock.mSamplerSlots.data());
    context->CSSetShaderResources(0, shaderBlock.mSRVSlotsCount + 1, shaderBlock.mSRVSlots.data());
    context->CSSetUnorderedAccessViews(0, shaderBlock.mUAVSlotsCount + 1, shaderBlock.mUAVSlots.data(), nullptr);
    context->CSSetShader(std::static_pointer_cast<DrawingRawComputeShader_D3D11>(shaderBlock.mpShader)->GetShader(), nullptr, 0);
}

void DrawingRawShaderEffect_D3D11::UpdateVertexShader(const ShaderBlock& shaderBlock) const
{
    auto context = m_pDevice->GetDeviceContext();

    context->VSSetConstantBuffers(0, shaderBlock.mCBSlotsCount + 1, shaderBlock.mCBSlots.data());
    context->VSSetSamplers(0, shaderBlock.mSamplerSlotsCount + 1, shaderBlock.mSamplerSlots.data());
    context->VSSetShaderResources(0, shaderBlock.mSRVSlotsCount + 1, shaderBlock.mSRVSlots.data());
    context->VSSetShader(std::static_pointer_cast<DrawingRawVertexShader_D3D11>(shaderBlock.mpShader)->GetShader(), nullptr, 0);
}

void DrawingRawShaderEffect_D3D11::UpdatePixelShader(const ShaderBlock& shaderBlock) const
{
    auto context = m_pDevice->GetDeviceContext();

    context->PSSetConstantBuffers(0, shaderBlock.mCBSlotsCount + 1, shaderBlock.mCBSlots.data());
    context->PSSetSamplers(0, shaderBlock.mSamplerSlotsCount + 1, shaderBlock.mSamplerSlots.data());
    context->PSSetShaderResources(0, shaderBlock.mSRVSlotsCount + 1, shaderBlock.mSRVSlots.data());
    context->PSSetShader(std::static_pointer_cast<DrawingRawPixelShader_D3D11>(shaderBlock.mpShader)->GetShader(), nullptr, 0);
}

void DrawingRawShaderEffect_D3D11::SetConstBufferSlots(ShaderBlock& shaderBlock, const DrawingRawShader::DrawingRawShaderType shaderType)
{
    for (auto& item : mConstBufferTable)
    {
        auto& constDesc = item.second;
        if (constDesc.mStartSlot[shaderType] == EMPTY_SLOT)
            continue;
    }
}

void DrawingRawShaderEffect_D3D11::SetTextureSlots(ShaderBlock& shaderBlock, const DrawingRawShader::DrawingRawShaderType shaderType)
{
}

void DrawingRawShaderEffect_D3D11::SetSamplerSlots(ShaderBlock& shaderBlock, const DrawingRawShader::DrawingRawShaderType shaderType)
{
}

void DrawingRawShaderEffect_D3D11::SetTexBufferSlots(ShaderBlock& shaderBlock, const DrawingRawShader::DrawingRawShaderType shaderType)
{
}

void DrawingRawShaderEffect_D3D11::SetRWBufferSlots(ShaderBlock& shaderBlock, const DrawingRawShader::DrawingRawShaderType shaderType)
{
}