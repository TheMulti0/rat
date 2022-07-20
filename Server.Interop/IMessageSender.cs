namespace Server.Interop;

public interface IMessageSender
{
    int Send(MessageType type, IEnumerable<byte> content);
}