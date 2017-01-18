#pragma once
#include "MessageTypes.h"
#include "MessageTypeContainer.h"

namespace CFH
{
	// Convenience macros for sending and subscribe/unsubscribing to messages.
#define SEND_DEFAULT_MESSAGE(messageType) \
	MessageBus::GetInstance()->Send<messageType>(messageType());
#define SEND_MESSAGE(messageType, message) \
	MessageBus::GetInstance()->Send<messageType>(message)

#define POST_DEFAULT_MESSAGE(messageType) \
	MessageBus::GetInstance()->Post<messageType>(messageType());
#define POST_MESSAGE(messageType, message) \
	MessageBus::GetInstance()->Post<messageType>(message);

#define SUBSCRIBE_TO_MESSAGE(messageType, subscriber, function) \
	MessageBus::GetInstance()->Subscribe<messageType>(subscriber, function)

#define UNSUBSCRIBE_FROM_MESSAGE(messageType, subscriber) \
	MessageBus::GetInstance()->Unsubscribe<messageType>(subscriber);

#define UNSUBSCRIBE_FROM_MESSAGES(subscriber) \
	MessageBus::GetInstance()->Unsubscribe(subscriber);


	// Used as a hub for messages. All messages are transmitted through one instance of this class.
	class MessageBus
	{
	public:
		MessageBus();
		MessageBus(const MessageBus&) = delete;
		~MessageBus();

		static MessageBus* GetInstance();

		template<typename MESSAGETYPE>
		void Subscribe(MessageSubscriber subscriber, MessageSubscribeFunction<MESSAGETYPE> function) 
		{
			MessageTypeContainer<MESSAGETYPE>* container;
			MessageTypeId typeId = Message::GetTypeId<MESSAGETYPE>();

			mutex_.LockExclusive();
			auto it = messageContainers_.find(typeId);
			if (it != messageContainers_.end())
				container = static_cast<MessageTypeContainer<MESSAGETYPE>*>(it->second);
			else
			{
				container = new MessageTypeContainer<MESSAGETYPE>();
				messageContainers_.insert(std::make_pair(typeId, (MessageTypeContainerBase*)container));
			}
			container->Subscribe(subscriber, function);
			mutex_.UnlockExclusive();
		}

		void Unsubscribe(MessageSubscriber subscriber);

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
		static MessageBus* instance_;

		std::map<MessageTypeId, MessageTypeContainerBase*> messageContainers_;
		SharedMutex mutex_;

	};
}