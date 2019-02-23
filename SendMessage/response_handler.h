#pragma once
#include <string>
#include <windows.h>
class ResponseHandler
{
public:
	static ResponseHandler* GetInstance();
private:
	ResponseHandler();
	virtual ~ResponseHandler();
public:
	void HandleResponse(int cmd_id, std::string cmd_buf);
private:
	std::string m_lpClassName;
	std::string m_lpWindowName;
};
