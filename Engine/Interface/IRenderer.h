#pragma once

#include "IRuntimeModule.h"
#include "Macros.h"
#include "DrawingResourceTable.h"

namespace Engine
{
    class IRenderer : public IRuntimeModule
    {
    public:
        virtual ~IRenderer() {};

        virtual void Initialize() override = 0;
        virtual void Shutdown() override = 0;

        virtual void Tick() override = 0;

        virtual void DefineResources(DrawingResourceTable& resTable) = 0;
        virtual void SetupStages() = 0;
        virtual void SetupBuffers(DrawingResourceTable& resTable) = 0;
        virtual void Cleanup() = 0;

        virtual void BeginFrame() = 0;
        virtual void EndFrame() = 0;

        virtual void UpdatePrimitive(DrawingResourceTable& resTable) = 0;
        virtual void Draw(DrawingResourceTable& resTable) = 0;
    };

#define FuncResourceName(name)                              \
    static inline std::shared_ptr<std::string> name()       \
    {                                                       \
        static auto str = strPtr(#name);                    \
        return str;                                         \
    }

}