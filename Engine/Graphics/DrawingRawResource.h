#pragma once

#include <memory>
#include <string>

namespace Engine
{
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

    class DrawingRawSamplarState
    {
    protected:
        virtual ~DrawingRawSamplarState() = default;
    };

    class DrawingRawTexture
    {
    protected:
        virtual ~DrawingRawTexture() = default;

    public:
        const std::shared_ptr<DrawingRawSamplarState>& GetSamplarState()
        {
            return m_pSamplarState;
        }

        void SetSamplarState(std::shared_ptr<DrawingRawSamplarState> pSamplarState)
        {
            m_pSamplarState = pSamplarState;
        }

    private:
        std::shared_ptr<DrawingRawSamplarState> m_pSamplarState;
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