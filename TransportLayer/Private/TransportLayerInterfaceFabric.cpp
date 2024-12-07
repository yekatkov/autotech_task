#include <cstdint>
#include <memory>

#include "../Public/TransportInterface.h"
#include "../Public/TransportInterfaceFabric.h"
#include "../Private/Can/CanInterface.h"

namespace TransportLayer
{
std::shared_ptr<TransportInterface> TransportInterfaceFabric::createCanInterface(uint16_t canFrameID)
{
    return std::make_shared<CanInterface>(canFrameID);
}
} // namespace TransportLayer
