#include "Messages.hpp"

namespace Machine::MessageBus
{
    StartAtMessage::StartAtMessage(uint32_t aPosition) :position(aPosition) {}
    StopAtMessage::StopAtMessage(uint32_t aPosition) :position(aPosition) {}
} // namespace Machine::MessageBus