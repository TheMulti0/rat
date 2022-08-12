#include "Screenshotter.h"

#include "Screenshot.h"

SharedSpan Screenshotter::ScreenshotScreen()
{
	return ScreenshotWindow(HWND_DESKTOP);
}

SharedSpan Screenshotter::ScreenshotWindow(HWND window)
{
	return Screenshot(window).Save();
}
