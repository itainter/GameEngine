#include "DrawingDevice.h"

using namespace Engine;

DrawingResource::DrawingResource(std::shared_ptr<IDrawingDevice> pDevice) : m_pDevice(pDevice),
    m_pName(nullptr), m_pDesc(nullptr)
{
}