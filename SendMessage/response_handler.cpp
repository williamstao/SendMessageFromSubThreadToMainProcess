#pragma once

#include "response_handler.h"

ResponseHandler::ResponseHandler() :m_lpClassName("ClientMsgWndClass"), m_lpWindowName("ClientMsgWnd") {}
ResponseHandler::~ResponseHandler() {}

ResponseHandler* ResponseHandler::GetInstance()
{
	static ResponseHandler* s_obj = NULL;
	if (s_obj == NULL)
	{
		s_obj = new ResponseHandler;
	}
	return s_obj;
}

void ResponseHandler::HandleResponse(int cmd_id, std::string buf)
{
	std::string cmd_buf = buf;
	HWND hWnd = FindWindow(m_lpClassName.c_str(), m_lpWindowName.c_str());
	if (hWnd != NULL)
	{
		COPYDATASTRUCT copyData;
		copyData.dwData = cmd_id;
		if (cmd_buf.length() == 0)
		{
			copyData.cbData = 0;
			copyData.lpData = NULL;
		}
		else
		{
			copyData.cbData = cmd_buf.length() + 1;
			copyData.lpData = (PVOID)cmd_buf.c_str();
		}

		LRESULT ret = ::SendMessage(hWnd, WM_COPYDATA, 0, (LPARAM)&copyData);
		if (ret == 0)
		{
			
		}
	}
	else
	{
		printf("hWnd NULL");
	}
}