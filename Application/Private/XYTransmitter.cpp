#include "../Public/XYTransmitter.h"
#include "TransportLayer/Public/TransportInterface.h"

namespace ApplicationLayer
{
XYTransmitter::XYTransmitter(uint16_t deviceId) : XYTransceiver(deviceId)
{
}

void XYTransmitter::send(const XY& value) const
{
    sendImpl(value);
}

void XYTransmitter::send(Protocol::Command command) const
{
    sendImpl(command);
}

void XYTransmitter::sendImpl(Protocol::Packet packet) const
{
    getTransportInterface().write(reinterpret_cast<const uint8_t*>(&packet), sizeof(packet));
}
} // namespace ApplicationLayer
