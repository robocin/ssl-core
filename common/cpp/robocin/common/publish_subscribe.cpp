#include "robocin/common/publish_subscribe.h"

namespace robocin {

ITopicSubscriber::ITopicSubscriber(std::string_view topic) : topic_(topic) {}

std::string_view ITopicSubscriber::topic() const { return topic_; }

} // namespace robocin
