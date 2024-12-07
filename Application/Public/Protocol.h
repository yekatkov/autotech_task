#pragma once

#include <cstdint>
#include <variant>

#include "XY.h"

namespace ApplicationLayer::Protocol
{
enum class Command : uint8_t
{
    Stop
};

using Packet = std::variant<XY, Command>;
} // namespace ApplicationLayer::Protocol
