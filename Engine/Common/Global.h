#pragma once

#include <iostream>
#include <memory>
#include <unordered_map>
#include <stdint.h>

#include "Vec4.h"
#include "FPS.h"
#include "IRuntimeModule.h"

namespace Engine
{
    enum ERTModule
    {
        eRTModule_App = 1,
        eRTModule_Entity_Pool = 2,
        eRTModule_EventManager = 3,
        eRTModule_DrawingManager = 4,
        eRTModule_SceneManager = 5,
        eRTModule_InputManager = 6,
        eRTModule_Log_System = 7,
        eRTModule_Log_Input = 8,

        eRTModule_Renderer_Begin = 101,
        eRTModule_Renderer_BasicPrim = 101,
        eRTModule_Renderer_End = 102,
    };

    enum EDeviceType
    {
        eDevice_D3D11 = 0,
        eDevice_D3D12 = 1,
        eDevice_OGL = 2,
    };

    inline std::ostream& operator<< (std::ostream &out, EDeviceType const& d)
    {
        if (d == eDevice_D3D11)
            return out << "D3D11";
        else if (d == eDevice_D3D12)
            return out << "D3D12";
        else if (d == eDevice_OGL)
            return out << "OGL";
        else
            return out << "Unknown";
    }

    struct Configuration
    {
        Configuration(uint32_t _width = 1024,
                      uint32_t _height = 768,
                      EDeviceType _type = eDevice_D3D11,
                      const char* _appName="Game Engine") :
                      width(_width),
                      height(_height),
                      type(_type),
                      background(33.f / 255.f, 40.f / 255.f, 48.f / 255.f, 1.0f),
                      appName(_appName),
                      hWnd(nullptr)
        {}

        uint32_t width;
        uint32_t height;
        EDeviceType type;
        Vec4<float> background;
        const char* appName;
        void* hWnd;

        friend std::ostream& operator<< (std::ostream &out, Configuration const& c)
        {
            return out << "Configuration: " << std::endl <<
                          "app name: " << c.appName << std::endl <<
                          "width: " << c.width << std::endl <<
                          "height: " << c.height << std::endl <<
                          "device type: " << c.type << std::endl;
        }
    };

    class IApplication;
    class IEventManager;
    class IDrawingManager;
    class ISceneManager;
    class IInputManager;
    class ILog;
    class IEntityPool;
    class IRenderer;

    class Global
    {
    public:
        Global() {}
        virtual ~Global();

        std::shared_ptr<IApplication> GetApplication();
        std::shared_ptr<IEntityPool> GetEntityPool();
        std::shared_ptr<IEventManager> GetEventManager();
        std::shared_ptr<IDrawingManager> GetDrawingManager();
        std::shared_ptr<ISceneManager> GetSceneManager();
        std::shared_ptr<IInputManager> GetInputManager();
        std::shared_ptr<ILog> GetLogSystem();
        std::shared_ptr<ILog> GetLogInput();
        // Renderer
        std::shared_ptr<IRenderer> GetRenderer(ERTModule module);

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
        template<typename T>
        std::shared_ptr<T> GetRuntimeModule(ERTModule e)
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
        std::unordered_map<ERTModule, std::shared_ptr<IRuntimeModule>> m_RTModuleMap;
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