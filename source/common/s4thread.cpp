// #include "stdafx.h"

#include "common/s4thread.h"
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
// #include "logger/logger.h"

namespace S4 {

	bool thread_spawn(THREAD_START_ROUTINE func, void* var, thread_id& thread)
	{
#ifdef _MSC_VER
		thread_id result = 0;
		unsigned int id = 0;
		result = _beginthreadex(NULL, 0, func, var, 0, &id);
		if (result == 0) return false;
#else
		thread_id result = 0;
		if (pthread_create(&result, 0, func, var) != 0) return false;
#endif
		thread = result;
		return true;
	}

	bool thread_spawn(THREAD_START_ROUTINE func, void* var)
	{
		thread_id thread = 0;
		return thread_spawn(func, var, thread);
	}

	void thread_join(thread_id thread)
	{
#ifdef _MSC_VER
		WaitForSingleObject((void*)thread, INFINITE);
		CloseHandle((HANDLE)thread);
#else
		pthread_join((pthread_t)thread, 0);
#endif
	}

	void thread_detach(thread_id thread)
	{
#ifdef _MSC_VER
		CloseHandle((HANDLE)thread);
#else
		pthread_t t = thread;
		pthread_detach(t);
#endif
	}

	thread_id thread_self()
	{
#ifdef _MSC_VER
		return (thread_id)GetCurrentThread();
#else
		return pthread_self();
#endif
	}

	void process_sleep(double s)
	{
#ifdef _MSC_VER
		Sleep((long)(s * 1000));
#else
		timespec time, remainder;
		double intpart;
		time.tv_nsec = (long)(modf(s, &intpart) * 1e9);
		time.tv_sec = (int)intpart;
		while (nanosleep(&time, &remainder) == -1)
			time = remainder;
#endif
	}

	//////////////////////////////////////////////////
	static Mutex chins_global_mutex;

	Locker::Locker(bool verbose) :
		m_mutex(chins_global_mutex)
	{
		if (verbose){
			// WARN("call Locker() without mutex input: using global_mutex!\n");
			std::cerr << "Call Locker() without mutex input: using global_mutex!" << std::endl;
		}
	}




void myYield(void){
#if defined(__APPLE__) || defined(__CYGWIN__)
    sched_yield();
#elif defined(unix) || defined(__unix) || defined(__unix__)
    pthread_yield();
#elif defined(_WIN32) || defined(_WIN64)
    SwitchToThread();
#endif
}





}