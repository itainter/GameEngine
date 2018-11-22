#pragma once

#include <stdint.h>
#include <memory>
#include <algorithm>
#include <unordered_map>
#include <string>

#include "DrawingConstants.h"

namespace Engine
{
    class IDrawingDevice;

    class DrawingResourceDesc
    {
    public:
        DrawingResourceDesc() {}
        DrawingResourceDesc(const DrawingResourceDesc& desc);
        DrawingResourceDesc(const DrawingResourceDesc&& desc);

        DrawingResourceDesc& operator= (const DrawingResourceDesc& rhs);
        virtual ~DrawingResourceDesc();

        virtual EDRType GetType() const = 0;

        typedef std::unordered_map<uint32_t, std::shared_ptr<std::string>> ResourceDescNamesType;

        ResourceDescNamesType GetResourceDescNames() const;
        void AddResourceDescName(uint32_t index, std::shared_ptr<std::string> name);
        std::shared_ptr<std::string> GetResourceDescName(uint32_t index) const;


    private:
        void CloneFromNames(const ResourceDescNamesType& from);

        ResourceDescNamesType mResourceDescNames;
    };

    class DrawingResource
    {
    public:
        DrawingResource(std::shared_ptr<IDrawingDevice> pDevice) {};
        virtual ~DrawingResource() = default;
    };


    class IDrawingDevice
    {
    public:
        IDrawingDevice() = default;
        virtual ~IDrawingDevice() = default;
    };
}