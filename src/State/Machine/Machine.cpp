
#include "etl/queue.h"
#include "etl/hfsm.h"
#include "etl/message_packet.h"

#include "State/Machine/Machine.hpp"
#include "Logging/Logger.hpp"

  Machine::Machine()
    : hfsm(MACHINE_ROUTER_ID)
  {
  }

  // //***************************************************************************
  // // The overridden virtual receive function.
  // //***************************************************************************
  // void Machine::receive(const etl::imessage& msg_)
  // {
  //   if (accepts(msg_))
  //   {
  //     // Place in queue.
  //     queue.emplace(msg_);
  //     ELSF_LOG_INFO("Queueing message %d\n", msg_.get_message_id());
  //   }
  //   else
  //   {
  //     ELSF_LOG_INFO("Message %d not accepted\n", msg_.get_message_id());
  //   }
  // }

  // //***************************************************************************
  // // The method to call to handle any queued messages.
  // //***************************************************************************
  // void Machine::process_queue()
  // {
  //   while (!queue.empty())
  //   {
  //     message_packet& packet = queue.front();
  //     etl::imessage& msg = packet.get();
  //     ELSF_LOG_INFO("Processing message %d\n", msg.get_message_id());

  //     // Call the base class's receive function.
  //     // This will route it to the correct 'on_event' handler.
  //     etl::fsm::receive(msg);

  //     queue.pop();
  //   }
  // }