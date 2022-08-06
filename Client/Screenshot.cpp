#include "Screenshot.h"

#include <Windows.h>
#include <gdiplus.h>
#include <wil/resource.h>

#include "StringExtensions.h"


SharedSpan Screenshot::ScreenshotScreen()
{
    auto hdc = wil::unique_hdc_window(
        GetDC(HWND_DESKTOP));

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

    m_image.Save(ToWString("myjpg.jpg").c_str(), &pngEncoder, nullptr);

    return SharedSpan(0);
}
