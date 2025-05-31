#include "Logger.h"
#include <fstream>
#include <cstdarg>

void Log(const char* fmt, ...)
{
    static std::ofstream file("log.txt", std::ios::app);
    if (!file.is_open()) return;

    char buf[512];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);

    file << buf << std::endl;
}
