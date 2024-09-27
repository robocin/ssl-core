from datetime import timedelta, datetime as dt
import json
import argparse
import sys
import time
from concurrent import futures
import logging
import math
import grpc

from network.multicast_udp_publisher_subscriber import (
    MulticastUdpPublisherSocket,
    MulticastUdpSubscriberSocket,
)
from network.pub_sub_mode import PubSubMode
from network.zmq_publisher_subscriber import ZmqPublisherSocket, ZmqSubscriberSocket
from utility.protobuf import parse_from_textpb, serialize
from pathlib import Path
import protocols.gateway.gateway_service_pb2_grpc as gateway_service_pb2_grpc
import protocols.gateway.gateway_service_pb2 as gateway_service_pb2
from google.protobuf import timestamp_pb2
from protocols.common import geometry_pb2, robot_id_pb2
from protocols.playback import sample_pb2, detection_pb2, field_pb2, game_status_pb2, raw_detection_pb2, tracked_detection_pb2
from protocols.common import game_stage_pb2
from protocols.common import match_type_pb2

first_timestamp = timestamp_pb2.Timestamp()
first_timestamp.GetCurrentTime()

def create_field():
    return field_pb2.Field(
        width=9000,
        length=12000,
        goal_depth=180,
        boundary_width=300,
        goal_width=1800,
        penalty_area_depth=1800,
        penalty_area_width=3600,
        goal_center_to_penalty_mark=8000
    )

def create_detection():
    balls = [
        detection_pb2.Detection.Ball(
            confidence=1,
            kick_information=None,
            position=geometry_pb2.Point3Df(x=0, y=0, z=0),
            velocity=geometry_pb2.Point3Df(x=0, y=0, z=0)
        )]

    robots = [
        detection_pb2.Detection.Robot(
            angle=None,
            angular_velocity=None,
            confidence=1,
            dribbler_width=60,
            feedback=None,
            height=140,
            position=geometry_pb2.Point2Df(x=-3199.97266 + i * 400, y=-2250 + i * 400),
            radius=90,
            robot_id=robot_id_pb2.RobotId(color=robot_id_pb2.RobotId.Color.COLOR_BLUE, number=i),
            velocity=None
        ) for i in range(11)]

    return detection_pb2.Detection(
        serial_id=1,
        expected_framerate=60,
        created_at=first_timestamp,
        balls=balls,
        robots=robots
    )

def create_game_status():
    home_team = game_status_pb2.GameStatus.Team(
        name="RobôCIn",
        consecutive_ball_placement_failures=0,
        goalkeeper_id=robot_id_pb2.RobotId(color=robot_id_pb2.RobotId.COLOR_BLUE, number=0),
        has_ball_placement_failures_reached_maximum=False,
        is_ball_placement_enabled=False,
        is_robot_substitution_allowed=False,
        is_robot_substitution_requested=False,
        maximum_allowed_robots=11,
        red_cards=0,
        robot_ids=[robot_id_pb2.RobotId(color=robot_id_pb2.RobotId.COLOR_BLUE, number=i) for i in range(11)],
        robot_substitution_time_left=None,
        robot_substitutions_left=0,
        score=0,
        time_to_expire_active_yellow_cards=None,
        timeouts_left=0,
        total_fouls_committed=0,
        total_timeout_time_left=None,
        yellow_cards=0
    )

    away_team = game_status_pb2.GameStatus.Team(
        name="Unknown",
        consecutive_ball_placement_failures=0,
        goalkeeper_id=robot_id_pb2.RobotId(color=robot_id_pb2.RobotId.COLOR_YELLOW, number=0),
        has_ball_placement_failures_reached_maximum=False,
        is_ball_placement_enabled=False,
        is_robot_substitution_allowed=False,
        is_robot_substitution_requested=False,
        maximum_allowed_robots=11,
        red_cards=0,
        robot_ids=[],
        robot_substitution_time_left=None,
        robot_substitutions_left=0,
        score=0,
        time_to_expire_active_yellow_cards=None,
        timeouts_left=0,
        total_fouls_committed=0,
        total_timeout_time_left=None,
        yellow_cards=0
    )
    
    return game_status_pb2.GameStatus(
        away_team=away_team,
        command=None,
        command_issued_timestamp=None,
        description='',
        game_events=[],
        game_events_proposals=[],
        game_stage=game_stage_pb2.GAME_STAGE_NORMAL_FIRST_HALF,
        game_stage_time_left=None,
        home_team=home_team,
        is_home_team_on_positive_half=True,
        match_type=match_type_pb2.MATCH_TYPE_FRIENDLY,
        next_command=None,
        source_id='',
        timestamp=first_timestamp,
        total_commands_issued=0
    )

