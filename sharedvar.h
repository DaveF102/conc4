//sharedvar.h
#ifndef SHAREDVAR_H
#define SHAREDVAR_H

#include <string>
#include <vector>
#include <future>
#include <mutex>
#include <deque>
#include <condition_variable>
#include "worker.h"

template <class T>
class MessageQueue
{
public:
	// constructor / destructor
	MessageQueue() {}

	// typical behavior methods
	void send(T &&msg);
	T receive();

private:
	std::deque<T> _queue;
	std::condition_variable _cond;
	std::mutex _mutex;
};

struct SharedStruct
{
	SharedStruct () : vx { -45.0f }, vy { 80.0f }, z { 1.0f }, t {1.0f, 2.0f, 3.0f} {}
	float vx;
	float vy;
	float z;
	float t[3];
};

class SharedVar
{
public:
	// Constructor

	// Getters and setters
	void SetSS(SharedStruct ss);
	SharedStruct GetSS();

	// Other methods

private:
	// Private member variables
	SharedStruct _ss;
	MessageQueue<SharedStruct> _fmq;
};

class InitThreads
{
public:
	void StartThreads();
	static void CallWorkers(int thn, std::string ufP);

private:
	SharedVar _sv;
};

#endif