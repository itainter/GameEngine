#pragma once

#include <memory>
#include <unordered_map>

#include "IDrawingManager.h"

#include "Global.h"
#include "ECSSystem.h"

#include "DrawingDevice.h"
#include "DrawingEffectPool.h"
#include "DrawingResourceTable.h"
#include "DrawingType.h"
#include "BasicPrimitiveRenderer.h"

namespace Engine
{
    class TransformComponent;
    class MeshFilterComponent;
    class MeshRendererComponent;
    class DrawingManager : public IDrawingManager, public ECSSystemBase<TransformComponent, MeshFilterComponent, MeshRendererComponent>
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
        bool EstablishConfiguration();
        bool PreConfiguration();
        bool CreateDevice();
        bool CreatePreResource();
        bool RegisterRenderer();
        bool PostConfiguration();

        std::shared_ptr<DrawingTarget> CreateSwapChain();
        std::shared_ptr<DrawingDepthBuffer> CreateDepthBuffer();

    private:
        void* m_window;
        uint2 m_deviceSize;
        EDeviceType m_deviceType;

        std::shared_ptr<DrawingDevice> m_pDevice;
        std::shared_ptr<DrawingContext> m_pContext;

        std::shared_ptr<DrawingEffectPool> m_pEffectPool;
        std::shared_ptr<DrawingResourceFactory> m_pResourceFactory;
        std::shared_ptr<DrawingResourceTable> m_pResourceTable;

        typedef std::unordered_map<ERendererType, std::shared_ptr<IRenderer>> RendererTable;
        RendererTable m_rendererTable;
    };
}