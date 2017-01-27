#pragma once
#include "CFH.Core\Types.h"
#include "CFH.Core\Input.h"

#include <Windows.h>
#include <Xinput.h>

#define XINPUTGETSTATE(name) DWORD WINAPI name(DWORD dwUserIndex, XINPUT_STATE* pState)
typedef XINPUTGETSTATE(xinputgetstate);
#define XInputGetState XInputGetState_

#define XINPUTSETSTATE(name) DWORD WINAPI name(DWORD dwUserIndex, XINPUT_VIBRATION* pVibration)
typedef XINPUTSETSTATE(xinputsetstate);
#define XInputSetState XInputSetState_

namespace CFH
{
	class Win32Input
	{
	public:
		void Initialize();
		void Update();

		Input::State* EngineInput;
		
		HRESULT HandleRawInput(HRAWINPUT input);
		HRESULT HandleKeyMessage(uint32 vkCode, uint32 flags);
	private:
		Input::State input_[2];
		Input::State* oldInput_;
		bool32 isControllerActive_[4];

		static xinputgetstate* XInputGetState_;
		static xinputsetstate* XInputSetState_;

		void InitializeRawInput();
		void InitializeXInput();

		void ProcessKeyboardButton(Input::ButtonState* newState, bool32 isDown);

		Input::Keys TranslateVKToInputKey(uint32 vkCode);

		void ProcessXInputButton(DWORD XInputButtonState, DWORD buttonBit, Input::ButtonState* oldState, Input::ButtonState* newState);
		real32 ProcessXInputStickValue(SHORT value, SHORT deadZone);
	};

}


