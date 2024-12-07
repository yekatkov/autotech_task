#pragma once

#include <condition_variable>
#include <cstdint>
#include <deque>

#include "Utils/CommonDefs.h"

namespace PhysicalLayer
{
class PhysicalLayerEmulator
{
public:
    static PhysicalLayerEmulator& getImpl();
    ~PhysicalLayerEmulator() = default;

    FORBID_COPY_MOVE(PhysicalLayerEmulator);

    // Blocking calls
    size_t read(uint8_t* buffer, size_t bytesCountForRead);
    void write(const uint8_t* buffer, size_t bytesCountForWrite);

    // Class helps to lock channel in case of performing sequence transaction in parallel
    class InterfaceLocker
    {
    public:
        virtual ~InterfaceLocker() = default;
    };

    std::shared_ptr<InterfaceLocker> getInterfaceWriteLocker();
    std::shared_ptr<InterfaceLocker> getInterfaceReadLocker();

private:
    PhysicalLayerEmulator() = default;

    // Set small size of buffer for imitation of chennel overload.
    static constexpr auto BufferSize = 5;

    // Mutex and conditional variable for thread safe access to _queue
    std::mutex _readyForReadLock;
    std::condition_variable _readyForReadCondVar;
    std::deque<uint8_t> _queue;

    // Mutexes are used in InterfaceLocker.
    std::mutex _lockInterfaceForReading;
    std::mutex _lockInterfaceForWriting;
};
} // namespace PhysicalLayer
