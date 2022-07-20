namespace Server.Interop;

public interface IRatManager : IDisposable
{
    int GetClientCount();

    IEnumerable<IClientPipe> GetClients();

    int Send(int client, MessageType type, IEnumerable<byte> content);

    void Join();
}