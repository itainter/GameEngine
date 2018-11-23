#pragma once

#include <memory>
#include <string>

#include "IDrawingDevice.h"
#include "DrawingResourceDesc.h"

namespace Engine
{
    class DrawingResource
    {
    public:
        DrawingResource(std::shared_ptr<IDrawingDevice> pDevice);
        virtual ~DrawingResource() = default;

        virtual std::shared_ptr<std::string> Name();
        virtual void SetName(std::shared_ptr<std::string> name);

        std::shared_ptr<IDrawingDevice*> GetDevice(); 
    protected:
        std::shared_ptr<IDrawingDevice> m_pDevice;
        std::shared_ptr<std::string> m_pName;
        std::shared_ptr<DrawingResourceDesc> m_pDesc;
    };

    class DrawingDevice : public IDrawingDevice
    {
    public:
        DrawingDevice() = default;
        virtual ~DrawingDevice() = default;
    };
}