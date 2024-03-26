#include <condition_variable>
#include <robocin/network/zmq_subscriber_socket.h>
#include <thread>
#include <vector>

namespace vision {

template <class Datagram>
class IController {
 public:
  IController() = default;

  IController(const IController&) = delete;
  IController& operator=(const IController&) = delete;
  IController(IController&&) = delete;
  IController& operator=(IController&&) = delete;

  virtual ~IController() = default;

  void run() {
    std::jthread consumer_thread([this] {
      while (true) {
        {
          std::lock_guard lock(mutex_);

          std::vector<Datagram> datagrams = consume();
          datagrams_.insert(datagrams_.end(),
                            std::make_move_iterator(datagrams.begin()),
                            std::make_move_iterator(datagrams.end()));
        }
        cv_.notify_one();
      }
    });

    std::jthread producer_thread([this] {
      while (true) {
        std::vector<Datagram> datagrams;
        {
          std::unique_lock lock(mutex_);
          cv_.wait(lock, [&] { return !datagrams_.empty(); });

          datagrams.swap(datagrams_);
        }
        produce(datagrams);
      }
    });
  }

  virtual std::vector<Datagram> consume() = 0;
  virtual void produce(std::vector<Datagram>& datagrams) = 0;

 private:
  std::mutex mutex_;
  std::condition_variable cv_;
  std::vector<Datagram> datagrams_;
};

class Controller : public IController<robocin::ZmqDatagram> {
 public:
  std::vector<robocin::ZmqDatagram> consume() final { return {}; }
  void produce(std::vector<robocin::ZmqDatagram>& datagrams) final {}
};

} // namespace vision
