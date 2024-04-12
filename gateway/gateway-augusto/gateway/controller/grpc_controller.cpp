#include "gateway/controller/grpc_controller.h"

#include "gateway/service_discovery.h"
#include "robocin/network/zmq_request_reply_socket.h"
#include "robocin/network/zmq_subscriber_socket.h"

#include <grpcpp/server_builder.h>
#include <protocols/ui/gateway.grpc.pb.h>
#include <protocols/ui/gateway.pb.h>
#include <protocols/vision/frame.pb.h>
#include <string>
#include <string_view>
namespace gateway {

namespace {

constexpr std::string_view kGatewayLive = "Gateway.Live";
constexpr std::string_view kVisionPubService = "Vision.Publisher";
constexpr std::string_view kVisionRepService = "Vision.Reply";

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using protocols::ui::GatewayService;
using protocols::ui::GetVisionChunkRequest;
using protocols::ui::GetVisionChunkResponse;
using protocols::ui::ReceiveLiveStreamRequest;
using protocols::ui::ReceiveLiveStreamResponse;
using robocin::ZmqRequestSocket;
using robocin::ZmqSubscriberSocket;

class GatewayServiceImpl final : public GatewayService::Service {
 public:
  GatewayServiceImpl() {
    requester_.connect(SServiceDiscovery.lookup(kVisionRepService).address);

    {
      auto [address, topics] = SServiceDiscovery.lookup(kVisionPubService);
      vision_subscriber_.connect(address, topics);
    }
  }

  Status GetVisionChunk(ServerContext* context,
                        const GetVisionChunkRequest* request,
                        GetVisionChunkResponse* response) override {
    requester_.send(request->SerializeAsString());
    auto reply = requester_.receive();
    *response = deserialize<GetVisionChunkResponse>(reply);
    return Status::OK;
  }

  Status ReceiveLiveStream(ServerContext* context,
                           const ReceiveLiveStreamRequest* request,
                           grpc::ServerWriter<ReceiveLiveStreamResponse>* writer) override {

    std::vector<zmq::pollitem_t> items;
    items.reserve(request->message_types_size());
    for (auto message_type : request->message_types()) {
      switch (message_type) {
        case protocols::ui::MESSAGE_TYPE_VISION:
          items.push_back({&vision_subscriber_, 0, ZMQ_POLLIN, 0});
        // case protocols::ui::MESSAGE_TYPE_REFEREE:
        //   items.push_back({&referee_subscriber_, 0, ZMQ_POLLIN, 0});
        default: std::cout << "Unsuported type\n";
      }
    }

    while (true) {
      zmq::poll(items);
      if (items[0].revents & ZMQ_POLLIN) {
        auto reply = vision_subscriber_.receive();
        ReceiveLiveStreamResponse response;
        *response.mutable_payload()->mutable_vision_frame()
            = deserialize<protocols::vision::Frame>(reply.message);
        writer->Write(response);
      }

      if (items[1].revents & ZMQ_POLLIN) {
        auto reply = vision_subscriber_.receive();
        ReceiveLiveStreamResponse response;
        *response.mutable_payload()->mutable_referee()
            = deserialize<protocols::referee::Referee>(reply.message);
        writer->Write(response);
      }
    }
  }

 private:
  ZmqRequestSocket requester_;
  ZmqSubscriberSocket vision_subscriber_;
  ZmqSubscriberSocket referee_subscriber_;

  template <class Response>
  static Response deserialize(std::string_view reply) {
    Response chunk;
    chunk.ParseFromString(std::string{reply});
    return chunk;
  }

  static ReceiveLiveStreamResponse buildLiveStreamResponse(std::string_view reply) {
    ReceiveLiveStreamResponse response;
    *response.mutable_payload()->mutable_vision_frame()
        = deserialize<protocols::vision::Frame>(reply);
    return response;
  }
};

} // namespace

GrpcController::GrpcController(std::string_view address) : address_{address} {}

void GrpcController::run() {
  ServerBuilder builder;
  builder.AddListeningPort(address_, grpc::InsecureServerCredentials());

  GatewayServiceImpl service;
  builder.RegisterService(&service);

  std::unique_ptr<Server> server(builder.BuildAndStart());
  server->Wait();
}

} // namespace gateway
