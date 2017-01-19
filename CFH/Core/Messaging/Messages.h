#pragma once

#include "MessageBus.h"

namespace CFH
{

	struct FrameBeginMessage {};
	struct FrameEndMessage {};

	struct WindowShowMessage {};
	struct WindowHideMessage {};
	struct WindowCloseMessage {};
	struct WindowResizeMessage {
		WindowResizeMessage(int width, int height) { Width = width; Height = height; }
		int Width; int Height;
	};
	struct WindowMoveMessage {
		WindowMoveMessage(int x, int y) { X = x; Y = y; }
		int X; int Y;
	};
}