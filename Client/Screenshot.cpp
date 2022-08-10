#include "Screenshot.h"

#include <Windows.h>
#include <gdiplus.h>
#include <wil/resource.h>

#include "StringExtensions.h"

SharedSpan Screenshot::ScreenshotScreen()
{
    return ScreenshotWindow(HWND_DESKTOP);
}

SharedSpan Screenshot::ScreenshotWindow(const HWND window)
{
	auto hdc = wil::unique_hdc_window(
		GetDC(window));

	const auto memdc = wil::unique_hdc(
		CreateCompatibleDC(hdc.get()));

	const int height = GetSystemMetrics(SM_CYSCREEN);
	const int width = GetSystemMetrics(SM_CXSCREEN);

	auto hBitmap = wil::unique_hbitmap(
		CreateCompatibleBitmap(hdc.get(), width, height));

	SelectObject(
		memdc.get(),
		hBitmap.get());

	BitBlt(
		memdc.get(),
		0, 
		0,
		width, 
		height, 
		hdc.get(),
		0,
		0, 
		SRCCOPY);

	auto m_image = Gdiplus::Bitmap(hBitmap.get(), nullptr);

	CLSID pngEncoder = { 0x557cf406, 0x1a04, 0x11d3, {0x9a, 0x73, 0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e} };

	IStream* stream;
	CreateStreamOnHGlobal(nullptr, true, &stream);

	m_image.Save(stream, &pngEncoder);

	ULARGE_INTEGER imageSize;
	LARGE_INTEGER offset;
	offset.QuadPart = 0;

	stream->Seek(offset, STREAM_SEEK_END, &imageSize);
	stream->Seek(offset, STREAM_SEEK_SET, nullptr);

	auto imageSpan = SharedSpan(imageSize.QuadPart);

	ULONG ulBytesRead;
	stream->Read(imageSpan.Data(), imageSize.QuadPart, &ulBytesRead);

	stream->Release();
	//m_image.Save(ToWString("myjpg.jpg").c_str(), &pngEncoder, nullptr);
	

	return imageSpan;
}
