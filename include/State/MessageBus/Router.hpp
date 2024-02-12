#pragma once

#include <etl/queue.h>
#include <etl/message_packet.h>
#include <etl/message_router.h>
#include "State/MessageBus/Subscription.hpp"
#include "Logging/Logger.hpp"

namespace State
{
namespace MessageBus
{

template <typename... Messages>
using RouterMessagePacket = etl::message_packet<Messages...>;



/**
* Router
*/

template <typename TDerived, typename... Messages>
class Router : public etl::message_router<TDerived, Messages...>
{
public:
    Router()
    {
        myValidMessagesList = {Messages::ID...};
    }

    virtual std::initializer_list<etl::message_id_t> GetValidMessagesList() const
    {
        return myValidMessagesList;
    }
protected:
    std::initializer_list<etl::message_id_t> myValidMessagesList;
};



/**
* QueuedRouter
*/

template <typename TDerived, size_t QueueSize, typename... Messages>
class QueuedRouter : public Router<TDerived, Messages...>
{
public:
    virtual void receive(const etl::imessage& msg_) override
    {
        myQueue.emplace(msg_);
        ELSF_LOG_INFO("Received message %d\n", msg_.get_message_id());
    }

    virtual void ProcessQueue()
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

private:
    etl::queue<RouterMessagePacket<Messages...>, QueueSize> myQueue;
};

} // namespace Machine
} // namespace State