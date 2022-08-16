#include "Screenshot.h"

#include <Windows.h>
#include <gdiplus.h>

Screenshot::Screenshot(const HWND window) :
	_window(window),
	_screenDc(GetDC(HWND_DESKTOP)),
	_memoryDc(CreateCompatibleDC(_screenDc.get())),
	_rect(CreateRect()),
	_width(_rect.right - _rect.left),
	_height(_rect.bottom - _rect.top),
	_bitmapHandle(CreateCompatibleBitmap(_screenDc.get(), _width, _height)),
	_stream(CreateMemoryStream()),
	_encoder(GetEncoder())
{
	Capture();
}

Screenshot::~Screenshot()
{
	_stream->Release();
}

SharedSpan Screenshot::Save()
{
	_bitmap->Save(_stream, &_encoder);

	const auto imageSize = GetImageSize();

	const auto size = static_cast<ULONG>(imageSize.QuadPart);

	auto imageSpan = SharedSpan(static_cast<int>(size));

	ULONG bytesRead = 0;
	while (bytesRead < size)
	{
		ULONG read = 0;

		_stream->Read(
			imageSpan.begin(),
			size - bytesRead,
			&read);

		bytesRead += read;
	}
	

	return imageSpan;
}

IStream* Screenshot::CreateMemoryStream()
{
	IStream* stream;

	HRESULT streamOnHGlobal = CreateStreamOnHGlobal(nullptr, true, &stream);

	return stream;
}

CLSID Screenshot::GetEncoder()
{
	CLSID pngEncoder = { 0x557cf406, 0x1a04, 0x11d3, {0x9a, 0x73, 0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e} };

	return pngEncoder;

	//const auto format = std::wstring(L"image/png");

	//UINT encodersCount = 0;
	//UINT totalArraySize = 0;
	//GetImageEncodersSize(&encodersCount, &totalArraySize);

	//// The codecs are stored in an array because calling their destructors
	//// causes a crash
	//auto codecs = new ImageCodecInfo[encodersCount];
	//GetImageEncoders(encodersCount, totalArraySize, codecs);

	//for (UINT i = 0; i < encodersCount; ++i)
	//{
	//	if (codecs[i].MimeType == format)
	//	{
	//		return codecs[i].Clsid;
	//	}
	//}
}

RECT Screenshot::CreateRect()
{
	RECT desktopRect;
	GetWindowRect(GetDesktopWindow(), &desktopRect);

	RECT windowRect;
	GetWindowRect(_window, &windowRect);

	constexpr int offset = 100;

	RECT rect;

	rect.left = max(windowRect.left - offset, desktopRect.left);
	rect.right = max(windowRect.right - offset, desktopRect.right);
	rect.bottom = max(windowRect.bottom - offset, desktopRect.bottom);
	rect.top = max(windowRect.top - offset, desktopRect.top);

	return rect;
}

void Screenshot::Capture()
{
	SelectObject(_memoryDc.get(), _bitmapHandle.get());

	BOOL bitBlt = BitBlt(_memoryDc.get(), 0, 0, _width, _height, _screenDc.get(), _rect.left, _rect.top, SRCCOPY);

	_bitmap = std::make_unique<Bitmap>(_bitmapHandle.get(), nullptr);
}

ULARGE_INTEGER Screenshot::GetImageSize()
{
	ULARGE_INTEGER imageSize;

	LARGE_INTEGER offset;
	offset.QuadPart = 0;

	_stream->Seek(offset, STREAM_SEEK_END, &imageSize);

	_stream->Seek(offset, STREAM_SEEK_SET, nullptr);

	return imageSize;
}
