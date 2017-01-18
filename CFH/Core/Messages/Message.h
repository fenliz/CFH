#pragma once
#include <functional>
#include <stdint.h>


namespace CFH
{
	typedef int MessageTypeId;
	typedef void* MessageSubscriber;

	template<typename MESSAGETYPE> using MessageSubscribeFunction =
		std::function<void(MESSAGETYPE)>;


	struct Message
{	
		static int TypeIdCounter;

		template<typename T>
		static MessageTypeId GetTypeId()
		{
			static int placeHolder = Message::TypeIdCounter++;
			return placeHolder;
		}
	};


	class BeginFrameMessage
	{
	};

	class EndFrameMessage
	{
	};
}