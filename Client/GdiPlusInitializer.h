#pragma once

#include <Windows.h>
#include <gdiplus.h>

using namespace Gdiplus;

class GdiPlusInitializer
{
public:
	GdiPlusInitializer();
	~GdiPlusInitializer();

private:
	GdiplusStartupInput _startupInput;
	ULONG_PTR _token;
};

