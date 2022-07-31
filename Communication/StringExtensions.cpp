#include "StringExtensions.h"

#include <windows.h>

std::string ToString(const std::wstring& s)
{
	const auto size = s.size();

	const int len = WideCharToMultiByte(
		CP_ACP,
		0,
		s.c_str(),
		size,
		nullptr,
		0,
		nullptr,
		nullptr);

	std::string r(len, L'\0');

	WideCharToMultiByte(
		CP_ACP,
		0,
		s.c_str(),
		size,
		&r[0],
		len,
		nullptr,
		nullptr);

	return r;
}

std::wstring ToWString(const std::string& s)
{
	const auto size = s.size();

	const int len = MultiByteToWideChar(
		CP_ACP,
		0,
		s.c_str(),
		size,
		nullptr,
		0);

	std::wstring r(len, L'\0');

	MultiByteToWideChar(
		CP_ACP,
		0,
		s.c_str(),
		size,
		&r[0],
		len);

	return r;
}