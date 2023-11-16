#include <string>

#include <absl/synchronization/mutex.h>
#include <absl/time/clock.h>
#include <absl/time/time.h>

#include "vision/common/publish_subscribe.h"
#include "vision/common/utility.h"
#include "vision/common/zmq_publish_subscribe.h"

#include "google/protobuf/util/time_util.h"

using vision::ITopicPublisher;
using vision::ITopicSubscriber;
using vision::PubSubMode;
using vision::ZmqPublisher;
using vision::ZmqSubscriber;

int main(int /*argc*/, char *argv[]) {
  int service_id = std::stoi(argv[1]);

  std::unique_ptr<ITopicSubscriber> subscriber =
      std::make_unique<ZmqSubscriber>("robocin");
  subscriber->connect("ipc:///tmp/channel" + std::to_string(service_id - 1) +
                      ".ipc");

  std::unique_ptr<ITopicPublisher> publisher = std::make_unique<ZmqPublisher>();
  publisher->bind("ipc:///tmp/channel" + std::to_string(service_id) + ".ipc");

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
      std::vector<int64_t> order;
      for (const auto& s : pck) {
        order.emplace_back(std::stoll(s));
      }
      assert(order.front() == *std::min_element(order.begin(), order.end()));

      std::cout << "elapsed: "
                << (absl::GetCurrentTimeNanos() - order.front()) / 1e6 << ", received: " << pck.size() << '\n';
    }
  }

  return 0;
}
