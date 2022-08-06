#include "GdiPlusInitializer.h"

GdiPlusInitializer::GdiPlusInitializer()
{
	GdiplusStartup(&_token, &_startupInput, nullptr);
}

GdiPlusInitializer::~GdiPlusInitializer()
{
	GdiplusShutdown(_token);
}
