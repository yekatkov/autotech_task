#include "../Public/PhysicalLayerEmulator.h"

#include <algorithm>

namespace PhysicalLayer
{
namespace
{
class InterfaceLockerImpl final : public PhysicalLayerEmulator::InterfaceLocker
{
public:
    explicit InterfaceLockerImpl(std::mutex& interfaceLock) : _interfaceLock(interfaceLock)
    {
        _interfaceLock.lock();
    }

    ~InterfaceLockerImpl() override
    {
        _interfaceLock.unlock();
    }

private:
    std::mutex& _interfaceLock;
};
}

size_t PhysicalLayerEmulator::read(uint8_t* buffer, size_t bytesCountForRead)
{
    // Always returns requested bytes count because we don't handle errors in channel in scope of this task
    const auto totalBytesCountForRead = bytesCountForRead;

    auto fetchAvailableData = [&buffer, &bytesCountForRead, this]()
    {
        if (auto currentBytesCountForRead = std::min(bytesCountForRead, _queue.size()))
        {
            // Get available bytes for read and remove them from queue
            auto srcIt = _queue.begin();
            std::copy_n(srcIt, currentBytesCountForRead, buffer);
            _queue.erase(srcIt, srcIt + static_cast<long>(currentBytesCountForRead));

            bytesCountForRead -= currentBytesCountForRead;
            buffer += currentBytesCountForRead;
        }
    };

    {
        // Get data which are already in queue
        std::unique_lock lock(_readyForReadLock);
        fetchAvailableData();
    }

    while (bytesCountForRead != 0)
    {
        std::unique_lock lock(_readyForReadLock);
        _readyForReadCondVar.wait(lock, [this]()
        {
            return !_queue.empty();
        });
        fetchAvailableData();
    }

    return totalBytesCountForRead;
}

void PhysicalLayerEmulator::write(const uint8_t* buffer, size_t bytesCountForWrite)
{
    {
        std::lock_guard lock(_readyForReadLock);
        std::copy_n(buffer, bytesCountForWrite, std::back_inserter(_queue));
    }
    _readyForReadCondVar.notify_all();
}

std::shared_ptr<PhysicalLayerEmulator::InterfaceLocker> PhysicalLayerEmulator::getInterfaceWriteLocker()
{
    return std::make_shared<InterfaceLockerImpl>(_lockInterfaceForWriting);
}

std::shared_ptr<PhysicalLayerEmulator::InterfaceLocker> PhysicalLayerEmulator::getInterfaceReadLocker()
{
    return std::make_shared<InterfaceLockerImpl>(_lockInterfaceForReading);
}

PhysicalLayerEmulator& PhysicalLayerEmulator::getImpl()
{
    static PhysicalLayerEmulator impl;
    return impl;
}
} // namespace PhysicalLayer
