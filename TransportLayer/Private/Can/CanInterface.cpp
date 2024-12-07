#include "CanInterface.h"
#include "PhysicalLayerEmulator/Public/PhysicalLayerEmulator.h"

namespace TransportLayer
{
CanInterface::CanInterface(uint16_t canFrameId) : _canFrameId(canFrameId)
{
}

size_t CanInterface::read(uint8_t* buffer, size_t bufferSize) const
{
    auto& physicalLayerEmulator = PhysicalLayer::PhysicalLayerEmulator::getImpl();
    auto lock = physicalLayerEmulator.getInterfaceReadLocker();

    while (true)
    {
        std::remove_const_t<decltype(_canFrameId)> canFrameId{0};
        size_t readSize{0};

        physicalLayerEmulator.read(reinterpret_cast<uint8_t*>(&canFrameId), sizeof(canFrameId));
        physicalLayerEmulator.read(reinterpret_cast<uint8_t*>(&readSize), sizeof(readSize));
        if (readSize > bufferSize || _canFrameId != canFrameId)
        {
            // Do somesing (flush readSize bytes in physicalLayerEmulator buffer for example)
        }
        physicalLayerEmulator.read(buffer, readSize);

        if (_canFrameId == canFrameId)
        {
            return readSize;
        }
    }
}

void CanInterface::write(const uint8_t* buffer, size_t bufferSize) const
{
    auto& physicalLayerEmulator = PhysicalLayer::PhysicalLayerEmulator::getImpl();
    auto lock = physicalLayerEmulator.getInterfaceWriteLocker();

    physicalLayerEmulator.write(reinterpret_cast<const uint8_t*>(&_canFrameId), sizeof(_canFrameId));
    physicalLayerEmulator.write(reinterpret_cast<const uint8_t*>(&bufferSize), sizeof(bufferSize));
    physicalLayerEmulator.write(buffer, bufferSize);
}
} // namespace TransportLayer
