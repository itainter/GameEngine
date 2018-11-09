#include <memory>
#include <stdexcept>
#include <iostream>
#include "IApplication.h"

using namespace Engine;

namespace Engine
{
    extern std::unique_ptr<IApplication> g_pApp;
}

int main(int argc, char** argv)
{
    try
    {
        g_pApp->Initialize();
    }
    catch (const std::runtime_error& e)
    {
        std::cout << e.what() << std::endl;
        return -1;
    }

    while (!g_pApp->IsQuit()) {
        try
        {
            g_pApp->Tick();
        }
        catch (const std::runtime_error& e)
        {
            std::cout << e.what() << std::endl;
            return -1;
        }
    }

    g_pApp->Shutdown();

    return 0;
}