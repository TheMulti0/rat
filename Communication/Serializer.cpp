#include "Serializer.h"

Serializer::Serializer(const int size):
	_index(0),
	_size(size),
	_data(new char[size])
{
}

void Serializer::Add(SharedSpan item)
{
	Add(item.Data(), item.Size());
}

void Serializer::Add(const char* item, const int size)
{
	std::copy_n(item, size, _data.get() + _index);
	_index += size;
}

SharedSpan Serializer::Data()
{
	auto span = SharedSpan(_size);

	std::copy_n(_data.release(), _size, span.Data());

	return span;
}
