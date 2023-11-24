#include "robocin/common/publish_subscribe.h"
#include "robocin/common/zmq_publish_subscribe.h"
#include "vision/network_interface_utility.h"

#include <absl/synchronization/mutex.h>
#include <absl/time/clock.h>
#include <absl/time/time.h>
#include <condition_variable>
#include <span>
#include <string>
#include <thread>

using robocin::ITopicPublisher;
using robocin::ITopicSubscriber;
using robocin::PubSubMode;
using robocin::ZmqPublisher;
using robocin::ZmqSubscriber;

constexpr double kNanosPerMilli = 1'000'000.0;

std::mutex mutex;
std::condition_variable cv;
std::vector<std::string> pck;

void subscriberRun(int service_id) {
  std::unique_ptr<ITopicSubscriber> subscriber = std::make_unique<ZmqSubscriber>("robocin");
  subscriber->connect(std::format("ipc:///tmp/channel{}.ipc", service_id - 1));

  while (true) {
    {
      std::lock_guard lock(mutex);

      // polling.
      //

      if (service_id > 0) {
        // Receiving using ipc
        std::string current;
        while (subscriber->receive(PubSubMode::DontWait, current)) {
          pck.emplace_back(std::move(current));
        }
      } else {
        // Receiving using udp
        pck.emplace_back(std::to_string(absl::GetCurrentTimeNanos()));
      }
    }

    cv.notify_one();
  }
}

void publisherRun(int service_id) {
  std::unique_ptr<ITopicPublisher> publisher = std::make_unique<ZmqPublisher>();
  publisher->bind(std::format("ipc:///tmp/channel{}.ipc", service_id));

  while (true) {
    std::unique_lock lock(mutex);
    cv.wait(lock, [&] { return !pck.empty(); });

    publisher->send("robocin", PubSubMode::Wait, pck.back());

    if (service_id > 1) {
      std::cout << std::format(
          "elapsed: {:^7.3f}ms, received: {:^3}\n",
          static_cast<double>(absl::GetCurrentTimeNanos() - std::stoll(pck.front()))
              / kNanosPerMilli,
          pck.size());
    }

    pck.clear();
  }
}

int main(int argc, char* argv[]) {
  auto entries = robocin::network_interface_utility::all_interface_entries();

  for (const auto& entry : entries) {
    std::cout << std::format("interface: {}, address: {}\n", entry.first, entry.second);
  }

  return 0;

  std::span args{argv + 1, argv + argc - 1};
  int service_id = std::stoi(args.front());

  std::jthread subscriber_thread(subscriberRun, service_id);
  std::jthread publisher_thread(publisherRun, service_id);

  return 0;
}