def create_sample():
    global first_timestamp
    timestamp = timestamp_pb2.Timestamp()
    timestamp.GetCurrentTime()
    return sample_pb2.Sample(timestamp=timestamp, first_timestamp=first_timestamp, raw_detection=None, tracked_detection=None, field=create_field(), detection=create_detection(), game_status=create_game_status())

class GatewayServiceServicer(gateway_service_pb2_grpc.GatewayServiceServicer):
    def __init__(self):
        print("server")

    def ReceiveLivestream(self, request_iterator, context):
        print("init connection")
        for message in request_iterator:
            f = 840
            count = -1
            fps = 60
            
            total_sent = 0
            diffs = []

            interval = 1 / fps  # Time interval between messages

            start_time = dt.now()
            next_send_time = start_time  # Set the initial time to start sending

            n = -2500

            while total_sent != count:
                now = dt.now()

                # If the current time is greater than or equal to the next scheduled time, send the message
                if now >= next_send_time:
                    # print(f"sending: {total_sent}")
                    pub_time = now
                    # publisher.send(serialized_message)

                    # if subscriber:
                    #     received = subscriber.receive(PubSubMode.Wait)
                    #     if received:
                    #         rcv_time = dt.now()
                    #         diffs.append((rcv_time - pub_time).total_seconds() * 1000)

                    total_sent += 1
                    next_send_time += timedelta(seconds=interval)  # Schedule next message send
                    
                    n += 1
                    f += 1
                    
                    # Ensure the value stays within the range [-2500, -500]
                    if n > -500:
                        n = -2500
                    elif n < -2500:
                        n = -500
                    
                    # print(message)
                    entity = gateway_service_pb2.ReceiveLivestreamResponse(
                        sample=create_sample()
                    )
                    yield entity

                    if (total_sent % 60 == 0):
                        print(f"time: {now}, fps: {60 / (now - start_time).total_seconds()}")
                        start_time = now

                # Sleep for a very short time to prevent busy-waiting (optional)
                time.sleep(0.001)  # A short sleep to yield CPU for other processes
        return
#   rpc ReceiveLivestream(stream ReceiveLivestreamRequest) returns (stream ReceiveLivestreamResponse);
#   rpc GetGameEvents(GetGameEventsRequest) returns (GetGameEventsResponse);
#   rpc GetReplayChunk(GetReplayChunkRequest) returns (GetReplayChunkResponse);


if __name__ == "__main__":
    print("initializing")

    print(create_sample())
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    gateway_service_pb2_grpc.add_GatewayServiceServicer_to_server(
        GatewayServiceServicer(), server
    )
    server.add_insecure_port("[::]:50053")
    server.start()
    server.wait_for_termination()

    # TODO($ISSUE_N): Fix to work calling from any directory.
    # os.chdir(os.path.dirname(os.path.abspath(__file__)))


    # total_sent = 0
    # diffs = []
    # while total_sent != count:
    #     print(f"sending: {total_sent}")
    #     pub_time = dt.now()
    #     publisher.send(serialized_message)
    #     # if subscriber:
    #     #     received = subscriber.receive(PubSubMode.Wait)
    #     #     if received:
    #     #         rcv_time = dt.now()
    #     #         diffs.append((rcv_time - pub_time).total_seconds() * 1000)

    #     total_sent += 1
    #     time.sleep(1/fps) # commented because it its impacting the benchmark.

    # print(diffs)
