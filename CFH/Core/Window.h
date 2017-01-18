#pragma once
#include "..\CFH.h"

#include <Windows.h>

namespace CFH
{
	class EngineContext;

	// Used for creating a Window that the engine could draw to.
	class CFH_API Window
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
		bool fullscreen_;
		int x_, y_;
		int width_, height_;

		bool InitializeWindow();
	};

}
