#pragma once
#include "MessageSubscribers.h"
#include "CFH.Core\CFH.h"

#include <functional>
#include <future>

namespace CFH
{
#define SEND_MESSAGE(message) \
	MessageBus::GetInstance()->Send(message)

#define POST_MESSAGE(message) \
	MessageBus::GetInstance()->Post<messageType>(message)

#define SUBSCRIBE_TO_MESSAGE(messageType, subscriber, function) \
	MessageBus::GetInstance()->Subscribe<messageType>(subscriber, function)

#define UNSUBSCRIBE_FROM_MESSAGE(messageType, subscriber) \
	MessageBus::GetInstance()->Unsubscribe<messageType>(subscriber)

#define UNSUBSCRIBE_FROM_MESSAGES(subscriber) \
	MessageBus::GetInstance()->Unsubscribe(subscriber)

	class MessageBus
	{
	public:
		static MessageBus* GetInstance()
		{
			static MessageBus instance;
			return &instance;
		}

		template<typename MESSAGETYPE>
		void Subscribe(void* subscriber, MESSAGESUBSCRIBERFUNC<MESSAGETYPE> function)
		{
			MessageSubscribers<MESSAGETYPE>* container;
			int32* type = GetTypeId<MESSAGETYPE>();

			mutex_.LockExclusive();
			auto it = messageSubscribers_.find(type);
			if (it != messageSubscribers_.end())
				container = static_cast<MessageSubscribers<MESSAGETYPE>*>(it->second);
			else
			{
				container = new MessageSubscribers<MESSAGETYPE>();
				messageSubscribers_.insert(std::make_pair(type, (MessageSubscribersBase*)container));
			}
			container->Subscribe(subscriber, function);
			mutex_.UnlockExclusive();
		}

		void Unsubscribe(void* subscriber)
		{
			for (auto& it : messageSubscribers_)
				it.second->Unsubscribe(subscriber);
		}
		
		template<typename MESSAGETYPE>
		void Unsubscribe(void* subscriber)
		{
			int32* type = GetTypeId<MESSAGETYPE>();

			mutex_.LockExclusive();
			auto it = messageSubscribers_.find(type);
			if (it != messageSubscribers_.end())
			{
				MessageSubscribers<MESSAGETYPE>* container =
					static_cast<MessageSubscribers<MESSAGETYPE>*>(it->second);
				subscribers->Unsubscribe(container);
			}
			mutex_.UnlockExclusive();
		}

		template<typename MESSAGETYPE>
		void Send(const MESSAGETYPE& message)
		{
			int32* type = GetTypeId<MESSAGETYPE>();

			mutex_.LockShared();
			auto it = messageSubscribers_.find(type);
			if (it != messageSubscribers_.end())
			{
				MessageSubscribers<MESSAGETYPE>* container =
					static_cast<MessageSubscribers<MESSAGETYPE>*>(it->second);
				container->Publish(message);
			}
			mutex_.UnlockShared();
		}

		template<typename MESSAGETYPE>
		void Post(const MESSAGETYPE& message)
		{
			std::async(std::launch::async, Send<MESSAGETYPE>(message));
		}

	private:
		template<typename MESSAGETYPE>
		static int32* GetTypeId()
		{
			static int type;
			return &type;
		}

		MessageBus() {}
		~MessageBus() {}

		MessageBus(const MessageBus&) = delete;
		MessageBus& operator=(const MessageBus&) = delete;

		std::map<int32*, MessageSubscribersBase*> messageSubscribers_;
		SharedMutex mutex_;
	};
}