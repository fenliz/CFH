#include "Win32Game.h"
#include "Win32Time.h"
#include "Win32File.h"
#include "Win32Memory.h"
#include "Win32Thread.h"

#include "CFH.Core\CFH.h"
#include "CFH.Core\Messaging\Message.h"

namespace CFH
{
	void Win32Game::Start(char* title,
						  HINSTANCE instance,
						  int x, int y,
						  int width, int height)
	{
		ENABLE_CONSOLE_LOGGING(Logger::Severity::Debug);
		Win32Time::Setup();
		Win32Memory::Setup();
		Win32File::Setup();
		Win32Thread::Setup();

		{
			PROFILE(Win32_Window);

			WNDCLASSA windowClass = {};
			windowClass.style = CS_HREDRAW | CS_VREDRAW;
			windowClass.lpfnWndProc = Win32Game::WndProc;
			windowClass.hInstance = instance;
			windowClass.lpszClassName = "CFHWindowClass";

			if (!RegisterClassA(&windowClass))
			{
				MessageBoxA(0, "Failed to register window class!", 0, 0);
				return;
			}
			HWND window = CreateWindowExA(0,								// dwExStyle
										  windowClass.lpszClassName,		// lpClassName
										  title,							// lpWindowName
										  WS_OVERLAPPEDWINDOW | WS_VISIBLE,	// dwStyle
										  x,								// X
										  y,								// Y
										  width,							// nWidth
										  height,							// nHeight
										  nullptr,							// hWndParent
										  nullptr,							// hMenu
										  instance,							// hInstance
										  nullptr);							// lpParam
			if (!window)
			{
				MessageBoxA(0, "Failed to create window!", 0, 0);
				return;
			}
		}

		Win32Game game;
		game.Run();
	}

	void Win32Game::Run()
	{
		{
			PROFILE(Win32_Start);

			engine_.Initialize();
			input_.Initialize();

		}

		bool isRunning = true;
		while (isRunning)
		{
			SEND_MESSAGE(FrameBeginMessage());

			input_.Update();


			{
				PROFILE(Win32_Message);

				MSG message;
				while (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
				{
					switch (message.message)
					{

					case WM_QUIT:
						isRunning = false;
						break;

					case WM_SYSKEYDOWN:
					case WM_SYSKEYUP:
					case WM_KEYDOWN:
					case WM_KEYUP:
						input_.HandleKeyMessage(message.wParam,
												message.lParam);
						break;

					case WM_INPUT:
						input_.HandleRawInput((HRAWINPUT)message.lParam);
						break;

					default:
						TranslateMessage(&message);
						DispatchMessage(&message);
					}
				}
			}


			{
				PROFILE(Win32_Update);

				engine_.Update(input_.EngineInput);

			}

			SEND_MESSAGE(FrameEndMessage());
		}

		{
			PROFILE(Win32_Quit);

		}
	}

	void Win32Game::Stop()
	{
		PostMessageA(0, WM_QUIT, 0, 0);
	}

	HRESULT Win32Game::WndProc(HWND window,
							   UINT msg,
							   WPARAM wParam,
							   LPARAM lParam)
	{
		HRESULT result = 0;
		switch (msg)
		{
		case WM_DESTROY:
		case WM_CLOSE:
			SEND_MESSAGE(WindowStateMessage(WindowState::Closed));
			PostQuitMessage(0);
			break;

		case WM_ACTIVATE:
			if (wParam == 1 || wParam == 2)
				SEND_MESSAGE(WindowStateMessage(WindowState::Activated));
			else if (wParam == 0 || wParam == 2097152)
				SEND_MESSAGE(WindowStateMessage(WindowState::Deactivated));
			break;

		case WM_SIZE:
			SEND_MESSAGE(WindowResizeMessage(LOWORD(lParam), HIWORD(lParam)));
			break;

		case WM_MOVE:
			SEND_MESSAGE(WindowMoveMessage(LOWORD(lParam), HIWORD(lParam)));
			break;

		default:
			result = DefWindowProc(window, msg, wParam, lParam);
			break;
		}
		return result;
	}
}
