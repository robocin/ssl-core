package metrics

import (
	"fmt"
	"sync"

	"github.com/robocin/ssl-core/common/golang/network"
	"github.com/robocin/ssl-core/protocols/playback"
	"github.com/robocin/ssl-core/protocols/third_party/game_controller"
	"google.golang.org/protobuf/proto"
)

type TimeMeasurementFromAutoRefInputToPlaybackOutput struct {
	*TimeMeasurement
	maxWaitPackages int
	hasReferenceID  bool
	referenceID     uint32
	mu              sync.Mutex
}

func NewPipelineTimeMeasurement(waitCount int) *TimeMeasurementFromAutoRefInputToPlaybackOutput {
	return &TimeMeasurementFromAutoRefInputToPlaybackOutput{
		TimeMeasurement: NewTimeMeasurement(waitCount),
		hasReferenceID:  false,
		referenceID:     0,
		mu:              sync.Mutex{},
	}
}

func (tm *TimeMeasurementFromAutoRefInputToPlaybackOutput) GetStartTime(datagram network.ZmqMultipartDatagram) {
	tm.mu.Lock()
	defer tm.mu.Unlock()

	fmt.Println("GetStartTime")
	var trackedPacket game_controller.TrackerWrapperPacket
	err := proto.Unmarshal(datagram.Message, &trackedPacket)
	if err != nil {
		fmt.Println("Error unmarshalling TrackerWrapperPacket", err)
		return
	}

	if trackedPacket.GetTrackedFrame() == nil {
		fmt.Println("TrackedFrame is nil")
		return
	}

	if tm.hasReferenceID && tm.TimeMeasurement.SaveStartTime() {
		fmt.Println("Saving start time for referenceID", tm.referenceID)
		tm.referenceID = trackedPacket.GetTrackedFrame().GetFrameNumber()
		tm.hasReferenceID = true
	}
}

func (tm *TimeMeasurementFromAutoRefInputToPlaybackOutput) GetEndTime(datagram network.ZmqMultipartDatagram) {
	tm.mu.Lock()
	defer tm.mu.Unlock()

	fmt.Println("GetEndTime")
	var sample playback.Sample
	err := proto.Unmarshal(datagram.Message, &sample)
	if err != nil {
		fmt.Println("Error unmarshalling Sample", err)
		return
	}

	if sample.GetTrackedDetection() == nil {
		fmt.Println("TrackedDetection is nil on Sample")
		return
	}

	if sample.GetTrackedDetection().GetSerialId() >= tm.referenceID {
		fmt.Println("Saving end time for referenceID", tm.referenceID)
		tm.hasReferenceID = false
		tm.TimeMeasurement.SaveEndTime()
	}
}
