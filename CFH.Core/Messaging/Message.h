#pragma once
#include "MessageBus.h"

namespace CFH
{
	struct FrameBeginMessage {};
	struct FrameEndMessage {};

	enum class WindowState
	{
		Closed,
		Activated,
		Deactivated
	};
	struct WindowStateMessage 
	{
		WindowStateMessage(WindowState state) 
		{ 
			State = state; 
		}
		WindowState State;
	};

	struct WindowResizeMessage 
	{
		WindowResizeMessage(int width, int height)
		{
			Width = width; Height = height;
		}
		int Width; int Height;
	};
	struct WindowMoveMessage
	{
		WindowMoveMessage(int x, int y)
		{
			X = x; Y = y;
		}
		int X; int Y;
	};
}