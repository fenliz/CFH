#pragma once
#include "MessageBus.h"
#include "MessageTypeContainer.h"

#include <list>
#include <future>

namespace CFH
{
	class MessageBus
	{
	public:
		MessageBus()
		{
		}
		MessageBus(const MessageBus&) = delete;
		~MessageBus()
		{
			mutex_.LockExclusive();
			for (auto& it : messageContainers_)
				delete it.second;
			mutex_.UnlockExclusive();
		}

		template<typename MESSAGETYPE>
		void Subscribe(MessageSubscriber subscriber, MessageSubscribeFunction<MESSAGETYPE> function)
		{
			MessageTypeContainer<MESSAGETYPE>* container;
			MessageTypeId typeId = Message::GetTypeId<MESSAGETYPE>();

			mutex_.LockExclusive();
			auto it = messageContainers_.find(typeId);
			if (it != messageContainers_.end())
				container =	static_cast<MessageTypeContainer<MESSAGETYPE>*>(it->second);
			else
			{
				container = new MessageTypeContainer<MESSAGETYPE>();
				messageContainers_.insert(std::make_pair(typeId, (MessageTypeContainerBase*)container));
			}
			container->Subscribe(subscriber, function);
			mutex_.UnlockExclusive();
		}

		void Unsubscribe(MessageSubscriber subscriber)
		{
			mutex_.LockExclusive();
			for (auto& it : messageContainers_)
				it.second->Unsubscribe(subscriber);
			mutex_.UnlockExclusive();
		}

		template<typename MESSAGETYPE>
		void Unsubscribe(MessageSubscriber subscriber)
		{
			MessageTypeId typeId = Message::GetTypeId<MESSAGETYPE>();

			mutex_.LockExclusive();
			auto it = messageContainers_.find(typeId);
			if (it != messageContainers_.end())
			{
				MessageTypeContainer<MESSAGETYPE>* container =
					static_cast<MessageTypeContainer<MESSAGETYPE>*>(iter->second);
				container->Remove(message);

				if (container->IsEmpty())
					messageContainers_.erase(it);
			}
			mutex_.UnlockExclusive();
		}

		template<typename MESSAGETYPE>
		void Send(const MESSAGETYPE& message)
		{
			MessageTypeId typeId = Message::GetTypeId<MESSAGETYPE>();

			mutex_.LockShared();
			auto it = messageContainers_.find(typeId);
			if (it != messageContainers_.end())
			{
				MessageTypeContainer<MESSAGETYPE>* container =
					static_cast<MessageTypeContainer<MESSAGETYPE>*>(it->second);
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
		std::map<MessageTypeId, MessageTypeContainerBase*> messageContainers_;
		SharedMutex mutex_;
	};
}