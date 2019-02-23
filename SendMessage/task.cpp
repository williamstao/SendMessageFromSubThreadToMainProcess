#pragma once
#include "task.h"
#include "md5.h"
#include "response_handler.h"
Task::Task(const std::string& filePath) : m_filePath("")
{
	m_filePath = filePath;
}

Task::~Task()
{

}

void Task::RetrieveRequest()
{
	Start();
}

void Task::DoRun()
{
	ProcRequest();
}

void Task::ProcRequest()
{
	std::string filePath = m_filePath;
	std::string info = "";
	int err = GetFileMd5Wrapper(filePath.c_str(), info);
	
	filePath.append(" get md5 ");
	filePath.append(info);
	filePath.append(" at thread ");
	filePath.append(std::to_string(GetCurrentThreadId()));

	if (err != 0)
	{
		ResponseHandler::GetInstance()->HandleResponse(-1, filePath.c_str());
	}
	else
	{
		ResponseHandler::GetInstance()->HandleResponse(0, filePath.c_str());
	}
}
