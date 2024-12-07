#include "../Public/XYReceiver.h"
#include "TransportLayer/Public/TransportInterface.h"

namespace ApplicationLayer
{
XYReceiver::XYReceiver(uint16_t deviceId) : XYTransceiver(deviceId)
{
}

Protocol::Packet XYReceiver::receive() const
{
    Protocol::Packet packet;
    getTransportInterface().read(reinterpret_cast<uint8_t*>(&packet), sizeof(packet));
    return packet;
}
} // namespace ApplicationLayer