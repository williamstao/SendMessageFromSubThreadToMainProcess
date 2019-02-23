#pragma once
#include "lock.h"
#include <windows.h>
class MyThread
{
public:
	MyThread();
	virtual ~MyThread();

public:
	int Start();
	void Stop();
	bool IsRunning() const;

public:
	virtual void DoRun() = 0;

private:
	static DWORD WINAPI thread_func(void* lpParam);

protected:
	bool m_IsRunning;
	bool m_NeedStop;

	MutexLock m_BaseLock;
};
