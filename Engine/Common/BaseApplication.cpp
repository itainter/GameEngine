#include <stdexcept>
#include <string>
#include <sstream>

#include "Global.h"
#include "IECSWorld.h"

#include "ECSWorld.h"

#include "BaseApplication.h"

using namespace Engine;

bool BaseApplication::m_bQuit = false;

void BaseApplication::Initialize()
{
    m_pWorld = gpGlobal->GetECSWorld();

    if (m_pWorld)
        m_pWorld->Initialize();
}

void BaseApplication::Shutdown()
{
    if (m_pWorld)
        m_pWorld->Shutdown();
}

void BaseApplication::Tick(float elapsedTime)
{
    if (m_pWorld)
        m_pWorld->Tick(elapsedTime);
}

bool BaseApplication::IsQuit() const
{
    return m_bQuit;
}