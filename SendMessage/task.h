#pragma once
#include<list>
#include<string>
#include "my_thread.h"
#include "lock.h"

class Task : public MyThread
{
public:
	Task(const std::string& filePath);
	~Task();
	void RetrieveRequest(); //run main process
	void ProcRequest();     //run sub process
	
public:     //from MyThread
	virtual void DoRun();
	std::string m_filePath;
};