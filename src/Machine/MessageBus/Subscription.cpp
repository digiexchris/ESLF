#include "Subscription.hpp"

namespace Machine::MessageBus 
{

Subscription::Subscription(etl::imessage_router& router, const etl::vector<etl::message_id_t, 10>& id_list_)
    : etl::message_broker::subscription(router)
    , id_list(id_list_)
  {
  }

  etl::message_broker::message_id_span_t Subscription::message_id_list() const
  {
    return etl::message_broker::message_id_span_t(id_list.begin(), id_list.end());
  }

} // namespace Machine::MessageBus