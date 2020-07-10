
#pragma once

#ifdef _MSC_VER
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <process.h>
#else
#include <pthread.h>
#endif

#include <atomic>

#define CD_SET_EC(ec, en) {if(ec) *((int*)(ec)) = (int)(en);}

namespace S4 {

#if(_MSC_VER >= 1900)
	typedef _beginthreadex_proc_type THREAD_START_ROUTINE;
#define THREAD_PROC unsigned int _stdcall
#elif(_MSC_VER > 0)
	typedef unsigned int(_stdcall * THREAD_START_ROUTINE)(void *);
#define  THREAD_PROC unsigned int _stdcall
#else
	extern "C" { typedef void * (THREAD_START_ROUTINE)(void *); }
#define THREAD_PROC void *
#endif

#ifdef _MSC_VER
#ifdef _WIN64
	typedef unsigned __int64  thread_id;
#else
	typedef unsigned int thread_id;
#endif
#else
	typedef pthread_t thread_id;
#endif

bool thread_spawn(THREAD_START_ROUTINE func, void* var, thread_id& thread);
bool thread_spawn(THREAD_START_ROUTINE func, void* var);
void thread_join(thread_id thread);
void thread_detach(thread_id thread);
thread_id thread_self();

//min-precision: ms in windows, ns in linux
void process_sleep(double seconds);



/// Portable implementation of a mutex.
class Mutex
{
public:
	Mutex()
	{
#ifdef _MSC_VER
		InitializeCriticalSection(&m_mutex);
#else
		m_count = 0;
		m_threadID = 0;
		//pthread_mutexattr_t attr;
		//pthread_mutexattr_init(&attr);
		//pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
		//pthread_mutex_init(&m_mutex, &attr);
		pthread_mutex_init(&m_mutex, 0);
#endif
	}

	~Mutex()
	{
#ifdef _MSC_VER
		DeleteCriticalSection(&m_mutex);
#else
		pthread_mutex_destroy(&m_mutex);
#endif
	}

	void lock()
	{
#ifdef _MSC_VER
		EnterCriticalSection(&m_mutex);
#else
		if (m_count && m_threadID == pthread_self())
		{
			++m_count; return;
		}
		pthread_mutex_lock(&m_mutex);
		++m_count;
		m_threadID = pthread_self();
#endif
	}

	void unlock()
	{
#ifdef _MSC_VER
		LeaveCriticalSection(&m_mutex);
#else
		if (m_count > 1)
		{
			m_count--; return;
		}
		--m_count;
		m_threadID = 0;
		pthread_mutex_unlock(&m_mutex);
#endif
	}

private:

#ifdef _MSC_VER
	CRITICAL_SECTION m_mutex;
#else
	pthread_mutex_t m_mutex;
	pthread_t m_threadID;
	int m_count;
#endif
};

/// Locks/Unlocks a mutex using RAII.
class Locker
{
public:
	//Locker l(v);	//make a Mutex v for threads to share before call Locker l(v)!
	Locker(Mutex& mutex)
		: m_mutex(mutex)
	{
		m_mutex.lock();
	}

	~Locker()
	{
		m_mutex.unlock();
	}

	Locker(bool verbose = true);//use global mutex!
private:
	Mutex& m_mutex;
};

/// Does the opposite of the Locker to ensure mutex ends up in a locked state.
class ReverseLocker
{
public:
	ReverseLocker(Mutex& mutex)
		: m_mutex(mutex)
	{
		m_mutex.unlock();
	}

	~ReverseLocker()
	{
		m_mutex.lock();
	}
private:
	Mutex& m_mutex;
};



class thread_runner_t
{
public:
	thread_runner_t(){};
	virtual ~thread_runner_t() {
		stop();
	}

	enum ec_t{
		DUAL_START = 1,
		SPAWN_FAIL,
		MAIN_RUN_ENTRY,
	};

	virtual bool restart(int* ec = nullptr) {
		if (!stop())
			return false;
		if (!start(ec))
			return false;
		return true;
	}
	
	virtual bool start(int* ec = nullptr){
		if(th_id){
			CD_SET_EC(ec, DUAL_START)
			return false;	//dual start
		}
		_stop = false;
		if(!thread_spawn(&run_body, this, th_id)){
			//report error
			th_id = 0;
			CD_SET_EC(ec, SPAWN_FAIL)
			return false;
		}
		process_sleep(0.001);	//wait 1ms ...
		return true;
	}

	virtual bool stop(){
		if(!th_id)
			return true;

		_stop = true;
		thread_join(th_id);
		th_id = 0;
		return true;
	}

	bool isRunning() {
		return _isRunning;
	}

	bool get_stop(){
		return _stop;
	}

	int get_last_ec(){
		return _last_ec;
	}
	
private:
	std::atomic_bool _isRunning = ATOMIC_VAR_INIT(false);
	std::atomic_bool _stop = ATOMIC_VAR_INIT(false);
protected:
	//true: goto main run loop
	//false: error and stop thread
	virtual bool pre_main_run_loop_act(int* ec = nullptr)
	{
		if (ec != nullptr) {
			*ec = 0;
		}
		return true;
	}
	//true: keep running
	//false: error and break main_run
	virtual bool main_run_loop_act(int* ec = nullptr)
	{
		if (ec != nullptr) {
			*ec = 0;
		}

		//do something here
		process_sleep(0.001);	

		return true;
	}

	virtual void post_main_run_loop_act(int* ec = nullptr)
	{
		if (ec != nullptr) {
			*ec = 0;
		}
	}

private:
	void main_run(void)
	{
		_last_ec = (int)MAIN_RUN_ENTRY;
		_isRunning = true;
		if (!pre_main_run_loop_act(&_last_ec)) {
			_isRunning = false;
			return;
		}

		while(!_stop){
			if(!main_run_loop_act(&_last_ec))
				break;
		}

		_isRunning = false;

		//auto clean
		thread_detach(thread_self());
		th_id = 0;
	}

private:
	thread_id th_id = 0;

	int _last_ec = 0;

	static THREAD_PROC run_body(void* arg){ //static is necessary.
		thread_runner_t * host = static_cast<thread_runner_t*>(arg);
		host->main_run();
		return 0;
	}

};

void myYield(void);

}

