#pragma once

#include "etl/message.h"

namespace State
{
namespace MessageBus
{

enum MessageId {
    START = 1,
    START_RUNNING_AT, //queue up a timer to engage the leadscrew (START) at a specific time (time in this case is the encoder position plus the time it takes move beween the indicated position to the estimated position between encoder pulses)
    STOP_RUNNING_AT,
    STOP,
    TRIGGER_ESTOP,
    RESET
};

struct MachineMessageInterface : public etl::imessage
{
  //virtual void DoStuff() = 0;
};

/* Starts the position tracking loop to make the tool
* follow the encoder. */
struct StartMessage : public etl::message<MessageId::START, MachineMessageInterface>
{
};

/** Starts the mode that will wait until the encoder is at
 * a specific position before starting the position tracking
*/
struct StartAtMessage : public etl::message<MessageId::START_RUNNING_AT, MachineMessageInterface>
{
    StartAtMessage(double time) : time(time) {}
    double time;
};

struct StopAtMessage : public etl::message<MessageId::STOP_RUNNING_AT, MachineMessageInterface>
{
    StopAtMessage(double time) : time(time) {}
    double time;
};

struct StopMessage : public etl::message<MessageId::STOP, MachineMessageInterface>
{
};

struct EStopMessage : public etl::message<MessageId::TRIGGER_ESTOP, MachineMessageInterface>
{
};

struct ResetMessage : public etl::message<MessageId::RESET, MachineMessageInterface>
{
};

} // namespace Machine
} // namespace State