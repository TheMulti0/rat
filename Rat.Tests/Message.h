#pragma once

#include <span>

#include "MessageType.h"

class Message
{
public:
	Message(MessageType type, std::span<char> content);

	[[nodiscard]] MessageType GetType() const;

	[[nodiscard]] std::span<char> GetContent() const;

private:
	MessageType _type;
	std::span<char> _content;
};
