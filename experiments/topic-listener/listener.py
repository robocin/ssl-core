import sys
import zmq


def new_zmq_subscriber(topic="detection"):
    context = zmq.Context()

    socket = context.socket(zmq.SUB)
    socket.connect("ipc:///tmp/.ssl-core/perception.ipc")
    socket.setsockopt_string(zmq.SUBSCRIBE, topic)

    print(f"Subscribed topic: {topic}")

    return socket


def listen(socket: zmq.Socket):
    while True:
        message = socket.recv_string()
        print(message)


if __name__ == "__main__":

    subscriber = new_zmq_subscriber()

    listen(subscriber)
