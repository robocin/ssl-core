import sys
import zmq


def new_zmq_subscriber(topic=""):
    context = zmq.Context()

    socket = context.socket(zmq.SUB)
    socket.connect("ipc:///tmp/topic_listener")
    socket.setsockopt_string(zmq.SUBSCRIBE, topic)

    print(f"Subscribed topic: {topic}")

    return socket


def listen(socket: zmq.Socket):
    while True:
        message = socket.recv_string()
        print(message)


if __name__ == "__main__":
    topic = "no_topic"
    try:
        topic = sys.argv[1]
    except:
        raise ValueError("No topic given.")

    subscriber = new_zmq_subscriber(topic)

    listen(subscriber)
