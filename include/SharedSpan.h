#pragma once

#include <memory>
#include <string>

class SharedSpan
{
public:
	SharedSpan();

	explicit SharedSpan(const std::string& str);

	explicit SharedSpan(int size);

	[[nodiscard]] char* begin();
	[[nodiscard]] char* end();

	[[nodiscard]] int size() const;

	[[nodiscard]] std::string toString() const;

private:
	int _size;
	std::shared_ptr<char> _buffer;
};

inline SharedSpan::SharedSpan(): _size(0)
{
}

inline SharedSpan::SharedSpan(const std::string& str):
	_size(static_cast<int>(str.size())),
	_buffer(std::shared_ptr<char>(new char[_size]))
{
	std::ranges::copy(str, _buffer.get());
}

inline SharedSpan::SharedSpan(const int size):
	_size(size),
	_buffer(std::shared_ptr<char>(new char[_size]))
{
}

inline int SharedSpan::size() const
{
	return _size;
}

inline std::string SharedSpan::toString() const
{
	return std::string(_buffer.get(), _size);
}

inline char* SharedSpan::begin()
{
	return _buffer.get();
}

inline char* SharedSpan::end()
{
	return begin() + _size;
}

