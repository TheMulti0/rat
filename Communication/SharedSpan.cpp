#include "SharedSpan.h"

#include "Trace.h"

SharedSpan::SharedSpan(): _size(0)
{
}

SharedSpan::SharedSpan(const std::string& str):
	_size(str.size()),
	_buffer(std::shared_ptr<char>(new char[_size]))
{
	std::ranges::copy(str, _buffer.get());
}

SharedSpan::SharedSpan(const size_t size):
	_size(size),
	_buffer(std::shared_ptr<char>(new char[_size]))
{
}

size_t SharedSpan::Size() const
{
	return _size;
}

char* SharedSpan::Data()
{
	auto str = _buffer.get();
	return str;
}

std::string SharedSpan::String() const
{
	return std::string(_buffer.get(), _size);

	//auto string = std::unique_ptr<char>(new char[_size]);

	//std::copy_n(_buffer.get(), _size, string.get());

	//return { string.release(), _size };
}
