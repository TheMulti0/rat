#pragma once
#include <string>

__declspec(dllexport)
std::string ToString(const std::wstring& s);

__declspec(dllexport)
std::wstring ToWString(const std::string& s);