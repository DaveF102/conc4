#include "sharedvar.h"

template <typename T>
T MessageQueue<T>::receive()
{
	//Lock prior to accessing
	std::unique_lock<std::mutex> uLock(_mutex);
	//Wait for new message
	_cond.wait(uLock, [this] { return !_queue.empty(); });
	//Use move semantics to remove message from queue
	T msg = std::move(_queue.back());
	_queue.pop_back();

	return msg;
}

template <typename T>
void MessageQueue<T>::send(T &&msg)
{
	//Lock prior to accessing
	std::lock_guard<std::mutex> uLock(_mutex);
	//Remove old messages
	_queue.clear();
	//Add new message to queue
	_queue.emplace_back(std::move(msg));
	_cond.notify_one();
}

void SharedVar::SetSS(SharedStruct ss)
{
	_fmq.send(std::move(ss));
}
	
SharedStruct SharedVar::GetSS()
{
	SharedStruct rv;
	rv = _fmq.receive();
	return rv;
}

void InitThreads::CallWorkers(int thn, std::string ufP)
{
	Worker wrk;
	wrk.InitWorker(thn, ufP);
}

void InitThreads::StartThreads()
{
	Worker wrk;
	std::string ufPath = "Test String";
	std::vector<std::future<void>> futures;

	int thNum = 3;
	for (int thCount = 0; thCount < thNum; thCount++)
	{
		futures.emplace_back(std::async(std::launch::async, CallWorkers, thCount, ufPath));
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	for (const std::future<void> &ftr : futures)
		ftr.wait();
}

