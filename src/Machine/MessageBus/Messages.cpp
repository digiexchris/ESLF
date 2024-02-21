#include "Machine/MessageBus/Messages.hpp"

namespace Machine
{
namespace MessageBus
{
    StartAtMessage::StartAtMessage(uint32_t aPosition) :position(aPosition) {}
    StopAtMessage::StopAtMessage(uint32_t aPosition) :position(aPosition) {}
} // namespace MessageBus
} // namespace State