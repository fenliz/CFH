#pragma once
#include <functional>
#include <stdint.h>

namespace CFH
{
	typedef int MessageTypeId;
	typedef void* MessageSubscriber;

	// Functions receiving messages must follow this convention:
	// void OnMessageReceived(MESSAGETYPE message);
	template<typename MESSAGETYPE> using MessageSubscribeFunction =
		std::function<void(MESSAGETYPE)>;

	struct Message
	{
		static int TypeIdCounter;

		template<typename T>
		static MessageTypeId GetTypeId()
		{
			// Trick for generating unique ids for the different types T that calls the method.
			static int placeHolder = Message::TypeIdCounter++;
			return placeHolder;
		}
	};

	class BeginFrameMessage	{};
	class EndFrameMessage {};
}