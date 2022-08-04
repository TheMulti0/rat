#pragma once

#include <memory>

class Serializer
{
public:
	explicit Serializer(const size_t size) :
		_index(0),
		_size(size),
		_data(new char[size])
	{
	}

	void Add(SharedSpan item)
	{
		Add(item.Data(), item.Size());
	}

	void Add(const char* item, const size_t size)
	{
		std::copy_n(item, size, _data.get() + _index);
		_index += size;
	}

	SharedSpan Data()
	{
		auto span = SharedSpan(_size);

		std::copy_n(_data.release(), _size, span.Data());

		return span;
	}

private:
	size_t _index;
	size_t _size;
	std::unique_ptr<char> _data;
};
