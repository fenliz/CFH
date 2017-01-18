#pragma once
#include "Semaphore.h"

namespace CFH
{
	class SharedMutex
	{
	public:
		SharedMutex() :
			sharedCount_(0),
			semaphore_(1)
		{
		}
		~SharedMutex()
		{
		}

		void LockShared()
		{
			entryMutex_.lock();
			entryMutex_.unlock();

			sharedEntryMutex_.lock();
			if (sharedCount_ == 0)
				semaphore_.Lock();
			sharedCount_++;
			sharedEntryMutex_.unlock();
		}

		void UnlockShared()
		{
			sharedEntryMutex_.lock();
			sharedCount_--;
			if (sharedCount_ == 0)
				semaphore_.Unlock();
			sharedEntryMutex_.unlock();
		}

		void LockExclusive()
		{
			entryMutex_.lock();
			semaphore_.Lock();
		}

		void UnlockExclusive()
		{
			semaphore_.Unlock();
			entryMutex_.unlock();
		}

	private:
		unsigned int sharedCount_;
		std::mutex entryMutex_;
		std::mutex sharedEntryMutex_;
		Semaphore semaphore_;
	};
}