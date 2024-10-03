namespace network;

/// <summary>
/// Represents a datagram message for ZeroMQ communication.
/// </summary>
public class ZMQDatagram
{
    public string Message { get; set; }
    public string Topic { get; set; }

    /// <summary>
    /// Initializes a new instance of the <see cref="ZMQDatagram"/> class with the specified message.
    /// </summary>
    /// <param name="message">The string message content.</param>
    /// <param name="topic">The string referencing the message topic.</param>
    public ZMQDatagram(string message, string topic)
    {
        Message = message;
        Topic = topic;
    }
}
