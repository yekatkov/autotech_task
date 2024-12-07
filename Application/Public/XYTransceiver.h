#pragma once

#include <memory>

namespace TransportLayer
{
class TransportInterface;
} // namespace TransportLayer

namespace ApplicationLayer
{
class XYTransceiver
{
public:
    uint16_t getDeviceId() const;

protected:
    explicit XYTransceiver(uint16_t deviceId);
    ~XYTransceiver() = default;
    TransportLayer::TransportInterface& getTransportInterface() const;

private:
    const uint16_t _deviceId;
    std::shared_ptr<TransportLayer::TransportInterface> _transportInterface;
};
} // namespace ApplicationLayer
