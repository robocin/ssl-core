#include "robocin/common/zmq_publish_subscribe.h"

namespace robocin {

namespace {

using enum PubSubMode;

constexpr int kSingleThread = 1;

} // namespace

// ZmqPublisher ------------------------------------------------------------------------------------
ZmqPublisher::ZmqPublisher(int n_threads) : context_(n_threads), publisher_(context_, ZMQ_PUB) {}

ZmqPublisher::ZmqPublisher() : ZmqPublisher(kSingleThread) {}

void ZmqPublisher::bind(std::string_view address) { publisher_.bind(address.data()); }

void ZmqPublisher::send(std::string_view topic, PubSubMode mode, std::string_view message) {
  zmq::send_flags flags = mode == DontWait ? zmq::send_flags::dontwait : zmq::send_flags::none;

  zmq::message_t zmq_topic(topic);
  publisher_.send(zmq_topic, zmq::send_flags::sndmore);

  zmq::message_t zmq_message(message);
  publisher_.send(zmq_message, flags);
}

// ZmqSubscriber -----------------------------------------------------------------------------------
ZmqSubscriber::ZmqSubscriber(std::string_view topic, int n_threads) :
    ITopicSubscriber(topic),
    context_(n_threads),
    subscriber_(context_, ZMQ_SUB) {}

ZmqSubscriber::ZmqSubscriber(std::string_view topic) : ZmqSubscriber(topic, kSingleThread) {}

void ZmqSubscriber::connect(std::string_view address) {
  subscriber_.connect(address.data());
  subscriber_.set(zmq::sockopt::subscribe, topic());
}

bool ZmqSubscriber::receive(PubSubMode mode, std::string& result) {
  zmq::recv_flags flags = mode == DontWait ? zmq::recv_flags::dontwait : zmq::recv_flags::none;

  if (zmq::message_t zmq_topic; subscriber_.recv(zmq_topic, flags)) {
    if (zmq::message_t zmq_result; subscriber_.recv(zmq_result, flags)) {
      result.assign(zmq_result.to_string());
      return true;
    }
  }
  return false;
}

} // namespace robocin
