#include "ThreadSafeLogger.h"

#include <iostream>

namespace Utils
{
ThreadSafeLogger& ThreadSafeLogger::getImpl()
{
    static ThreadSafeLogger impl;
    return impl;
}

void ThreadSafeLogger::writeLog(std::string_view msg) const
{
    std::lock_guard lock(_stdoutGuard);
    std::cout << msg;
}
} // namespace Utils
