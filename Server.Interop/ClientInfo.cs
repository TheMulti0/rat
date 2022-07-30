using System.Runtime.InteropServices;

namespace Server.Interop;

[StructLayout(LayoutKind.Sequential)]
public struct ClientInfo
{
    [field: MarshalAs(UnmanagedType.ByValTStr, SizeConst = 16)]
    public string Address { get; set; }
}