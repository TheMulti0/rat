#pragma once

#include <map>
#include <string>

#include <Windows.h>

class PressedKey
{
public:
	PressedKey(
		int keyStroke,
		HKL layout
	);

	[[nodiscard]] std::string ToString() const;

private:
	static bool IsKeyLowercase();

	char GetLetter() const;

	static std::map<int, std::string> _keyNames;

	int _keyStroke;
	HKL _layout;
};
