#include "PressedKey.h"

#include <sstream>

std::map<int, std::string> _keyNames{
	{VK_BACK, "[BACKSPACE]"},
	{VK_RETURN, "\n"},
	{VK_SPACE, "_"},
	{VK_TAB, "[TAB]"},
	{VK_SHIFT, "[SHIFT]"},
	{VK_LSHIFT, "[LSHIFT]"},
	{VK_RSHIFT, "[RSHIFT]"},
	{VK_CONTROL, "[CONTROL]"},
	{VK_LCONTROL, "[LCONTROL]"},
	{VK_RCONTROL, "[RCONTROL]"},
	{VK_MENU, "[ALT]"},
	{VK_LWIN, "[LWIN]"},
	{VK_RWIN, "[RWIN]"},
	{VK_ESCAPE, "[ESCAPE]"},
	{VK_END, "[END]"},
	{VK_HOME, "[HOME]"},
	{VK_LEFT, "[LEFT]"},
	{VK_RIGHT, "[RIGHT]"},
	{VK_UP, "[UP]"},
	{VK_DOWN, "[DOWN]"},
	{VK_PRIOR, "[PG_UP]"},
	{VK_NEXT, "[PG_DOWN]"},
	{VK_OEM_PERIOD, "."},
	{VK_DECIMAL, "."},
	{VK_OEM_PLUS, "+"},
	{VK_OEM_MINUS, "-"},
	{VK_ADD, "+"},
	{VK_SUBTRACT, "-"},
	{VK_CAPITAL, "[CAPSLOCK]"},
};

PressedKey::PressedKey(
	const int keyStroke, 
	const HKL layout
):
	_keyStroke(keyStroke),
	_layout(layout)
{
}

std::string PressedKey::ToString() const
{
	std::stringstream output;

	output << "[" << _keyStroke << "] ";

	_keyNames.contains(_keyStroke)
		? output << _keyNames.at(_keyStroke)
		: output << GetLetter();

	return output.str();
}

bool PressedKey::IsKeyLowercase()
{
	// check caps lock
	bool lowercase = (GetKeyState(VK_CAPITAL) & 0x0001) != 0;

	// check shift key
	if ((GetKeyState(VK_SHIFT) & 0x1000) != 0 ||
		(GetKeyState(VK_LSHIFT) & 0x1000) != 0 ||
		(GetKeyState(VK_RSHIFT) & 0x1000) != 0)
	{
		lowercase = !lowercase;
	}

	return lowercase;
}

char PressedKey::GetLetter() const
{
	const auto lowercase = IsKeyLowercase();

	const char key = MapVirtualKeyExA(_keyStroke, MAPVK_VK_TO_CHAR, _layout);

	return lowercase
       ? key
       : tolower(key);
}
