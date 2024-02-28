#pragma once

#include <etl/message.h>
#include <etl/queue.h>
#include <etl/message_packet.h>
#include <etl/message_router.h>
#include "Subscription.hpp"
#include "Logging/Logger.hpp"

namespace Machine::MessageBus
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
    const std::vector<etl::message_id_t>& GetValidMessagesList() const
    {
        return myValidMessagesList;
    }
private:
    std::vector<etl::message_id_t> myValidMessagesList{Messages::ID...};
};



/**
* QueuedRouter
*/

template <typename TDerived, size_t QueueSize, typename... Messages>
class QueuedRouter : public Router<TDerived, Messages...>
{
public:
    void receive(const etl::imessage& msg_) override
    {
        try
        {
            myQueue.emplace(msg_);
        }
        catch (const etl::queue_full&)
        {
            ELSF_LOG_ERROR("Queue full, message %d dropped\n", msg_.get_message_id());
            return;
        }
        catch (const etl::unhandled_message_exception&)
        {
            ELSF_LOG_ERROR("Unexpected message for this router, message %d dropped\n", msg_.get_message_id());
            return;
        }
        catch (...)
        {
            ELSF_LOG_ERROR("Unknown error, message %d dropped\n", msg_.get_message_id());
            return;
        }

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

} // namespace Machine::MessageBus