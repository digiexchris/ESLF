#include "State/MessageBus/Router.hpp"

#include "Logging/Logger.hpp"

#include <etl/message.h>

namespace State
{
namespace MessageBus
{

/**
* Router
*/

template <typename TDerived, typename... Messages>
Router<TDerived, Messages...>::Router()
{
  mySubscription = new Subscription(this, GetValidMessagesList());
}

template <typename TDerived, typename... Messages>
Subscription* Router<TDerived, Messages...>::GetSubscription() const
{
  return mySubscription;
}

template <typename TDerived, typename... Messages>
std::initializer_list<etl::message_id_t> Router<TDerived, Messages...>::GetValidMessagesList() const
{
  return {Messages::ID...};
}


/** 
* QueuedRouter
*/
template <typename TDerived, size_t QueueSize, typename... Messages>
void QueuedRouter<TDerived, QueueSize, Messages...>::process_queue()
{
  while (!myQueue.empty())
  {
    RouterMessagePacket<Messages...>& packet = myQueue.front();
    etl::imessage& msg = packet.get();
    ELSF_LOG_INFO("Processing message %d\n", msg.get_message_id());

    // Call the base class's receive function.
    // This will route it to the correct 'on_event' handler.
    Router<TDerived, Messages...>::receive(msg);

    myQueue.pop();
  }
}

//queue it up so it can be received off of the queue in order instead
//for example, letting continuous moves complete before starting to decellerate
//TODO consider adding a message base class type to allow sending messages
//that should skip the queue and be sent to receive immediately, such as STOP and ESTOP
template <typename TDerived, size_t QueueSize, typename... Messages>
void QueuedRouter<TDerived, QueueSize, Messages...>::receive(const etl::imessage& msg_)
{
  myQueue.emplace(msg_);
  ELSF_LOG_INFO("Received message %d\n", msg_.get_message_id());
}


} // namespace MessageBus
} // namespace State