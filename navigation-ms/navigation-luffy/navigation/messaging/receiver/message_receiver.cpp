#include "navigation/messaging/receiver/message_receiver.h"

#include "navigation/parameters/parameters.h"

#include <robocin/network/zmq_datagram.h>
#include <robocin/network/zmq_poller.h>
#include <robocin/output/log.h>

namespace navigation {
namespace {

using ::robocin::ilog;
using ::robocin::IZmqPoller;
using ::robocin::IZmqSubscriberSocket;
using ::robocin::wlog;
using ::robocin::ZmqDatagram;

} // namespace

MessageReceiver::MessageReceiver(std::unique_ptr<::robocin::IZmqSubscriberSocket> behavior_socket,
                                 std::unique_ptr<::robocin::IZmqSubscriberSocket> detection_socket,
                                 std::unique_ptr<::robocin::IZmqSubscriberSocket> game_status_socket,
                                 std::unique_ptr<::robocin::IZmqPoller> zmq_poller,
                                 std::unique_ptr<IPayloadMapper> payload_mapper) :
  behavior_socket_{std::move(behavior_socket)},
  detection_socket_{std::move(detection_socket)},
  game_status_socket_{std::move(game_status_socket)},
  zmq_poller_{std::move(zmq_poller)},
  payload_mapper_{std::move(payload_mapper)} {}

Payload MessageReceiver::receive() {
  // ilog("running.");

  std::vector<ZmqDatagram> datagrams{};

  while (datagrams.empty()) {
    zmq_poller_->poll(pNavigationPollerTimeoutMs());

    while (true) {
      ZmqDatagram behavior_zmq_datagram = zmq_poller_->receive(*behavior_socket_);
      if (behavior_zmq_datagram.empty()) {
        break;
      }

      datagrams.emplace_back(std::move(behavior_zmq_datagram));
    }

    while (true) {
      ZmqDatagram game_status_zmq_datagram = zmq_poller_->receive(*game_status_socket_);
      if (game_status_zmq_datagram.empty()) {
        break;
      }

      datagrams.emplace_back(std::move(game_status_zmq_datagram));
    }

    while (true) {
      ZmqDatagram detection_zmq_datagram = zmq_poller_->receive(*detection_socket_);
      if (detection_zmq_datagram.empty()) {
        break;
      }

      datagrams.emplace_back(std::move(detection_zmq_datagram));
    }

    if (datagrams.empty()) {
      // wlog("no datagram received after {} ms.", pRefereePollerTimeoutMs());
    }
  }

  return payload_mapper_->fromZmqDatagrams(datagrams);
}

} // namespace navigation
