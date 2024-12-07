#pragma once

#include <cstdint>
#include <memory>

namespace TransportLayer
{
class TransportInterface;

class TransportInterfaceFabric
{
public:
    static std::shared_ptr<TransportInterface> createCanInterface(uint16_t canFrameID);
};
} // namespace TransportLayer
