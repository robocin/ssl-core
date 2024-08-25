package main

import (
	"fmt"
	"os"
	"strconv"
	"sync"

	"github.com/robocin/ssl-core/common/golang/network"
	"github.com/robocin/ssl-core/gateway/gateway-augusto/internal/metrics"
	"github.com/robocin/ssl-core/gateway/gateway-augusto/internal/server"
	"github.com/robocin/ssl-core/gateway/gateway-augusto/internal/socket"
	"github.com/robocin/ssl-core/gateway/gateway-augusto/internal/worker"
)

func startGatewayUdpMulticastWorker(address string, proxy chan network.ZmqMultipartDatagram, topic string, wg *sync.WaitGroup, onReceive func(datagram network.ZmqMultipartDatagram)) {
	defer wg.Done()

	w := worker.NewUdpMulticastWorker(address, 2048, proxy, topic, onReceive)
	w.Listen()
}

func startGatewayZmqServer(proxy chan network.ZmqMultipartDatagram, wg *sync.WaitGroup) {
	defer wg.Done()

	server := server.NewZqmServer("ipc:///tmp/.ssl-core/gateway.ipc", proxy)
	server.Start()
}

func startGatewayGrpcServer(wg *sync.WaitGroup) {
	defer wg.Done()

	server := server.NewGrpcServer("0.0.0.0:50051")
	server.Start()
}

func interceptUDPWorkerWith(timeMeasurement *metrics.TimeMeasurementFromAutoRefInputToPlaybackOutput, address string, proxy chan network.ZmqMultipartDatagram, topic string, wg *sync.WaitGroup) {
	defer wg.Done()

	w := worker.NewUdpMulticastWorker(address, 2048, proxy, topic, timeMeasurement.GetStartTime)
	w.Listen()
}

func interceptGrpcServerWith(timeMeasurement *metrics.TimeMeasurementFromAutoRefInputToPlaybackOutput, wg *sync.WaitGroup) {
	defer wg.Done()

	subscriber := socket.NewSocketReceiverHandler(
		network.NewZmqSubscriberSocket("ipc:///tmp/.ssl-core/gateway.ipc", "sample"),
		timeMeasurement.GetEndTime,
	)
	server := server.NewGrpcServerWithSubscriberHandler("0.0.0.0:50051", *subscriber)
	server.Start()
}

func main() {
	visionPort := os.Getenv("VISION_PORT")
	if visionPort == "" {
		fmt.Println("VISION_PORT not set")
		return
	}

	gcPort := os.Getenv("GC_PORT")
	if gcPort == "" {
		fmt.Println("GC_PORT not set")
		return
	}

	fmt.Println("gateway-augusto is running!")

	// TODO(aalmds): refactor addresses with service discovery
	// TODO(aalmds): review error handlers

	proxy := make(chan network.ZmqMultipartDatagram)

	wg := sync.WaitGroup{}
	wg.Add(5)

	go startGatewayUdpMulticastWorker(fmt.Sprintf("224.5.23.2:%s", visionPort), proxy, "vision-third-party", &wg, nil)
	go startGatewayUdpMulticastWorker(fmt.Sprintf("224.5.23.1:%s", gcPort), proxy, "referee-third-party", &wg, nil)
	go startGatewayZmqServer(proxy, &wg)

	if os.Getenv("INTERCEPT") == "true" {
		waitPackages := os.Getenv("WAIT_PACKAGES")
		if waitPackages == "" {
			fmt.Println("WAIT_PACKAGES not set")
			return
		}
		waitPackagesInt, err := strconv.Atoi(waitPackages)
		if err != nil {
			fmt.Println("Invalid WAIT_PACKAGES value")
			return
		}
		timeMeasurement := metrics.NewPipelineTimeMeasurement(waitPackagesInt)
		go interceptUDPWorkerWith(timeMeasurement, "224.5.23.2:10010", proxy, "tracked-third-party", &wg)
		go interceptGrpcServerWith(timeMeasurement, &wg)
	} else {
		go startGatewayUdpMulticastWorker("224.5.23.2:10010", proxy, "tracked-third-party", &wg, nil)
		go startGatewayGrpcServer(&wg)
	}

	wg.Wait()
}
