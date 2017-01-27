#pragma once
#include "CFH.Core\Threading\SharedMutex.h"

#include <map>

namespace CFH
{
	template<typename MESSAGE> using MESSAGESUBSCRIBERFUNC =
		std::function<void(MESSAGE)>;

	class MessageSubscribersBase
	{
	public:
		virtual void Unsubscribe(void* subscriber) = 0;
	};

	template<typename MESSAGETYPE>
	class MessageSubscribers : MessageSubscribersBase
	{
	public:
		MessageSubscribers() {}
		~MessageSubscribers() {}

		MessageSubscribers(const MessageSubscribers&) = delete;
		MessageSubscribers& operator=(const MessageSubscribers&) = delete;

		void Subscribe(void* subscriber, MESSAGESUBSCRIBERFUNC<MESSAGETYPE> function)
		{
			mutex_.LockExclusive();
			subscribers_.insert(std::make_pair(subscriber, function));
			mutex_.UnlockExclusive();
		}

		void Unsubscribe(void* subscriber)
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

		bool32 IsEmpty()
		{
			return subscribers_.empty();
		}

	private:
		std::map<void*, MESSAGESUBSCRIBERFUNC<MESSAGETYPE>> subscribers_;
		SharedMutex mutex_;
	};
};