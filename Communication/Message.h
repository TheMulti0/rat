#pragma once

#include <span>

#include "MessageType.h"

class Message
{
public:
	static Message Deserialize(std::span<char> buffer);
	std::span<char> Serialize() const;

	Message(MessageType type, std::span<char> content);

	MessageType GetType() const;
	std::span<char> GetContent() const;

private:
	MessageType _type;
	std::span<char> _content;
};