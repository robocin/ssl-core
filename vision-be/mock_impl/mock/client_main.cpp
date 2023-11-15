#include <string>

#include <absl/synchronization/mutex.h>
#include <absl/time/clock.h>
#include <absl/time/time.h>

#include "mock/common/publish_subscribe.h"
#include "mock/common/utility.h"
#include "mock/common/zmq_publish_subscribe.h"

using ines::ITopicPublisher;
using ines::ITopicSubscriber;
using ines::PubSubMode;
using ines::ZmqPublisher;
using ines::ZmqSubscriber;

int main(int argc, char *argv[]) {
  int service_id = std::atoi(argv[1]);

  std::unique_ptr<ITopicSubscriber> subscriber =
      std::make_unique<ZmqSubscriber>("robocin");
  subscriber->connect("ipc:///tmp/channel" + std::to_string(service_id - 1)  + ".ipc");

  std::unique_ptr<ITopicPublisher> publisher = std::make_unique<ZmqPublisher>();
  publisher->bind("ipc:///tmp/channel" + std::to_string(service_id) +
                  ".ipc");

  long long cycle = 0;
  while(true) {
    std::string pck = "s";

    if(service_id == 0) {
      auto start_time = absl::ToUnixNanos(absl::Now());
      std::cout << "cycle: " << cycle << " id: " << service_id << ": " << start_time << '\n';
    } else {
      subscriber->receive(PubSubMode::Wait, pck);
    }
   
    publisher->send("robocin", PubSubMode::Wait, pck);

    if(service_id == 5) {
      // std::cout << service_id << ": " << end_time << ", diff:"
      //     << absl::ToInt64Nanoseconds(end_time - start_time) / 1e6 << '\n';
      auto start_time = absl::ToUnixNanos(absl::Now());
      std::cout << "cycle: " << cycle << " id: " << service_id << ": " << start_time << '\n';
    } 

    ++cycle;
  }

  return 0;
}
