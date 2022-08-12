#pragma once

#include "GdiPlusInitializer.h"
#include "SharedSpan.h"

class Screenshotter
{
public:
	SharedSpan ScreenshotScreen();
	SharedSpan ScreenshotWindow(HWND window);

private:
	GdiPlusInitializer _initializer;
};

