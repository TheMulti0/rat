#pragma once

#include <wil/resource.h>

#include "GdiPlusInitializer.h"
#include "SharedSpan.h"

class Screenshot
{
public:
	explicit Screenshot(HWND window);

	~Screenshot();

	SharedSpan Save();

private:
	RECT CreateRect();
	IStream* CreateMemoryStream();
	CLSID GetEncoder();

	void Capture();
	ULARGE_INTEGER GetImageSize();

	HWND _window;
	wil::unique_hdc_window _screenDc;
	wil::unique_hdc _memoryDc;
	RECT _rect;
	int _width;
	int _height;
	wil::unique_hbitmap _bitmapHandle;
	IStream* _stream;
	CLSID _encoder;

	std::unique_ptr<Bitmap> _bitmap;
};

