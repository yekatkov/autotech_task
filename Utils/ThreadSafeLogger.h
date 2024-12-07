#pragma once

#include "CommonDefs.h"

#include <mutex>
#include <string_view>

namespace Utils
{
class ThreadSafeLogger
{
public:
    static ThreadSafeLogger& getImpl();
    ~ThreadSafeLogger() = default;

    FORBID_COPY_MOVE(ThreadSafeLogger);

    void writeLog(std::string_view msg) const;

private:
    ThreadSafeLogger() = default;
    mutable std::mutex _stdoutGuard;
};
} // Utils
