#ifndef ROBOCIN_COMMON_ZMQ_PUBLISH_SUBSCRIBE_H
#define ROBOCIN_COMMON_ZMQ_PUBLISH_SUBSCRIBE_H

#include "robocin/common/publish_subscribe.h"

#include <string>
#include <string_view>
#include <zmq.hpp>

namespace robocin {

class ZmqPublisher : public ITopicPublisher {
 public:
  explicit ZmqPublisher(int n_threads);
  ZmqPublisher();
  void bind(std::string_view address) override;
  void send(std::string_view topic, PubSubMode mode, std::string_view message) override;

 private:
  ::zmq::context_t context_;
  ::zmq::socket_t publisher_;
};

class ZmqSubscriber : public ITopicSubscriber {
 public:
  ZmqSubscriber(std::string_view topic, int n_threads);
  explicit ZmqSubscriber(std::string_view topic);
  void connect(std::string_view address) override;
  bool receive(PubSubMode mode, std::string& result) override;

 private:
  ::zmq::context_t context_;
  ::zmq::socket_t subscriber_;
};

} // namespace robocin

#endif // ROBOCIN_COMMON_ZMQ_PUBLISH_SUBSCRIBE_H
