#pragma once

#include <memory>

#include "IDrawingManager.h"
#include "DrawingDevice.h"

namespace Engine
{
    class DrawingManager : public IDrawingManager
    {
    public:
        DrawingManager();
        virtual ~DrawingManager();

        void Initialize() override;
        void Shutdown() override;

        void Tick() override;



        void Flush() override;
        void BeginFrame() override;
        void EndFrame() override;

        EDeviceType GetDeviceType() const override;
        void SetDeviceType(EDeviceType type) override;

    private:
        EDeviceType m_deviceType;
        std::shared_ptr<DrawingDevice> m_pDevice;
        std::shared_ptr<DrawingContext> m_pContext;
    };
}