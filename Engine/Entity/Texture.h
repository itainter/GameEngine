#pragma once

#include <string>

#include "ITexture.h"
#include "DrawingDevice.h"

namespace Engine
{
    class Texture : public ITexture
    {
    public:
        Texture();
        Texture(std::string uri);
        virtual ~Texture();

        std::string GetURI() const override;
        void SetURI(std::string uri) override;

    protected:
        std::string m_uri;
        std::weak_ptr<DrawingTexture> m_pTexture;
    };
}