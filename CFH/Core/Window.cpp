#include "Window.h"
#include "EngineContext.h"

#include <Windows.h>

namespace CFH
{
	Window::Window(EngineContext* context) :
		hWnd_(nullptr),
		hInstance_(nullptr),
		title_(nullptr),
		fullscreen_(false),
		x_(0),
		y_(0),
		width_(0),
		height_(0)
	{
	}
	Window::~Window()
	{
		hWnd_ = nullptr;
		hInstance_ = nullptr;
	}

	bool Window::Initialize(LPWSTR title)
	{
		fullscreen_ = true;
		title_ = title;

		return InitializeWindow();
	}
	bool Window::Initialize(int width, int height, LPWSTR title)
	{
		width_ = width;
		height_ = height;
		fullscreen_ = false;
		title_ = title;

		return InitializeWindow();
	}
	bool Window::InitializeWindow()
	{
		hInstance_ = GetModuleHandle(nullptr);

		// Setup and register a class in Windows
		WNDCLASSEX wc;
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wc.lpfnWndProc = &Window::WndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hInstance_;
		wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
		wc.hIconSm = wc.hIcon;
		wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wc.lpszMenuName = nullptr;
		wc.lpszClassName = title_;
		wc.cbSize = sizeof(WNDCLASSEX);
		RegisterClassEx(&wc);

		if (fullscreen_)
		{
			// If fullscreen we use the resolution of the primary monitor.
			width_ = GetSystemMetrics(SM_CXSCREEN);
			height_ = GetSystemMetrics(SM_CYSCREEN);

			DEVMODE dmScreenSettings;
			memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
			dmScreenSettings.dmSize = sizeof(dmScreenSettings);
			dmScreenSettings.dmPelsWidth = width_;
			dmScreenSettings.dmPelsHeight = height_;
			dmScreenSettings.dmBitsPerPel = 32;
			dmScreenSettings.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;

			ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
		}
		else
		{
			x_ = (GetSystemMetrics(SM_CXSCREEN) - width_) / 2;
			y_ = (GetSystemMetrics(SM_CYSCREEN) - height_) / 2;
		}

		// Create the window in Windows
		hWnd_ = CreateWindowEx(
			WS_EX_APPWINDOW,								// dwExStyle
			title_,											// lpClassName
			title_,											// lpWindowName
			WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_BORDER,	// dwStyle
			x_,												// x
			y_,												// y
			width_,											// nWidth
			height_,										// nHeight
			nullptr,										// hWndParent
			nullptr,										// hMenu
			hInstance_,										// hInstance
			nullptr);										// lParam
		if (!hWnd_)
			return false;

		return true;
	}

	bool Window::Show()
	{
		bool result = ShowWindow(hWnd_, SW_SHOW) != 0 ? true : false;
		if (result)
		{
			SetForegroundWindow(hWnd_);
			SetFocus(hWnd_);
			ShowCursor(false);
		}
		return result;
	}
	bool Window::Hide()
	{
		ShowCursor(true);
		return ShowWindow(hWnd_, SW_HIDE) != 0 ? true : false;
	}

	HWND Window::GetHandle()
	{
		return hWnd_;
	}
	HINSTANCE Window::GetInstance()
	{
		return hInstance_;
	}

	int Window::GetX()
	{
		return x_;
	}
	int Window::GetY()
	{
		return y_;
	}
	int Window::GetWidth()
	{
		return width_;
	}
	int Window::GetHeight()
	{
		return height_;
	}

	LPWSTR Window::GetTitle()
	{
		return title_;
	}
	bool Window::IsFullscreen()
	{
		return fullscreen_;
	}

	LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_DESTROY:
		case WM_CLOSE:
			PostQuitMessage(0);
			return 0;
		case WM_KEYDOWN:
			if (wParam == VK_ESCAPE)
				PostQuitMessage(0);
			return 0;
		}
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}
