#pragma once

#include <memory>
#include <string>

#ifdef MAKEDLL
#  define EXPORT __declspec(dllexport)
#else
#  define EXPORT __declspec(dllimport)
#endif

class SharedSpan
{
public:
	EXPORT SharedSpan();

	EXPORT explicit SharedSpan(
		const std::string& str
	);

	EXPORT SharedSpan(
		size_t size
	);

	EXPORT [[nodiscard]] size_t Size() const;
	EXPORT [[nodiscard]] char* Data();
	EXPORT [[nodiscard]] std::string String() const;

private:
	size_t _size;
	std::shared_ptr<char> _buffer;
};

