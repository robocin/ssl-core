#include "robocin/common/publish_subscribe.h"
#include "robocin/common/zmq_publish_subscribe.h"

#include <absl/synchronization/mutex.h>
#include <absl/time/clock.h>
#include <absl/time/time.h>
#include <span>
#include <string>

using robocin::ITopicPublisher;
using robocin::ITopicSubscriber;
using robocin::PubSubMode;
using robocin::ZmqPublisher;
using robocin::ZmqSubscriber;

class Point {
 public:
  int x, y;
};

constexpr double kNanosPerMilli = 1'000'000;

int main(int argc, char* argv[]) {
  std::span args{argv + 1, argv + argc - 1};
  int service_id = std::stoi(args.front());

  std::unique_ptr<ITopicSubscriber> subscriber = std::make_unique<ZmqSubscriber>("robocin");
  subscriber->connect(std::format("ipc:///tmp/channel{}.ipc", service_id - 1));

  std::unique_ptr<ITopicPublisher> publisher = std::make_unique<ZmqPublisher>();
  publisher->bind(std::format("ipc:///tmp/channel{}.ipc", service_id));

  while (true) {
    std::vector<std::string> pck;

    if (service_id > 0) {
      std::string current;
      while (subscriber->receive(PubSubMode::DontWait, current)) {
        pck.emplace_back(std::move(current));
      }
      if (pck.empty()) {
        continue;
      }
    } else {
      pck.emplace_back(std::to_string(absl::GetCurrentTimeNanos()));
    }

    publisher->send("robocin", PubSubMode::Wait, pck.back());

    if (service_id > 4) {
      std::cout << std::format(
          "elapsed: {:^7.3f}ms, received: {:^3}\n",
          static_cast<double>(absl::GetCurrentTimeNanos() - std::stoll(pck.front()))
              / kNanosPerMilli,
          pck.size());
    }
  }

  return 0;
}
