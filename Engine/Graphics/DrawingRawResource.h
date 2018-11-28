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
    protected:
        virtual ~DrawingRawBlendState() = default;
    };

    class DrawingRawDepthState
    {
    protected:
        virtual ~DrawingRawDepthState() = default;
    };

    class DrawingRawRasterState
    {
    protected:
        virtual ~DrawingRawRasterState() = default;
    };

    class DrawingRawSamplerState
    {
    protected:
        virtual ~DrawingRawSamplerState() = default;
    };

    class DrawingRawTexture
    {
    protected:
        virtual ~DrawingRawTexture() = default;

    public:
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
    protected:
        DrawingRawShader(std::shared_ptr<const std::string> pShaderName) : m_pShaderName(pShaderName) {}
        virtual ~DrawingRawShader() { m_pShaderName = nullptr; };

        enum DrawingRawShaderType
        {
            RawShader_VS,
            RawShader_PS,
            RawShader_CS,
        };

        virtual DrawingRawShaderType GetShaderType() const = 0;

    private:
        std::shared_ptr<const std::string> m_pShaderName;
    };

    class DrawingRawVertexShader : public DrawingRawShader
    {
    public:
        DrawingRawShaderType GetShaderType() const override { return RawShader_VS; }
    };

    class DrawingRawPixelShader : public DrawingRawShader
    {
    public:
        DrawingRawShaderType GetShaderType() const override { return RawShader_PS; }
    };

    class DrawingRawComputeShader : public DrawingRawShader
    {
    public:
        DrawingRawShaderType GetShaderType() const override { return RawShader_CS; }
    };

    class DrawingRawVertexFormat
    {
    protected:
        virtual ~DrawingRawVertexFormat() = default;
    };

    class DrawingRawVertexBuffer
    {
    protected:
        virtual ~DrawingRawVertexBuffer() = default;
    };

    class DrawingRawIndexBuffer
    {
    protected:
        virtual ~DrawingRawIndexBuffer() = default;
    };

    class DrawingRawTarget
    {
    protected:
        virtual ~DrawingRawTarget() = default;
    };
}