using System.Runtime.InteropServices;

namespace Server.Interop;

public class MessageSender : IMessageSender
{
    private readonly IntPtr _sender;

    public MessageSender(IntPtr sender)
    {
        _sender = sender;
    }

    [DllImport(Dependencies.CommunicationDll)]
    private static extern int Send(
        IntPtr sender, 
        MessageType type, 
        byte[] content, 
        int contentLength);

    public int Send(MessageType type, IEnumerable<byte> content)
    {
        var array = content.ToArray();

        return Send(_sender, type, array, array.Length);
    }
}