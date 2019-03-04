#pragma once
#include "pch.h"
#include <condition_variable>
#include <deque>
#include <mutex>


template <typename T>
class FifoBuffer
{
private:
	std::condition_variable condition;
	std::deque<T> buffer;
	std::mutex mutex;

public:
	FifoBuffer() {};

	~FifoBuffer() {};

	inline void push(T const& value) {
		{
			std::unique_lock<std::mutex> lock(this->mutex);
			buffer.push_front(value);
		}
		this->condition.notify_one();
	}

	inline T pop() {
		T result;
		std::unique_lock<std::mutex> lock(this->mutex);
		if (this->condition.wait_for(lock, std::chrono::milliseconds(1), [this] {return !this->buffer.empty(); })) {
			result = this->buffer.back();
			this->buffer.pop_back();
		} else { 
			result = T();
		}
		return result;
	}

	inline bool empty() {
		std::unique_lock<std::mutex> lock(this->mutex);
		return buffer.empty();
	}
};
