#include "navigation/messaging/sender/message_sender.h"

#include <protocols/behavior/behavior_unification.pb.h>
#include <robocin/output/log.h>
#include <robocin/wip/service_discovery/addresses.h>

namespace navigation {
namespace {

namespace service_discovery = robocin::service_discovery;

using ::robocin::ilog;

namespace rc {

using ::protocols::navigation::Navigation;

} // namespace rc

} // namespace

MessageSender::MessageSender(std::unique_ptr<::robocin::IZmqPublisherSocket> detection_socket) :
    detection_socket_{std::move(detection_socket)} {}

void MessageSender::send(const rc::Navigation& navigation) {
  // ilog("sending... {}", navigation.DebugString());

  detection_socket_->send({
      service_discovery::kNavigationTopic,
      navigation.SerializeAsString(),
  });
}

} // namespace navigation
