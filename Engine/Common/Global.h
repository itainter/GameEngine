#pragma once

#include <iostream>
#include <memory>
#include <map>
#include <stdint.h>

#include "Vec4.h"
#include "FPS.h"
#include "IRuntimeModule.h"

namespace Engine
{
    struct Configuration
    {
        Configuration(uint32_t _width = 1024, uint32_t _height = 768, const char* _appName="Game Engine") :
                      width(_width),
                      height(_height),
                      background(33.f / 255.f, 40.f / 255.f, 48.f / 255.f, 1.0f),
                      appName(_appName),
                      hWnd(nullptr)
        {}

        uint32_t width;
        uint32_t height;
        Vec4<float> background;
        const char* appName;
        void* hWnd;

        friend std::ostream& operator<< (std::ostream &out, Configuration const& c)
        {
            return out << "Configuration: " <<
                          "app name: " << c.appName <<
                          "width: " << c.width <<
                          "height: " << c.height <<
                          std::endl;
        }
    };

    enum ERTModule
    {
        eRTModule_App = 1,
        eRTModule_EventManager = 2,
        eRTModule_DrawingManager = 3,
        eRTModule_InputManager = 4,
        eRTModule_Log_System = 5,
        eRTModule_Log_Input = 6,
    };

    class IApplication;
    class IEventManager;
    class IDrawingManager;
    class IInputManager;
    class ILog;

    class Global
    {
    public:
        Global() {}
        virtual ~Global();

        std::shared_ptr<IApplication> GetApplication();
        std::shared_ptr<IEventManager> GetEventManager();
        std::shared_ptr<IDrawingManager> GetDrawingManager();
        std::shared_ptr<IInputManager> GetInputManager();
        std::shared_ptr<ILog> GetLogSystem();
        std::shared_ptr<ILog> GetLogInput();

        Configuration& GetConfiguration();
        FPSCounter& GetFPSCounter();

        template<typename T>
        void RegisterRuntimeModule(ERTModule e)
        {
            auto it = m_RTModuleMap.find(e);
            if (it != m_RTModuleMap.end())
                return;
            auto module = std::make_shared<T>();
            std::shared_ptr<IRuntimeModule> result = std::dynamic_pointer_cast<IRuntimeModule>(module);

            m_RTModuleMap[e] = result;
        }

    private:
        template<typename T, ERTModule e>
        std::shared_ptr<T> GetRuntimeModule()
        {
            auto it = m_RTModuleMap.find(e);
            if (it == m_RTModuleMap.end())
                return nullptr;
            else
            {
                auto& module = it->second;
                std::shared_ptr<T> result = std::dynamic_pointer_cast<T>(module);
                return result;
            }
        }

    private:
        std::map<ERTModule, std::shared_ptr<IRuntimeModule>> m_RTModuleMap;
        Configuration m_config;
        FPSCounter m_fps;
    };

    class Setup
    {
    public:
        Setup();
        virtual ~Setup() {};
    };

    extern Global* gpGlobal;
}