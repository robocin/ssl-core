#include "vision/common/publish_subscribe.h"

namespace vision {

ITopicSubscriber::ITopicSubscriber(std::string_view topic) : topic_(topic) {}

} // namespace vision
