#pragma once
#include "Input.h"

namespace CFH
{
	class CFHCORE_API Engine
	{
	public:
		void Initialize();
		void Update(Input::State* input);
	};
}