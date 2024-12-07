#pragma once

#include "XYTransceiver.h"
#include "Protocol.h"
#include "XY.h"

namespace TransportLayer
{
class TransportInterface;
} // namespace TransportLayer

namespace ApplicationLayer
{
class XYTransmitter : public XYTransceiver
{
public:
    explicit XYTransmitter(uint16_t deviceId);
    ~XYTransmitter() = default;

    void send(const XY& value) const;
    void send(Protocol::Command command) const;

private:
    void sendImpl(Protocol::Packet packet) const;
};
} // namespace ApplicationLayer
