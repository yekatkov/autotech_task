#pragma once

#include "XYTransceiver.h"
#include "Protocol.h"

namespace TransportLayer
{
class TransportInterface;
} // namespace TransportLayer

namespace ApplicationLayer
{
class XYReceiver : public XYTransceiver
{
public:
    explicit XYReceiver(uint16_t deviceId);
    ~XYReceiver() = default;

    // Blocking receiving.
    Protocol::Packet receive() const;
};
} // namespace ApplicationLayer
