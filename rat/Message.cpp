#include <memory>

#include "Message.h"
#include "Serializer.h"

Message Message::Deserialize(std::span<char> buffer)
{
	auto type = *reinterpret_cast<const MessageType*>(buffer.data());
	if (type != MessageType::Chat)
	{
		return {MessageType::Chat, std::string("")};
	}

	auto message = std::string(
		buffer.data() + sizeof type,
		buffer.size() - sizeof type);

	return
	{
		type,
		message
	};
}

std::span<char> Message::Serialize() const
{
	const int length = _message.length();
	const char* cStr = _message.c_str();

	constexpr auto typeSize = sizeof _type;
	const int actualMessageSize = typeSize + length;

	Serializer s(sizeof actualMessageSize + actualMessageSize);

	s.Add(reinterpret_cast<const char*>(&actualMessageSize), sizeof actualMessageSize);
	s.Add(reinterpret_cast<const char*>(&_type), typeSize);
	s.Add(cStr, length);

	return s.Data();
}

Message::Message(const MessageType type, std::string message) : _type(type), _message(std::move(message))
{
}

MessageType Message::GetType() const
{
	return _type;
}

std::string Message::GetMessageString() const
{
	return _message;
}
