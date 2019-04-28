#include "WindowsApplication.h"
#include "EventManager.h"
#include "DrawingManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "SystemLog.h"
#include "InputLog.h"
#include "EntityPool.h"

#include "TransformComponent.h"
#include "MeshFilterComponent.h"
#include "MeshRendererComponent.h"

#include "RenderableSystem.h"

#include "CubeMesh.h"
#include "GLTF2Mesh.h"

#include "BasicPrimitiveRenderer.h"

using namespace Engine;
using namespace Platform;
    
class GameSetup : public Setup
{
public:
    GameSetup()
    {
        gpGlobal->GetConfiguration().appName = "Game Test";
        gpGlobal->GetConfiguration().width = 1080;
        gpGlobal->GetConfiguration().height = 1080;
        gpGlobal->GetConfiguration().type = eDevice_D3D12;

        gpGlobal->RegisterRuntimeModule<WindowsApplication>(eRTModule_App);
        gpGlobal->RegisterRuntimeModule<EntityPool>(eRTModule_Entity_Pool);

        gpGlobal->RegisterRuntimeModule<EventManager>(eRTModule_EventManager);
        gpGlobal->RegisterRuntimeModule<DrawingManager>(eRTModule_DrawingManager);
        gpGlobal->RegisterRuntimeModule<SceneManager>(eRTModule_SceneManager);
        gpGlobal->RegisterRuntimeModule<InputManager>(eRTModule_InputManager);
        gpGlobal->RegisterRuntimeModule<SystemLog>(eRTModule_Log_System);
        gpGlobal->RegisterRuntimeModule<InputLog>(eRTModule_Log_Input);

        gpGlobal->RegisterRuntimeModule<BasicPrimitiveRenderer>(eRTModule_Renderer_BasicPrim);

        auto& entityPool = gpGlobal->GetEntityPool();

        // ECSSystem
        entityPool->AddECSSystem(std::make_shared<RenderableSystem>());

        // Entity
        TransformComponent posComp;
        MeshFilterComponent meshFilterComp;
        MeshRendererComponent meshRendererComp;

        posComp.SetPosition(Vec3<float>(1.0f, 1.0f, 1.0f));
        //meshFilterComp.SetMesh(std::make_shared<CubeMesh>());
        meshFilterComp.SetMesh(std::make_shared<GLTF2Mesh>("Asset/Scene/Test/DamagedHelmet.gltf"));

        meshRendererComp.SetRenderer(gpGlobal->GetRenderer(eRTModule_Renderer_BasicPrim));

        auto entity = entityPool->CreateEntity<TransformComponent, MeshFilterComponent, MeshRendererComponent>(posComp, meshFilterComp, meshRendererComp);
    }
};

static GameSetup setup;