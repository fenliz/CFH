#include "Win32Input.h"
#include "Win32Memory.h"

#include "CFH.Core\Engine.h"

namespace CFH
{
	class Win32Game
	{
	public:
		static CFHWIN32_API void Start(char* title,
								  HINSTANCE instance = nullptr,
								  int x = CW_USEDEFAULT, int y = CW_USEDEFAULT,
								  int width = CW_USEDEFAULT, int height = CW_USEDEFAULT);

		static CFHWIN32_API void Stop();
	private:
		Win32Game() {}
		Win32Game(const Win32Game&) = delete;
		~Win32Game() {}

		void Run();

		Engine engine_;
		Win32Input input_;
		Win32Memory memory_;

		static HRESULT CALLBACK WndProc(HWND window, UINT msg, WPARAM wParam, LPARAM lParam);
	};
}