#pragma once

#include <memory>

#include "SharedSpan.h"

class Serializer
{
public:
	explicit Serializer(int size);

	void Add(SharedSpan item);

	void Add(const char* item, const int size);

	SharedSpan Data();

private:
	int _index;
	int _size;
	std::unique_ptr<char> _data;
};
