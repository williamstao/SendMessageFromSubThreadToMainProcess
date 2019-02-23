#pragma once
#include "lock.h"
MutexLock::MutexLock()
{

}

MutexLock::~MutexLock()
{

}

void MutexLock::Lock()
{
	m_mutexLock.lock();
}

void MutexLock::UnLock()
{
	m_mutexLock.unlock();
}

Guard::Guard(MutexLock& lock) :m_lock(lock)
{
	m_lock.Lock();
}

Guard::~Guard()
{
	m_lock.UnLock();
}


