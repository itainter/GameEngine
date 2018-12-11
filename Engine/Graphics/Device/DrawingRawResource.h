#pragma once

#include <memory>
#include <string>

namespace Engine
{
    class DrawingNativeContext
    {
    };

    class DrawingRawBlendState
    {
    public:
        virtual ~DrawingRawBlendState() = default;
    };

    class DrawingRawDepthState
    {
    public:
        virtual ~DrawingRawDepthState() = default;
    };

    class DrawingRawRasterState
    {
    public:
        virtual ~DrawingRawRasterState() = default;
    };

    class DrawingRawSamplerState
    {
    public:
        virtual ~DrawingRawSamplerState() = default;
    };

    class DrawingRawTexture
    {
    public:
        virtual ~DrawingRawTexture() = default;

        const std::shared_ptr<DrawingRawSamplerState>& GetSamplerState()
        {
            return m_pSamplerState;
        }

        void SetSamplerState(std::shared_ptr<DrawingRawSamplerState> pSamplerState)
        {
            m_pSamplerState = pSamplerState;
        }

    private:
        std::shared_ptr<DrawingRawSamplerState> m_pSamplerState;
    };

    class DrawingRawShader
    {
    public:
        DrawingRawShader(std::shared_ptr<const std::string> pShaderName) : m_pShaderName(pShaderName) {}
        virtual ~DrawingRawShader() { m_pShaderName = nullptr; };

        enum DrawingRawShaderType
        {
            RawShader_VS,
            RawShader_PS,
            RawShader_CS,
            RawShader_Count,
        };

        virtual DrawingRawShaderType GetShaderType() const = 0;

    private:
        std::shared_ptr<const std::string> m_pShaderName;
    };

    class DrawingRawEffect
    {
    protected:
        std::shared_ptr<const std::string> m_pEffectName;

    public:
        DrawingRawEffect(std::shared_ptr<const std::string> pEffectName) : m_pEffectName(pEffectName) {}
        virtual ~DrawingRawEffect()
        {
            m_pEffectName = nullptr;
        }

        virtual void Apply() = 0;
        virtual void Terminate() = 0;
    };

    class DrawingRawVertexShader : public DrawingRawShader
    {
    public:
        DrawingRawVertexShader(std::shared_ptr<const std::string> pShaderName) : DrawingRawShader(pShaderName) {}
        DrawingRawShaderType GetShaderType() const override { return RawShader_VS; }
    };

    class DrawingRawPixelShader : public DrawingRawShader
    {
    public:
        DrawingRawPixelShader(std::shared_ptr<const std::string> pShaderName) : DrawingRawShader(pShaderName) {}
        DrawingRawShaderType GetShaderType() const override { return RawShader_PS; }
    };

    class DrawingRawComputeShader : public DrawingRawShader
    {
    public:
        DrawingRawComputeShader(std::shared_ptr<const std::string> pShaderName) : DrawingRawShader(pShaderName) {}
        DrawingRawShaderType GetShaderType() const override { return RawShader_CS; }
    };

    class DrawingRawVertexFormat
    {
    public:
        virtual ~DrawingRawVertexFormat() = default;
    };

    class DrawingRawVertexBuffer
    {
    public:
        virtual ~DrawingRawVertexBuffer() = default;
    };

    class DrawingRawIndexBuffer
    {
    public:
        virtual ~DrawingRawIndexBuffer() = default;
    };

    class DrawingRawTarget
    {
    public:
        enum ETargetType
        {
            eTarget_OffScreen,
            eTarget_SwapChain,
            eTarget_Depth,
        };

        virtual ~DrawingRawTarget() = default;
    };
}