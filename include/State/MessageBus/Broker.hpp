#pragma once
#include <etl/message_broker.h>
#include "Logging/Logger.hpp"
//TODO eventually this will route messages to all subscribed routers
//eg. stop message goes to UI and Machine routers.

// Custom broker.
class Broker : public etl::message_broker
{
public:

  using etl::message_broker::receive;

  void receive(const etl::imessage& msg) override
  {
    ELSF_LOG_INFO("Broker received message: {}", msg.get_message_id());
    etl::message_broker::receive(msg);
  }
};