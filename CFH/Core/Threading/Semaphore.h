#pragma once
#include "..\..\CFH.h"

#include <mutex>
#include <condition_variable>

namespace CFH
{
	// A "lock" which restrics multiple uses at the same time
	// and forces others to wait until it is unlocked.
	class Semaphore
	{
	public:
		explicit Semaphore(unsigned int initialCount) :
			count_(initialCount)
		{
		}
		~Semaphore() = default;

		void Lock()
		{
			std::unique_lock<std::mutex> lock(mutex_);
			condition_.wait(lock, [this] { return (count_ != 0); });
			count_--;
		}

		void Unlock()
		{
			std::lock_guard<std::mutex> lock(mutex_);
			count_++;
			condition_.notify_one();
		}

	private:
		unsigned int count_;
		std::condition_variable condition_;
		std::mutex mutex_;
	};
}