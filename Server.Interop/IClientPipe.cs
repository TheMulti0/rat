namespace Server.Interop;

public interface IClientPipe
{
    IConnection GetConnection();

    IMessageSender GetSender();
}