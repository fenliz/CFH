#include "MessageBus.h"

#include <future>

namespace CFH
{
	MessageBus* MessageBus::instance_ = nullptr;

	MessageBus::MessageBus()
	{
		ASSERT(!instance_);
		instance_ = this;
	}
	MessageBus::~MessageBus()
	{
		mutex_.LockExclusive();
		for (auto& it : messageContainers_)
			delete it.second;
		mutex_.UnlockExclusive();
	}

	void MessageBus::Unsubscribe(MessageSubscriber subscriber)
	{
		mutex_.LockExclusive();
		for (auto& it : messageContainers_)
			it.second->Unsubscribe(subscriber);
		mutex_.UnlockExclusive();
	}

	MessageBus* MessageBus::GetInstance()
	{
		return instance_;
	}
}