#pragma once

#include <memory>

class Serializer
{
public:
	explicit Serializer(const int size) :
		_index(0),
		_size(size),
		_data(new char[size])
	{
	}

	void Add(SharedSpan item)
	{
		Add(item.Data(), item.Size());
	}

	void Add(const char* item, const int size)
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
	int _index;
	int _size;
	std::unique_ptr<char> _data;
};
