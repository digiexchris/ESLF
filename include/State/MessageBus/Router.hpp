#pragma once

#include <etl/queue.h>
#include <etl/message_packet.h>
#include <etl/message_router.h>

namespace State
{
namespace MessageBus
{

template <typename... Messages>
using RouterMessagePacket = etl::message_packet<Messages...>;

template <typename TDerived, typename... Messages>
class Router : public etl::message_router<TDerived, Messages...>
{
public:
    virtual void receive(const etl::imessage& msg_) = 0;

protected:
    
};



template <typename TDerived, size_t QueueSize, typename... Messages>
class QueuedRouter : public Router<TDerived, Messages...>
{
public:
    virtual void receive(const etl::imessage& msg_) override;
    //optional method to process the queue
    //some routers are simple enough to not need a queue so this is optional
    virtual void process_queue();

private:
    etl::queue<RouterMessagePacket<Messages...>, QueueSize> queue;
};

} // namespace Machine
} // namespace State