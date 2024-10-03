namespace network;

using NetMQ;
using NetMQ.Sockets;

/// <summary>
/// Represents a publisher socket for ZeroMQ communication.
/// </summary>
public class ZMQSubscriberSocket : IDisposable
{
    public SubscriberSocket Socket { get; set; }

    /// <summary>
    /// Initializes a new instance of the <see cref="ZMQSubscriberSocket"/> class.
    /// </summary>
    public ZMQSubscriberSocket(string address, string topics)
    {
        Socket = new SubscriberSocket(address);
        Socket.Subscribe(topics);
    }

    /// <summary>
    /// Receives <see cref="ZMQDatagram"/> to topic from SubscriberSocket.
    /// </summary>
    public ZMQDatagram Receive()
    {
        string messageTopicReceived = Socket.ReceiveFrameString();
        string messageReceived = Socket.ReceiveFrameString();

        return new ZMQDatagram(messageTopicReceived, messageReceived);
    }

    /// <summary>
    /// Dispose method implementation closing the SubscriberSocket.
    /// </summary>
    public void Dispose()
    {
        Socket?.Close();
    }
}
