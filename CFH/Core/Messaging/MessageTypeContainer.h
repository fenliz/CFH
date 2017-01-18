#pragma once
#include "MessageTypes.h"
#include "..\Threading\SharedMutex.h"

#include <map>

namespace CFH
{
	// A container for subscribers of a specific message.
	class MessageTypeContainerBase
	{
	public:
		virtual void Unsubscribe(MessageSubscriber subscriber) = 0;
	};

	template<typename MESSAGETYPE>
	class MessageTypeContainer : MessageTypeContainerBase
	{
	public:
		MessageTypeContainer() = default;
		MessageTypeContainer(const MessageTypeContainer&) = delete;
		~MessageTypeContainer() = default;

		void Subscribe(MessageSubscriber subscriber, MessageSubscribeFunction<MESSAGETYPE> function)
		{
			subscribers_.insert(std::make_pair(subscriber, function));
		}
		
		void Unsubscribe(MessageSubscriber subscriber)
		{
			mutex_.LockExclusive();

			auto it = subscribers_.find(subscriber);
			if (it != subscribers_.end())
				subscribers_.erase(it);

			mutex_.UnlockExclusive();
		}

		void Publish(const MESSAGETYPE& message)
		{
			mutex_.LockShared();

			for (auto& it : subscribers_)
				it.second(message);

			mutex_.UnlockShared();
		}

		void Clear()
		{
			mutex_.LockExclusive();

			subscribers_.clear();

			mutex_.UnlockExclusive();
		}
		
		bool IsEmpty()
		{
			return subscribers_.empty();
		}

	private:
		std::map<MessageSubscriber, MessageSubscribeFunction<MESSAGETYPE>> subscribers_;
		SharedMutex mutex_;
	};
}

