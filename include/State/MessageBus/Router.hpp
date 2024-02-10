#pragma once

#include <etl/queue.h>
#include <etl/message_packet.h>
#include <etl/message_router.h>
#include "State/MessageBus/Subscription.hpp"

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
    Router();
    ~Router() { delete mySubscription; }
    virtual void receive(const etl::imessage& msg_) = 0;
    virtual std::initializer_list<etl::message_id_t> GetValidMessagesList() const;
    virtual Subscription* GetSubscription() const;
protected:
    Subscription* mySubscription;
};



/**
* QueuedRouter
*/

template <typename TDerived, size_t QueueSize, typename... Messages>
class QueuedRouter : public Router<TDerived, Messages...>
{
public:
    virtual void receive(const etl::imessage& msg_) override;
    virtual void process_queue();

private:
    etl::queue<RouterMessagePacket<Messages...>, QueueSize> myQueue;
};

} // namespace Machine
} // namespace State