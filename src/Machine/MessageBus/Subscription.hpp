#pragma once

#include <etl/message_broker.h>
#include <etl/vector.h>

namespace Machine::MessageBus
{

// Custom subscription type.
class Subscription : public etl::message_broker::subscription
{
public:

  Subscription(etl::imessage_router& router, const etl::vector<etl::message_id_t, 10>& id_list_);

  etl::message_broker::message_id_span_t message_id_list() const override;

  etl::vector<etl::message_id_t, 10> id_list;

  virtual ~Subscription() = default;
};


} // namespace Machine::MessageBus