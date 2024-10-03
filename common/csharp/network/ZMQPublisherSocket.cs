namespace network;

using System.Text;
using NetMQ;
using NetMQ.Sockets;

/// <summary>
/// Represents a publisher socket for ZeroMQ communication.
/// </summary>
public class ZMQPublisherSocket : IDisposable
{
    public PublisherSocket Socket { get; set; }

    /// <summary>
    /// Initializes a new instance of the <see cref="ZMQPublisherSocket"/> class.
    /// </summary>
    public ZMQPublisherSocket()
    {
        Socket = new PublisherSocket();
    }

    /// <summary>
    /// Sends <see cref="ZMQDatagram"/> to topic via PublisherSocket.
    /// </summary>
    public void Send(ZMQDatagram datagram)
    {
        Socket
        .SendMoreFrame(Encoding.UTF8.GetBytes(datagram.Topic))
        .SendFrame(Encoding.UTF8.GetBytes(datagram.Message));
    }

    /// <summary>
    /// Dispose method implementation closing the PublisherSocket.
    /// </summary>
    public void Dispose()
    {
        Socket?.Close();
    }
}
