using System.Runtime.InteropServices;

namespace Server.Interop;

public class RatManager : IRatManager
{
    private IntPtr _manager;

    [DllImport(Dependencies.ServerDll)]
    private static extern IntPtr CreateRatManager(int port);

    [DllImport(Dependencies.ServerDll)]
    private static extern int GetClientCount(IntPtr manager);

    [DllImport(Dependencies.ServerDll)]
    private static extern void GetClients(
        IntPtr manager, 
        [In, Out, MarshalAs(UnmanagedType.LPArray)] ClientInfo[] infos);

    [DllImport(Dependencies.ServerDll)]
    private static extern int Send(
        IntPtr manager,
        int client,
        MessageType type,
        byte[] content,
        int contentLength);

    [DllImport(Dependencies.ServerDll)]
    private static extern void Join(IntPtr manager);

    [DllImport(Dependencies.ServerDll)]
    private static extern int DisposeRatManager(IntPtr manager);

    public RatManager(int port)
    {
        _manager = CreateRatManager(port);
    }

    public int GetClientCount()
    {
        return GetClientCount(_manager);
    }

    public unsafe IEnumerable<ClientInfo> GetClients()
    {
       // IntPtr[] array = IntPtr.Zero;

        int length = GetClientCount();
        ClientInfo[] infos = new ClientInfo[length];
        GetClients(_manager, infos);
        //IntPtr[] newArr = new IntPtr[length];
        //Marshal.Copy(array, newArr, 0, length);
        ////Marshal.FreeHGlobal(array);

        //var arr = array.Select(Marshal.PtrToStructure<ClientInfo>)!.ToArray();

        //ClientInfo[] arr = new ClientInfo[length];
        //for (int i = 0; i < length; i++)
        //{
        //    arr[i] = (ClientInfo)Marshal.PtrToStructure(array, typeof(ClientInfo))!;
        //    array += Marshal.SizeOf(typeof(ClientInfo));
        //}

        return infos;
    }

    public int Send(int client, MessageType type, IEnumerable<byte> content)
    {
        var array = content.ToArray();

        return Send(_manager, client, type, array, array.Length);
    }

    public void Join()
    {
        Join(_manager);
    }

    public void Dispose()
    {
        Dispose(false);
    }

    ~RatManager()
    {
        Dispose(true);
    }

    private void Dispose(bool calledByGc)
    {
        if (_manager != IntPtr.Zero)
        {
            DisposeRatManager(_manager);

            _manager = IntPtr.Zero;
        }

        if (calledByGc)
        {
            // No need to call the finalizer since we've now cleaned
            // up the unmanaged memory
            GC.SuppressFinalize(this);
        }
    }
}