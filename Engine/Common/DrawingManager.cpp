#pragma once

#include "DrawingManager.h"

using namespace Engine;

DrawingManager::DrawingManager() : m_deviceType(eDevice_D3D11), m_pDevice(nullptr), m_pContext(nullptr)
{
}

DrawingManager::~DrawingManager()
{
}

void DrawingManager::Initialize()
{
}

void DrawingManager::Shutdown()
{
}

void DrawingManager::Tick()
{
}

void DrawingManager::Flush()
{
}

void DrawingManager::BeginFrame()
{
}

void DrawingManager::EndFrame()
{
}

EDeviceType DrawingManager::GetDeviceType() const
{
    return m_deviceType;
}

void DrawingManager::SetDeviceType(EDeviceType type)
{
    m_deviceType = type;
}

