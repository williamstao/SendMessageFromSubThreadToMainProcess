#pragma once
#include <mutex> 
class MutexLock
{
public:
	MutexLock();
	~MutexLock();
public:
	void Lock();
	void UnLock();
private:
	std::mutex m_mutexLock;
};

class Guard
{
public:
	Guard(MutexLock&);
	~Guard();
private:
	MutexLock& m_lock;
};
