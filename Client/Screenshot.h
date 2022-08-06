#pragma once

#include "GdiPlusInitializer.h"
#include "SharedSpan.h"

class Screenshot
{
public:
	SharedSpan ScreenshotScreen();

private:
	GdiPlusInitializer _initializer;
};

