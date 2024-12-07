#pragma once

#include "../../Public/TransportInterface.h"

namespace TransportLayer
{
class CanInterface final : public TransportInterface
{
public:
    explicit CanInterface(uint16_t canFrameId);
    ~CanInterface() override = default;

    size_t read(uint8_t* buffer, size_t bufferSize) const override;
    void write(const uint8_t* buffer, size_t bufferSize) const override;

private:
    const uint16_t _canFrameId{0};
};
} // namespace TransportLayer
