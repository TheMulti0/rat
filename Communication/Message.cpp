#include "Message.h"
#include "Serializer.h"

Message Message::Deserialize(SharedSpan buffer)
{
	auto type = *reinterpret_cast<const MessageType*>(buffer.Data());

	const auto contentSize = buffer.Size() - sizeof type;

	auto content = SharedSpan(contentSize);

	std::copy_n(buffer.Data() + sizeof type, contentSize, content.Data());

	return
	{
		type,
		content
	};
}

SharedSpan Message::Serialize()
{
	const auto length = _content.Size();

	constexpr auto typeSize = sizeof _type;
	const int actualMessageSize = typeSize + length;

	Serializer s(actualMessageSize);

	s.Add(reinterpret_cast<const char*>(&_type), typeSize);
	s.Add(_content);

	return s.Data();
}

Message::Message(const MessageType type, SharedSpan content) :
	_type(type),
	_content(std::move(content))
{
}

MessageType Message::GetType() const
{
	return _type;
}

SharedSpan Message::GetContent() const
{
	return _content;
}
