using System.Runtime.InteropServices;

namespace Server.Interop;

public class Connection : IConnection
{
    private readonly IntPtr _connection;

    public Connection(IntPtr connection)
    {
        _connection = connection;
    }

    [DllImport(Dependencies.CommunicationDll)]
    [return: MarshalAs(UnmanagedType.LPStr)]
    private static extern string GetAddress(IntPtr connection);

    public string GetAddress()
    {
        return GetAddress(_connection);
    }
}