#pragma once

#include <memory>
#include <string>

class SharedSpan
{
public:
	SharedSpan();

	explicit SharedSpan(const std::string& str);

	explicit SharedSpan(const size_t size);

	[[nodiscard]] size_t Size() const;

	[[nodiscard]] char* Data();

	[[nodiscard]] std::string String() const;

private:
	size_t _size;
	std::shared_ptr<char> _buffer;
};

inline SharedSpan::SharedSpan(): _size(0)
{
}

inline SharedSpan::SharedSpan(const std::string& str):
	_size(str.size()),
	_buffer(std::shared_ptr<char>(new char[_size]))
{
	std::ranges::copy(str, _buffer.get());
}

inline SharedSpan::SharedSpan(const size_t size):
	_size(size),
	_buffer(std::shared_ptr<char>(new char[_size]))
{
}

inline size_t SharedSpan::Size() const
{
	return _size;
}

inline char* SharedSpan::Data()
{
	return _buffer.get();
}

inline std::string SharedSpan::String() const
{
	return std::basic_string<char>(_buffer.get(), _size);
}

