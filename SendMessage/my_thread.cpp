#include "my_thread.h"
#include <windows.h>
MyThread::MyThread() :m_IsRunning(false), m_NeedStop(false)
{

}

MyThread::~MyThread()
{

}

int MyThread::Start()
{
	if (!m_IsRunning)
	{
		Guard guard(m_BaseLock);

		if (!m_IsRunning)
		{
			m_IsRunning = true;
			m_NeedStop = false;

			HANDLE  hwd = CreateThread(NULL, 0, MyThread::thread_func, this, 0, NULL);
			if (hwd == NULL)
			{
				printf("CreateThread failed\n");
				return -1;
			}
		}
	}
	return 0;
}

void MyThread::Stop()
{
	Guard guard(m_BaseLock);
	m_NeedStop = true;
}

bool MyThread::IsRunning() const
{
	return m_IsRunning;
}

DWORD WINAPI MyThread::thread_func(void* lpParam)
{
	MyThread* This = (MyThread *)lpParam;
	This->DoRun();
	This->m_IsRunning = false;

	return NULL;
}