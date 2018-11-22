#pragma once

#include "DrawingDevice.h"

using namespace Engine;

DrawingResourceDesc::DrawingResourceDesc(const DrawingResourceDesc& desc)
{
    CloneFromNames(desc.mResourceDescNames);
}

DrawingResourceDesc::DrawingResourceDesc(const DrawingResourceDesc&& desc)
{
    CloneFromNames(desc.mResourceDescNames);
    mResourceDescNames.clear();
}

DrawingResourceDesc& DrawingResourceDesc::operator= (const DrawingResourceDesc& rhs)
{
    if (this == &rhs)
        return *this;

    CloneFromNames(rhs.mResourceDescNames);
    return *this;
}

DrawingResourceDesc::~DrawingResourceDesc()
{
    mResourceDescNames.clear();
}

DrawingResourceDesc::ResourceDescNamesType DrawingResourceDesc::GetResourceDescNames() const
{
    return mResourceDescNames;
}

void DrawingResourceDesc::AddResourceDescName(uint32_t index, std::shared_ptr<std::string> name)
{
    auto it = mResourceDescNames.find(index);
    if (it != mResourceDescNames.cend())
        return;

    mResourceDescNames.emplace(index, name);
}

std::shared_ptr<std::string> DrawingResourceDesc::GetResourceDescName(uint32_t index) const
{
    auto it = mResourceDescNames.find(index);
    if (it == mResourceDescNames.cend())
        return nullptr;
    
    return it->second;
}

void DrawingResourceDesc::CloneFromNames(const ResourceDescNamesType& from)
{
    mResourceDescNames.clear();
    std::for_each(from.cbegin(), from.cend(), [this](const ResourceDescNamesType::value_type& aElem)
    {
        if (auto& lpName = aElem.second)
            mResourceDescNames.emplace(aElem.first, lpName);
    });
}
