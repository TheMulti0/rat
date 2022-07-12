namespace Server.Interop;

public interface IRatManager : IDisposable
{
    int GetClientCount();

    int Send(int client, MessageType type, IEnumerable<byte> content);

    void Join();
}