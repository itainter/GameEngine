#pragma once

#include "ISceneManager.h"

namespace Engine
{
    class SceneManager : public ISceneManager
    {
    public:
        SceneManager() {}
        virtual ~SceneManager() {}

        void Initialize() override;
        void Shutdown() override;
        void Tick() override;
    };
}