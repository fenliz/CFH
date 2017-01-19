#include "Window.h"
#include "Logging\Log.h"
#include "EngineContext.h"
#include "Messaging\Messages.h"

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
		SUBSCRIBE_TO_MESSAGE(WindowMoveMessage, this, [this](const WindowMoveMessage& message) { OnWindowMove(message); });
		SUBSCRIBE_TO_MESSAGE(WindowResizeMessage, this, [this](const WindowResizeMessage& message) { OnWindowResize(message); });
		SUBSCRIBE_TO_MESSAGE(FrameBeginMessage, this, [this](FrameBeginMessage message) { int i = 0; });
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

		// Setup and register our window-class in Windows
		WNDCLASSEX wc;
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.lpszClassName = title_;
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wc.lpfnWndProc = &Window::WndProc;
		wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
		wc.hIconSm = wc.hIcon;
		wc.hInstance = hInstance_;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.lpszMenuName = nullptr;
		if (!RegisterClassEx(&wc))
			return false;

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

			if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
				return false;
		}
		else
		{
			x_ = (GetSystemMetrics(SM_CXSCREEN) - width_) / 2;
			y_ = (GetSystemMetrics(SM_CYSCREEN) - height_) / 2;
		}

		// Create an instance of the window-class we just created.
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
		// Try to show the window but abort if it was already visible.
		if (ShowWindow(hWnd_, SW_SHOW) != 0)
			return false;

		SetForegroundWindow(hWnd_);
		SetFocus(hWnd_);
		ShowCursor(false);
		return true;
	}
	bool Window::Hide()
	{
		// Try to hide the window but abort if it was already hidden.
		if (ShowWindow(hWnd_, SW_HIDE) == 0)
			return false;

		ShowCursor(true);
		return true;
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

	// The messagepump registered when creating the window.
	LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_DESTROY:
		case WM_CLOSE:
			SEND_DEFAULT_MESSAGE(WindowCloseMessage);
			return 0;
		case WM_SIZE:
			SEND_MESSAGE(WindowResizeMessage, 
				WindowResizeMessage((int)(short)LOWORD(lParam), 
								    (int)(short)HIWORD(lParam)));
			break;
		case WM_MOVE:
			SEND_MESSAGE(WindowMoveMessage,
				WindowMoveMessage((int)(short)LOWORD(lParam), 
								  (int)(short)HIWORD(lParam)));
		case WM_KEYDOWN:
			if (wParam == VK_ESCAPE)
				SEND_DEFAULT_MESSAGE(WindowCloseMessage);
			break;
		}
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	void Window::OnWindowMove(const WindowMoveMessage& message)
	{
		x_ = message.X;
		y_ = message.Y;
	}
	void Window::OnWindowResize(const WindowResizeMessage& message)
	{
		width_ = message.Width;
		height_ = message.Height;
	}
}
