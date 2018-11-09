#include <memory>
#include "BaseApplication.h"

namespace Engine
{
    BaseApplication g_App;
    std::unique_ptr<IApplication> g_pApp = std::make_unique<BaseApplication>(g_App);
}