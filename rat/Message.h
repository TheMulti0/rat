#pragma once

#include <span>
#include <string>

#include "MessageType.h"

class Message
{
public:
	static Message Deserialize(std::span<char> buffer);
	std::span<char> Serialize() const;

	Message(MessageType type, std::string message);

	MessageType GetType() const;
	std::string GetMessageString() const;

private:
	MessageType _type;
	std::string _message;
};