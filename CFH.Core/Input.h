#pragma once
#include "CFH.Core\Types.h"
#include "Middleware\CFH.Math\Vector2.h"

namespace CFH
{
	class CFHCORE_API Input
	{
	public:
		enum class Buttons
		{
			Up,
			Down,
			Left,
			Right,
			DPadUp,
			DPadDown,
			DPadLeft,
			DPadRight,
			LeftShoulder,
			RightShoulder,
			Start,
			Back,
			Count
		};
		enum class MouseButtons
		{
			Left,
			Right,
			Middle,
			Thumb1,
			Thumb2,
			Count
		};
		enum class Keys
		{
			_0,
			_1,
			_2,
			_3,
			_4,
			_5,
			_6,
			_7,
			_8,
			_9,
			A,
			Alt,
			B,
			Backspace,
			C,
			Control,
			CapsLock,
			D,
			Delete,
			Down,
			E,
			End,
			Enter,
			Escape,
			F,
			F1,
			F10,
			F11,
			F12,
			F2,
			F3,
			F4,
			F5,
			F6,
			F7,
			F8,
			F9,
			G,
			H,
			Home,
			I,
			Insert,
			J,
			K,
			L,
			Left,
			M,
			N,
			NumMinus,
			NumPlus,
			NumDivide,
			NumMultiply,
			Num0,
			Num1,
			Num2,
			Num3,
			Num4,
			Num5,
			Num6,
			Num7,
			Num8,
			Num9,
			NumLock,
			O,
			P,
			PageDown,
			PageUp,
			Pause,
			PrintScreen,
			Q,
			R,
			Right,
			S,
			ScrollLock,
			Shift,
			SpaceBar,
			T,
			Tab,
			U,
			Up,
			V,
			W,
			X,
			Y,
			Z,
			Count,
			Invalid
		};

		struct KeyState
		{
			int32 ChangeCount;
			bool32 IsDown;
		};
		struct ButtonState
		{
			int32 ChangeCount;
			bool32 IsDown;
		};

		struct StickState
		{
			Math::Vector2 State;
			Math::Vector2 Delta;
		};

		struct TriggerState
		{
			real32 State;
			real32 Delta;
		};

		struct ControllerState
		{
			bool32 IsConnected;
			bool32 IsAnalog;

			StickState LeftThumbstick;
			StickState RightThumbstick;

			TriggerState LeftTrigger;
			TriggerState RightTrigger;

			union
			{
				ButtonState Buttons[(uint32)Buttons::Count];
				struct
				{
					ButtonState Up;
					ButtonState Down;
					ButtonState Left;
					ButtonState Right;

					ButtonState DPadUp;
					ButtonState DPadDown;
					ButtonState DPadLeft;
					ButtonState DPadRight;

					ButtonState LeftShoulder;
					ButtonState RightShoulder;

					ButtonState Start;
					ButtonState Back;
				};
			};
		};

		struct MouseState
		{
			int32 Wheel;
			Math::Vector2 Position;
			Math::Vector2 Delta;
			union
			{
				ButtonState Buttons[(uint32)MouseButtons::Count];
				struct
				{
					ButtonState Left;
					ButtonState Right;
					ButtonState Middle;
					ButtonState Thumb1;
					ButtonState Thumb2;
				};
			};
		};

		struct State
		{
			ControllerState Controllers[4];
			MouseState Mouse;
			union
			{
				KeyState Keys[(uint32)Keys::Count];
				struct
				{
					KeyState _0;
					KeyState _1;
					KeyState _2;
					KeyState _3;
					KeyState _4;
					KeyState _5;
					KeyState _6;
					KeyState _7;
					KeyState _8;
					KeyState _9;
					KeyState A;
					KeyState Alt;
					KeyState B;
					KeyState Backspace;
					KeyState C;
					KeyState Control;
					KeyState CapsLock;
					KeyState D;
					KeyState Delete;
					KeyState Down;
					KeyState E;
					KeyState End;
					KeyState Enter;
					KeyState Escape;
					KeyState F;
					KeyState F1;
					KeyState F10;
					KeyState F11;
					KeyState F12;
					KeyState F2;
					KeyState F3;
					KeyState F4;
					KeyState F5;
					KeyState F6;
					KeyState F7;
					KeyState F8;
					KeyState F9;
					KeyState G;
					KeyState H;
					KeyState Home;
					KeyState I;
					KeyState Insert;
					KeyState J;
					KeyState K;
					KeyState L;
					KeyState Left;
					KeyState M;
					KeyState N;
					KeyState NumMinus;
					KeyState NumPlus;
					KeyState NumDivide;
					KeyState NumMultiply;
					KeyState Num0;
					KeyState Num1;
					KeyState Num2;
					KeyState Num3;
					KeyState Num4;
					KeyState Num5;
					KeyState Num6;
					KeyState Num7;
					KeyState Num8;
					KeyState Num9;
					KeyState NumLock;
					KeyState O;
					KeyState P;
					KeyState PageDown;
					KeyState PageUp;
					KeyState Pause;
					KeyState PrintScreen;
					KeyState Q;
					KeyState R;
					KeyState Right;
					KeyState S;
					KeyState ScrollLock;
					KeyState Shift;
					KeyState SpaceBar;
					KeyState T;
					KeyState Tab;
					KeyState U;
					KeyState Up;
					KeyState V;
					KeyState W;
					KeyState X;
					KeyState Y;
					KeyState Z;
				};
			} Keyboard;
		};

	};
}