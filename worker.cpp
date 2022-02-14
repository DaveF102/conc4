#include <iostream>
#include <thread>
#include <memory>
#include "worker.h"

void Worker::InitWorker(int num, std::string ufPath)
{
	float initf = 10.0f;
	SharedVar sv;
	SharedStruct ss;
	while (true)
	{
		if (num == 0)
		{
			initf = initf + 0.001f;
			ss.vx = initf;
			sv.SetSS(ss);
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
		else
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			ss = sv.GetSS();
			std::cout << "Thread: " << std::this_thread::get_id() << ", num = " << num  << ", vx = " << ss.vx  << std::endl;
		}
	}
}
