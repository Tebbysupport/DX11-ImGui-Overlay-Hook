#include "Hook.h"
#include "DX11Hook.h"

namespace Hook
{
    void Initialize()
    {
        DX11Hook::Init();
    }

    void Shutdown()
    {
        DX11Hook::Shutdown();
    }
}
