#pragma once

#include "IDrawingManager.h"

namespace Engine
{
    class DrawingManager : public IDrawingManager
    {
    public:
        DrawingManager() {}
        virtual ~DrawingManager() {}

        void Initialize() override;
        void Shutdown() override;

        void Tick() override;

        void Flush() override;
        void BeginFrame() override;
        void EndFrame() override;
    };
}