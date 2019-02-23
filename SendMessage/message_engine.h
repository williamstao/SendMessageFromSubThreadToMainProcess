#pragma once
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <list>
#include "lock.h"
#include "IResponseLister.h"
#include "msg_wnd.h"

class ClientEngine;
typedef std::shared_ptr<ClientEngine> TPClientEnginePtr;
class ClientEngine : public std::enable_shared_from_this<ClientEngine>
{
	typedef ClientEngine self;
public:
	ClientEngine();
	~ClientEngine();
	static TPClientEnginePtr GetInstance();
	int registResponseListener(IResponseLister* listener);
	int unregistResponseListener(IResponseLister* listener);
	int doClientEngineResponse(int cmd_id, const char* cmd_buf, uint32_t cmd_buf_len);
	static void doClientEngineResponseOnMainThread(std::weak_ptr<ClientEngine> host, int cmd_id, const uint8_t* cmd_buf, uint32_t cmd_buf_len);
	int InitApp(std::shared_ptr<MsgWnd> msgWnd);
private:
	MutexLock m_Lock;
	std::list<IResponseLister*> m_response_list;
	std::shared_ptr<MsgWnd> m_msgWnd;
};
