#ifndef DF3CB14B_C50E_4D75_A70F_9E0C26714A89
#define DF3CB14B_C50E_4D75_A70F_9E0C26714A89
#ifndef NAVIGATION_MESSAGING_RECEIVER_PAYLOAD_H
#define NAVIGATION_MESSAGING_RECEIVER_PAYLOAD_H

#include <protocols/behavior/behavior_unification.pb.h>
#include <robocin/network/zmq_datagram.h>
#include <span>
#include <vector>

namespace navigation {

class Payload {
 public:
  Payload(std::vector<::protocols::behavior::unification::Behavior> behaviors);

  [[nodiscard]] std::span<const ::protocols::behavior::unification::Behavior> getBehaviors() const;

  [[nodiscard]] bool empty() const;

 private:
  std::vector<::protocols::behavior::unification::Behavior> behaviors_;
};

} // namespace navigation

#endif // NAVIGATION_MESSAGING_RECEIVER_PAYLOAD_H

#endif /* DF3CB14B_C50E_4D75_A70F_9E0C26714A89 */
