#pragma once
#include "..\CFH.h"

#include <Windows.h>
#include <atomic>

namespace CFH
{
	class EngineContext;
	struct WindowResizeMessage;
	struct WindowMoveMessage;

	// Used for creating a Window that the engine could draw to.
	class Window
	{
	public:
		Window(EngineContext* context);
		~Window();

		bool Initialize(LPWSTR title);
		bool Initialize(int width, int height, LPWSTR title);

		bool Show();
		bool Hide();

		HWND GetHandle();
		HINSTANCE GetInstance();

		int GetX();
		int GetY();
		int GetWidth();
		int GetHeight();

		LPWSTR GetTitle();
		bool IsFullscreen();

		static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	private:
		Window(const Window&);

		HWND hWnd_;
		HINSTANCE hInstance_;

		LPWSTR title_;
		std::atomic<bool> fullscreen_;
		std::atomic<int> x_, y_;
		std::atomic<int> width_, height_;

		bool InitializeWindow();

		void OnWindowMove(const WindowMoveMessage& message);
		void OnWindowResize(const WindowResizeMessage& message);
	};

}
