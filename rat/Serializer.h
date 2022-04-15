#pragma once

#include <span>

class Serializer
{
public:
	explicit Serializer(const size_t size) :
		_index(0),
		_size(size),
		_data(new char[size])
	{
	}

	void Add(const std::span<char> item)
	{
		Add(item.data(), item.size());
	}

	void Add(const char* item, const size_t size)
	{
		std::copy_n(item, size, _data + _index);
		_index += size;
	}

	std::span<char> Data()
	{
		return { _data, _size };
	}

private:
	size_t _index;
	size_t _size;
	char* _data;
};
