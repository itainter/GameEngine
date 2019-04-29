#include "WindowsApplication.h"
#include "EventManager.h"
#include "DrawingManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "SystemLog.h"

#include "TransformComponent.h"
#include "MeshFilterComponent.h"
#include "MeshRendererComponent.h"

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

        gpGlobal->RegisterApp<WindowsApplication>();

        gpGlobal->RegisterRuntimeModule<InputManager>(eSystem_InputManager);
        gpGlobal->RegisterRuntimeModule<EventManager>(eSystem_EventManager);
        gpGlobal->RegisterRuntimeModule<SceneManager>(eSystem_SceneManager);
        gpGlobal->RegisterRuntimeModule<DrawingManager>(eSystem_DrawingManager);
        gpGlobal->RegisterRuntimeModule<SystemLog>(eSystem_Log_System);

        gpGlobal->RegisterRenderer<BasicPrimitiveRenderer>(eRenderer_BasicPrim);

        auto& pWorld = gpGlobal->GetECSWorld();

        // ECSSystem
        pWorld->AddECSSystem(gpGlobal->GetInputManager());
        pWorld->AddECSSystem(gpGlobal->GetEventManager());
        pWorld->AddECSSystem(gpGlobal->GetDrawingManager());
        pWorld->AddECSSystem(gpGlobal->GetLogSystem());

        // Entity
        TransformComponent posComp;
        MeshFilterComponent meshFilterComp;
        MeshRendererComponent meshRendererComp;

        posComp.SetPosition(Vec3<float>(1.0f, 1.0f, 1.0f));

        auto pMesh = std::make_shared<CubeMesh>();
        //auto pMesh = std::make_shared<GLTF2Mesh>("Asset/Scene/Test/DamagedHelmet.gltf")

        meshFilterComp.SetMesh(pMesh);
        meshRendererComp.SetRenderer(gpGlobal->GetRenderer(eRenderer_BasicPrim));

        gpGlobal->GetRenderer(eRenderer_BasicPrim)->AttachMesh(pMesh);

        auto entity = pWorld->CreateEntity<TransformComponent, MeshFilterComponent, MeshRendererComponent>(posComp, meshFilterComp, meshRendererComp);
    }
};

static GameSetup setup;