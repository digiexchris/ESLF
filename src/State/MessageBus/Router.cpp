#include "State/MessageBus/Router.hpp"

#include "Logging/Logger.hpp"

#include <etl/message.h>

namespace State
{
namespace MessageBus
{

  // //***************************************************************************
  // // The overridden virtual receive function.
  //***************************************************************************
template <typename TDerived, typename... Messages>
class Router<TDerived, Messages...>::receive(const etl::imessage& msg_)
  {
    if (accepts(msg_))
    {
      // Place in queue.
      queue.emplace(msg_);
      ELSF_LOG_INFO("Queueing message %d\n", msg_.get_message_id());
    }
    else
    {
      ELSF_LOG_INFO("Message %d not accepted\n", msg_.get_message_id());
    }
  }

  //***************************************************************************
  // The method to call to handle any queued messages.
  //***************************************************************************
  template <typename TDerived, size_t QueueSize, typename... Messages>
  void QueuedRouter<TDerived, QueueSize, Messages...>::process_queue()
  {
    // while (!queue.empty())
    // {
    //   RouterMessagePacket<Messages...>& packet = queue.front();
    //   etl::imessage& msg = packet.get();
    //   ELSF_LOG_INFO("Processing message %d\n", msg.get_message_id());

    //   // Call the base class's receive function.
    //   // This will route it to the correct 'on_event' handler.
    //   etl::fsm::receive(msg);

    //   queue.pop();
    // }
  }


} // namespace MessageBus
} // namespace State