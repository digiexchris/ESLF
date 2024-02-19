#include "State/MessageBus/Messages.hpp"

namespace State
{
namespace MessageBus
{
    StartAtMessage::StartAtMessage(uint32_t aPosition) :position(aPosition) {}
    StopAtMessage::StopAtMessage(uint32_t aPosition) :position(aPosition) {}
} // namespace MessageBus
} // namespace State