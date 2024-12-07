#include "../Public/XYTransceiver.h"
#include "TransportLayer/Public/TransportInterfaceFabric.h"

namespace ApplicationLayer
{
XYTransceiver::XYTransceiver(uint16_t deviceId)
    : _deviceId(deviceId)
    , _transportInterface(TransportLayer::TransportInterfaceFabric::createCanInterface(deviceId))
{
}

uint16_t XYTransceiver::getDeviceId() const
{
    return _deviceId;
}

TransportLayer::TransportInterface& XYTransceiver::getTransportInterface() const
{
    return *_transportInterface;
}
} // namespace ApplicationLayer
