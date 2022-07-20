using System.Runtime.InteropServices;

namespace Server.Interop;

//TODO add dispose
public class ClientPipe : IClientPipe
{
    private readonly IntPtr _pipe;

    public ClientPipe(IntPtr pipe)
    {
        _pipe = pipe;
    }

    [DllImport(Dependencies.CommunicationDll)]
    private static extern IntPtr GetConnection(IntPtr pipe);

    [DllImport(Dependencies.CommunicationDll)]
    private static extern IntPtr GetSender(IntPtr pipe);

    public IConnection GetConnection()
    {
        var ptr = GetConnection(_pipe);

        return new Connection(ptr);
    }

    public IMessageSender GetSender()
    {
        var ptr = GetSender(_pipe);

        return new MessageSender(ptr);
    }
}