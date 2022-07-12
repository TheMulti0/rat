﻿using System.Runtime.InteropServices;

namespace Server.Interop;

public class RatManager : IRatManager
{
    private const string ServerDll = "Server.dll";

    private IntPtr _manager;

    [DllImport(ServerDll)]
    private static extern IntPtr CreateRatManager(int port);

    [DllImport(ServerDll)]
    private static extern int GetClientCount(IntPtr manager);

    [DllImport(ServerDll)]
    private static extern int Send(
        IntPtr manager,
        int client,
        MessageType type,
        byte[] content,
        int contentLength);

    [DllImport(ServerDll)]
    private static extern void Join(IntPtr manager);

    [DllImport(ServerDll)]
    private static extern int DisposeRatManager(IntPtr manager);

    public RatManager(int port)
    {
        _manager = CreateRatManager(port);
    }

    public int GetClientCount()
    {
        return GetClientCount(_manager);
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