#include "Win32Input.h"

#include "CFH.Core\Logging\Logger.h"

namespace CFH
{
	XINPUTGETSTATE(XInputGetStateStub) { return ERROR_DEVICE_NOT_CONNECTED; }
	xinputgetstate* Win32Input::XInputGetState = XInputGetStateStub;
	XINPUTSETSTATE(XInputSetStateStub) { return ERROR_DEVICE_NOT_CONNECTED; }
	xinputsetstate* Win32Input::XInputSetState = XInputSetStateStub;

	void Win32Input::Initialize()
	{
		for (int i = 0; i < ArrayCount(isControllerActive_); i++)
			isControllerActive_[i] = false;

		input_[0] = {};
		input_[1] = {};

		EngineInput = &input_[0];
		oldInput_ = &input_[1];

		InitializeRawInput();
		InitializeXInput();
	}
	void Win32Input::InitializeRawInput()
	{
		RAWINPUTDEVICE rid;
		rid.usUsagePage = 0x01;
		rid.usUsage = 0x02;
		rid.dwFlags = 0;
		rid.hwndTarget = 0;

		if (!RegisterRawInputDevices(&rid, 1, sizeof(rid)))
			LOG_ERROR("Could not register RawInput devices.");

		POINT point;
		GetCursorPos(&point);
		EngineInput->Mouse.Position.X = (real32)point.x;
		EngineInput->Mouse.Position.Y = (real32)point.y;
	}
	void Win32Input::InitializeXInput()
	{
		HMODULE XInputLibrary = LoadLibraryA("xinput1_4.dll");

		if (!XInputLibrary)
			XInputLibrary = LoadLibraryA("xinput9_1_0.dll");

		if (!XInputLibrary)
			XInputLibrary = LoadLibraryA("xinput1_3.dll");

		if (XInputLibrary)
		{
			XInputGetState = (xinputgetstate*)GetProcAddress(XInputLibrary, "XInputGetState");
			XInputSetState = (xinputsetstate*)GetProcAddress(XInputLibrary, "XInputSetState");
		}
	}

