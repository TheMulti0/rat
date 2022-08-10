#pragma once

#include "GdiPlusInitializer.h"
#include "SharedSpan.h"

class Screenshot
{
public:
	SharedSpan ScreenshotScreen();

	static SharedSpan ScreenshotWindow(HWND window);

private:
	GdiPlusInitializer _initializer;
};

