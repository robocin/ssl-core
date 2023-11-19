#ifndef ROBOCIN_COMMON_PUBLISH_SUBSCRIBE_H
#define ROBOCIN_COMMON_PUBLISH_SUBSCRIBE_H

#include "robocin/common/concepts.h"

#include <string_view>

namespace robocin {

enum class PubSubMode : std::uint8_t {
  Wait = 0,
  DontWait = 1
};

class ITopicPublisher {
 public:
  virtual ~ITopicPublisher() = default;

  virtual void bind(std::string_view address) = 0;
  virtual void send(std::string_view topic, PubSubMode mode, std::string_view message) = 0;

  template <protobuf Pb>
  void send(std::string_view topic, PubSubMode mode, const Pb& proto) {
    std::string serialized_message;
    proto.SerializeToString(&serialized_message);
    send(topic, mode, serialized_message);
  }
};

class ITopicSubscriber {
 public:
  explicit ITopicSubscriber(std::string_view topic);

  virtual ~ITopicSubscriber() = default;

  virtual void connect(std::string_view address) = 0;
  virtual bool receive(PubSubMode mode, std::string& result) = 0;

  template <protobuf Pb>
  bool receive(PubSubMode mode, Pb& proto) {
    if (std::string str_result; receive(mode, str_result)) {
      proto.ParseFromString(str_result);
      return true;
    }
    return false;
  }

  [[nodiscard]] std::string_view topic() const;

 private:
  std::string topic_;
};

} // namespace robocin

#endif // ROBOCIN_COMMON_PUBLISH_SUBSCRIBE_H
