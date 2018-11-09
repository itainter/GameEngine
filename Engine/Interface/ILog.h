#pragma once

namespace Engine
{
    class ILog
    {
    public:
        virtual ~ILog() {};

        virtual void Initialize() = 0;
        virtual void Shutdown() = 0;
    };
}