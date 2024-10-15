#include "navigation/messaging/receiver/payload_mapper.h"

#include "navigation/messaging/receiver/payload.h"

#include <robocin/network/zmq_datagram.h>
#include <robocin/output/log.h>
#include <robocin/wip/service_discovery/addresses.h>

namespace navigation {
namespace {

namespace service_discovery = robocin::service_discovery;

using ::robocin::wlog;
using ::robocin::ZmqDatagram;

namespace rc {

using ::protocols::behavior::unification::Behavior;

} // namespace rc

} // namespace

Payload PayloadMapper::fromZmqDatagrams(std::span<const ZmqDatagram> messages) const {
  std::vector<rc::Behavior> behaviors;

  for (const ZmqDatagram& zmq_datagram : messages) {
    if (zmq_datagram.topic() == service_discovery::kBehaviorTopic) {
      rc::Behavior behavior;
      behavior.ParseFromString(std::string{zmq_datagram.message()});
      behaviors.emplace_back(std::move(behavior));

    } else {
      // wlog("zmq_datagram with topic '{}' not processed.", zmq_datagram.topic());
    }
  }

  return Payload{std::move(behaviors)};
}

} // namespace navigation
