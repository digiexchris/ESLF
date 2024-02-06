#pragma once

#include <etl/message_broker.h>
#include "Logging/Logger.hpp"

namespace State{
namespace MessageBus{

// Custom subscription type.
class Subscription : public etl::message_broker::subscription
{
public:

  Subscription(etl::imessage_router& router, std::initializer_list<etl::message_id_t> id_list_)
    : etl::message_broker::subscription(router)
    , id_list(id_list_)
  {
  }

  etl::message_broker::message_id_span_t message_id_list() const override
  {
    return etl::message_broker::message_id_span_t(id_list.begin(), id_list.end());
  }

  std::vector<etl::message_id_t> id_list;
};

// Custom broker.
class Broker : public etl::message_broker
{
public:

  using etl::message_broker::receive;

  // Hook incoming messages and translate Message4 to Message3.
  void receive(const etl::imessage& msg) override
  {
    ELSF_LOG_INFO("Broker received message: {}", msg.get_message_id());
    etl::message_broker::receive(msg);
  }
};


// // The subscriptions.
// Subscription subscription1{ router1, { Message1::ID, Message2::ID } };
// Subscription subscription2{ router2, { Message2::ID, Message3::ID } };

// // Instance of message broker.
// etl::message_broker broker;

// // Subscribe router1 and router1 to the broker.
// broker.subscribe(subscription1);
// broker.subscribe(subscription2);

// broker.receive(message1); // Received by router1
// broker.receive(message2); // Received by router1 and router2
// broker.receive(message3); // Received by router2
// broker.receive(message4); // Received by router2 as a Message3


} // namespace MessageBus
} // namespace State