	void Win32Input::Update()
	{
		Input::KeyState* key = &EngineInput->Keyboard.Keys[0];
		for (int keysIndex = 0; keysIndex < ArrayCount(EngineInput->Keyboard.Keys); keysIndex++)
		{
			key->ChangeCount = 0;
			key++;
		}

		for (DWORD controllerIndex = 0; controllerIndex < XUSER_MAX_COUNT; controllerIndex++)
		{
			Input::ControllerState* oldController = &oldInput_->Controllers[controllerIndex];
			Input::ControllerState* newController = &EngineInput->Controllers[controllerIndex];

			XINPUT_STATE controllerState;
			if (isControllerActive_[controllerIndex] &&
				XInputGetState(controllerIndex, &controllerState) == ERROR_SUCCESS)
			{
				newController->IsConnected = true;
				newController->IsAnalog = oldController->IsAnalog;

				XINPUT_GAMEPAD* pad = &controllerState.Gamepad;
				newController->LeftThumbstick.State.X = ProcessXInputStickValue(pad->sThumbLX, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
				newController->LeftThumbstick.Delta.X = newController->LeftThumbstick.State.X - oldController->LeftThumbstick.State.X;

				newController->LeftThumbstick.State.Y = ProcessXInputStickValue(pad->sThumbLY, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
				newController->LeftThumbstick.Delta.Y = newController->LeftThumbstick.State.Y - oldController->LeftThumbstick.State.Y;

				newController->RightThumbstick.State.X = ProcessXInputStickValue(pad->sThumbRX, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
				newController->RightThumbstick.Delta.X = newController->RightThumbstick.State.X - oldController->RightThumbstick.State.X;

				newController->RightThumbstick.State.Y = ProcessXInputStickValue(pad->sThumbRY, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
				newController->RightThumbstick.Delta.Y = newController->RightThumbstick.State.Y - oldController->RightThumbstick.State.Y;

				newController->LeftTrigger.State = (real32)((pad->bLeftTrigger - XINPUT_GAMEPAD_TRIGGER_THRESHOLD) /
					(255 - XINPUT_GAMEPAD_TRIGGER_THRESHOLD));
				newController->LeftTrigger.Delta = newController->LeftTrigger.State - oldController->LeftTrigger.State;

				newController->RightTrigger.State = (real32)((pad->bRightTrigger - XINPUT_GAMEPAD_TRIGGER_THRESHOLD) /
					(255 - XINPUT_GAMEPAD_TRIGGER_THRESHOLD));
				newController->RightTrigger.Delta = newController->RightTrigger.State - oldController->RightTrigger.State;

				ProcessXInputButton(pad->wButtons, XINPUT_GAMEPAD_Y,
									&oldController->Up, &newController->Up);
				ProcessXInputButton(pad->wButtons, XINPUT_GAMEPAD_A,
									&oldController->Down, &newController->Down);
				ProcessXInputButton(pad->wButtons, XINPUT_GAMEPAD_X,
									&oldController->Left, &newController->Left);
				ProcessXInputButton(pad->wButtons, XINPUT_GAMEPAD_B,
									&oldController->Right, &newController->Right);

				ProcessXInputButton(pad->wButtons, XINPUT_GAMEPAD_DPAD_UP,
									&oldController->DPadUp, &newController->DPadUp);
				ProcessXInputButton(pad->wButtons, XINPUT_GAMEPAD_DPAD_DOWN,
									&oldController->DPadDown, &newController->DPadDown);
				ProcessXInputButton(pad->wButtons, XINPUT_GAMEPAD_DPAD_LEFT,
									&oldController->DPadLeft, &newController->DPadLeft);
				ProcessXInputButton(pad->wButtons, XINPUT_GAMEPAD_DPAD_RIGHT,
									&oldController->DPadRight, &newController->DPadRight);

				ProcessXInputButton(pad->wButtons, XINPUT_GAMEPAD_LEFT_SHOULDER,
									&oldController->LeftShoulder, &newController->LeftShoulder);
				ProcessXInputButton(pad->wButtons, XINPUT_GAMEPAD_RIGHT_SHOULDER,
									&oldController->RightShoulder, &newController->RightShoulder);

				ProcessXInputButton(pad->wButtons, XINPUT_GAMEPAD_START,
									&oldController->Start, &newController->Start);
				ProcessXInputButton(pad->wButtons, XINPUT_GAMEPAD_BACK,
									&oldController->Back, &newController->Back);
			}
			else
			{
				newController->IsConnected = false;
				isControllerActive_[controllerIndex] = false;
			}
		}

		Input::State* temp = EngineInput;
		EngineInput = oldInput_;
		oldInput_ = temp;

		POINT point;
		GetCursorPos(&point);
		EngineInput->Mouse.Position = Math::Vector2((real32)point.x, (real32)point.y);
		oldInput_->Mouse.Delta = Math::Vector2::Zero;
	}

	HRESULT Win32Input::HandleRawInput(HRAWINPUT rawInput)
	{
		UINT dwSize;
		GetRawInputData(rawInput, RID_INPUT, nullptr, &dwSize, sizeof(RAWINPUTHEADER));
		LPBYTE lpb = new BYTE[dwSize];
		if (!lpb)
			return E_FAIL;

		if (GetRawInputData(rawInput, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER)) != dwSize)
			return E_FAIL;

		RAWINPUT* raw = (RAWINPUT*)lpb;
		if (raw->header.dwType == RIM_TYPEMOUSE)
		{
			RAWMOUSE* mouse = &raw->data.mouse;
			switch (mouse->usFlags)
			{
			case MOUSE_MOVE_RELATIVE:
				EngineInput->Mouse.Delta.X += raw->data.mouse.lLastX;
				EngineInput->Mouse.Delta.Y += raw->data.mouse.lLastY;
				break;
			}
		}

		return S_OK;
	}
	HRESULT Win32Input::HandleKeyMessage(uint32 vkCode, uint32 flags)
	{
		bool32 wasDown = ((flags & (1 << 30)) != 0);
		bool32 isDown = ((flags & (1 << 31)) == 0);

		if (wasDown == isDown)
			return E_FAIL;

		Input::Keys key = TranslateVKToInputKey(vkCode);
		if (key == Input::Keys::Invalid)
		{
			LOG_DEBUG("Received invalid keymessage with VK " << vkCode);
			return E_FAIL;
		}

		Input::KeyState* keyState = &EngineInput->Keyboard.Keys[(uint32)key];
		if (keyState->IsDown != isDown)
		{
			keyState->IsDown = isDown;
			keyState->ChangeCount++;
		}

		return S_OK;
	}

	Input::Keys Win32Input::TranslateVKToInputKey(uint32 vkCode)
	{
		switch (vkCode)
		{
		case 0x30: return Input::Keys::_0;
		case 0x31: return Input::Keys::_1;
		case 0x32: return Input::Keys::_2;
		case 0x33: return Input::Keys::_3;
		case 0x34: return Input::Keys::_4;
		case 0x35: return Input::Keys::_5;
		case 0x36: return Input::Keys::_6;
		case 0x37: return Input::Keys::_7;
		case 0x38: return Input::Keys::_8;
		case 0x39: return Input::Keys::_9;

		case 0x41: return Input::Keys::A;
		case 0x42: return Input::Keys::B;
		case 0x43: return Input::Keys::C;
		case 0x44: return Input::Keys::D;
		case 0x45: return Input::Keys::E;
		case 0x46: return Input::Keys::F;
		case 0x47: return Input::Keys::G;
		case 0x48: return Input::Keys::H;
		case 0x49: return Input::Keys::I;
		case 0x4A: return Input::Keys::J;
		case 0x4B: return Input::Keys::K;
		case 0x4C: return Input::Keys::L;
		case 0x4D: return Input::Keys::M;
		case 0x4E: return Input::Keys::N;
		case 0x4F: return Input::Keys::O;
		case 0x50: return Input::Keys::P;
		case 0x51: return Input::Keys::Q;
		case 0x52: return Input::Keys::R;
		case 0x53: return Input::Keys::S;
		case 0x54: return Input::Keys::T;
		case 0x55: return Input::Keys::U;
		case 0x56: return Input::Keys::V;
		case 0x57: return Input::Keys::W;
		case 0x58: return Input::Keys::X;
		case 0x59: return Input::Keys::Y;
		case 0x5A: return Input::Keys::Z;

		case VK_F1: return Input::Keys::F1;
		case VK_F2: return Input::Keys::F2;
		case VK_F3: return Input::Keys::F3;
		case VK_F4: return Input::Keys::F4;
		case VK_F5: return Input::Keys::F5;
		case VK_F6: return Input::Keys::F6;
		case VK_F7: return Input::Keys::F7;
		case VK_F8: return Input::Keys::F8;
		case VK_F9: return Input::Keys::F9;
		case VK_F10: return Input::Keys::F10;
		case VK_F11: return Input::Keys::F11;
		case VK_F12: return Input::Keys::F11;

		case VK_MENU: return Input::Keys::Alt;
		case VK_CONTROL: return Input::Keys::Control;
		case VK_SHIFT: return Input::Keys::Shift;
		case VK_CAPITAL: return Input::Keys::CapsLock;
		case VK_SPACE: return Input::Keys::SpaceBar;
		case VK_RETURN: return Input::Keys::Enter;
		case VK_BACK: return Input::Keys::Backspace;
		case VK_ESCAPE: return Input::Keys::Escape;
		case VK_TAB: return Input::Keys::Tab;

		case VK_SNAPSHOT: return Input::Keys::PrintScreen;
		case VK_SCROLL: return Input::Keys::ScrollLock;
		case VK_PAUSE: return Input::Keys::Pause;
		case VK_INSERT: return Input::Keys::Insert;
		case VK_HOME: return Input::Keys::Home;
		case VK_PRIOR: return Input::Keys::PageUp;
		case VK_DELETE: return Input::Keys::Delete;
		case VK_END: return Input::Keys::End;
		case VK_NEXT: return Input::Keys::PageDown;

		case VK_UP: return Input::Keys::Up;
		case VK_DOWN: return Input::Keys::Down;
		case VK_LEFT: return Input::Keys::Left;
		case VK_RIGHT: return Input::Keys::Right;

		case VK_NUMPAD0: return Input::Keys::Num0;
		case VK_NUMPAD1: return Input::Keys::Num1;
		case VK_NUMPAD2: return Input::Keys::Num2;
		case VK_NUMPAD3: return Input::Keys::Num3;
		case VK_NUMPAD4: return Input::Keys::Num4;
		case VK_NUMPAD5: return Input::Keys::Num5;
		case VK_NUMPAD6: return Input::Keys::Num6;
		case VK_NUMPAD7: return Input::Keys::Num7;
		case VK_NUMPAD8: return Input::Keys::Num8;
		case VK_NUMPAD9: return Input::Keys::Num9;
		case VK_NUMLOCK: return Input::Keys::NumLock;
		case VK_SUBTRACT: return Input::Keys::NumMinus;
		case VK_ADD: return Input::Keys::NumPlus;
		case VK_DIVIDE: return Input::Keys::NumDivide;
		case VK_MULTIPLY: return Input::Keys::NumMultiply;
		}

		return Input::Keys::Invalid;
	}

	void Win32Input::ProcessKeyboardButton(Input::ButtonState* state, bool32 isDown)
	{
		if (state->IsDown != isDown)
		{
			state->IsDown = isDown;
			state->ChangeCount++;
		}
	}

	void Win32Input::ProcessXInputButton(DWORD XInputButtonState, DWORD buttonBit,
										 Input::ButtonState* oldState, Input::ButtonState* newState)
	{
		newState->IsDown = ((XInputButtonState & buttonBit) == buttonBit);
		newState->ChangeCount = (oldState->IsDown != newState->IsDown) ? 1 : 0;
	}
	real32 Win32Input::ProcessXInputStickValue(SHORT value, SHORT deadZoneThreshold)
	{
		real32 result = 0;

		if (value < -deadZoneThreshold)
			result = (real32)((value + deadZoneThreshold) / (32768.0f - deadZoneThreshold));
		else if (value > deadZoneThreshold)
			result = (real32)((value - deadZoneThreshold) / (32767.0f - deadZoneThreshold));

		return result;
	}
}
