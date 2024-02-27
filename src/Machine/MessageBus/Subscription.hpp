#pragma once

#include <etl/message_broker.h>

namespace Machine{
namespace MessageBus{

// Custom subscription type.
class Subscription : public etl::message_broker::subscription
{
public:

  Subscription(etl::imessage_router& router, std::vector<etl::message_id_t> id_list_);

  etl::message_broker::message_id_span_t message_id_list() const override;

  std::vector<etl::message_id_t> id_list;
};


} // namespace MessageBus
} // namespace State