#pragma once

#include <memory>
#include <string>

namespace Engine
{
    class ITexture
    {
    public:
        ITexture() {}
        virtual ~ITexture() = default;

        virtual std::string GetURI() const = 0;
        virtual void SetURI(std::string uri) = 0;
    };
}