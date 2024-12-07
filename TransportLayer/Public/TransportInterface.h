#pragma once

#include <cstddef>
#include <cstdint>

namespace TransportLayer
{
class TransportInterface
{
public:
    virtual ~TransportInterface() = default;

    virtual size_t read(uint8_t* buffer, size_t bufferSize) const = 0;
    virtual void write(const uint8_t* buffer, size_t bufferSize) const = 0;
};
} // namespace TransportLayer
