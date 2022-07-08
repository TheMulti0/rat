#pragma once

enum class MessageType : char
{
	Chat = 0,
	Ping = 1,
	CreateProcessS = 2,
	StartReverseShell = 3,
	ReverseShellMessage = 4,
	StopReverseShell = 5
};