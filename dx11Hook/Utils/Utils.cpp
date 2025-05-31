#include "Utils.h"
#include <Windows.h>

bool IsKeyPressed(int vKey)
{
    return (GetAsyncKeyState(vKey) & 0x1);
}
