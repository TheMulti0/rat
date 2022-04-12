#include "Message.h"
#include "Serializer.h"

Message Message::Deserialize(std::span<char> buffer)
{
	auto type = *reinterpret_cast<const MessageType*>(buffer.data());

	auto content = std::span(
		buffer.data() + sizeof type,
		buffer.size() - sizeof type);

	return
	{
		type,
		content
	};
}

std::span<char> Message::Serialize() const
{
	const auto length = _content.size();
	const char* cStr = _content.data();

	constexpr auto typeSize = sizeof _type;
	const int actualMessageSize = typeSize + length;

	Serializer s(sizeof actualMessageSize + actualMessageSize);

	s.Add(reinterpret_cast<const char*>(&actualMessageSize), sizeof actualMessageSize);
	s.Add(reinterpret_cast<const char*>(&_type), typeSize);
	s.Add(cStr, length);

	return s.Data();
}

Message::Message(const MessageType type, std::span<char> content) :
	_type(type),
	_content(content)
{
}

MessageType Message::GetType() const
{
	return _type;
}

std::span<char> Message::GetContent() const
{
	return _content;
}
