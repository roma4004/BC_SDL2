//
// Created by d.romanichenko on 12-Jul-21.
//

#ifndef TIMER_HPP
#define TIMER_HPP

#include <functional>
#include <chrono>
#include <thread>
#include <atomic>
#include <mutex>
#include <future>
#include <condition_variable>

//template<class return_type, class...arguments>
class Timer
{
public:
	Timer(
			bool										autoRun,
			bool										isRepeatable,
			std::chrono::milliseconds					interval,
			std::function<void()> 						function
//			std::function<return_type(arguments...)>	function,
//			arguments...								args
			)
		:
			_isRepeatable(isRepeatable),
			_interval(interval),
			_function(std::move(function))
//			f(std::async(std::launch::async, Callback))
		{ if (autoRun) enable(/*, args...*/); }
	~Timer() { if (Running()) disable(); }

	[[nodiscard]] std::atomic_bool const& Running() const { return _isRunning; }
	void disable() { if (Running()) _isRunning = false; }
	void enable(/*arguments...args*/)
	{
		if (Running())
			return;
		_isRunning = true;

		_thread = std::thread([&]()
		{
			while (_isRunning)
			{
				std::this_thread::sleep_until(
						std::chrono::steady_clock::now() += _interval);

				_function(/*args...*/);

				if (!_isRepeatable)
					_isRunning = false;
			}
		});
		_thread.detach();
	}

private:
	std::function<void()>						_function;
//	std::function<return_type(arguments...)>	_function;
//TODO: refactor atomic_bool to atomic_flag
	std::atomic_bool							_isRunning {false };
	std::atomic_bool							_isRepeatable;
	std::chrono::milliseconds					_interval;
	std::thread									_thread;

	std::mutex mutex;
	std::future<int> f;
	/*
	void threadFunc()
	{
		using std::chrono::high_resolution_clock;
		using std::chrono::duration_cast;
		using std::chrono::duration;
		using std::chrono::milliseconds;

		do
		{
			//Ждем runIntervalMs
			if (f.wait_for(runIntervalMs) == std::future_status::ready)
				callback();
			//		elapsedTime = std::chrono::high_resolution_clock::now();
			//		auto timeDiff = std::chrono::duration_cast<std::chrono::seconds>(elapsedTime - startTime).count();
			//		if (timeDiff >= runIntervalMs)
			//		{
			//std::cout << elapsedTime.asSeconds() << std::endl;

			//reset start time for new interval
			//			startTime = std::chrono::high_resolution_clock::now();
			//		}

			if (!isRepeatable)
				return;
	}

	private:
	 */
};

#endif //TIMER_HPP
