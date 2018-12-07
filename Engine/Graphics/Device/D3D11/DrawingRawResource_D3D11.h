#pragma once

#include <vector>
#include <d3d11.h>
#include <assert.h>

#include "DrawingDevice_D3D11.h"
#include "DrawingRawResource.h"

namespace Engine
{
    class DrawingRawVertexFormat_D3D11 : public DrawingRawVertexFormat
    {
    public:
        DrawingRawVertexFormat_D3D11(const DrawingDevice_D3D11& device, const std::vector<D3D11_INPUT_ELEMENT_DESC>& desc,
                                     const void* pShaderBytecodeWithInputSignature, uint32_t byteCodeLength) : m_device(device)
        {
            ID3D11InputLayout* pRaw = m_pInputLayout.get();
            HRESULT hr = m_device.GetDevice()->CreateInputLayout(desc.data(), static_cast<UINT>(desc.size()), pShaderBytecodeWithInputSignature, byteCodeLength, &pRaw);
            assert(SUCCEEDED(hr));
        }

        std::shared_ptr<ID3D11InputLayout> Get() const
        {
            return m_pInputLayout;
        }

    private:
        const DrawingDevice_D3D11& m_device;
        std::shared_ptr<ID3D11InputLayout> m_pInputLayout;
    };
}