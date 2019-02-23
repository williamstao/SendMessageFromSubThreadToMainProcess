#pragma once
#include "message_engine.h"

ClientEngine::ClientEngine()
{
}
ClientEngine::~ClientEngine() {}

ClientEnginePtr ClientEngine::GetInstance()
{
	static ClientEnginePtr obj(new ClientEngine());
	return obj;
}

int ClientEngine::registResponseListener(IResponseLister* listener)
{
	Guard guard(m_Lock);
	if (listener == NULL)
	{
		return -1;
	}

	std::list<IResponseLister*>::iterator it;
	for (it = m_response_list.begin(); it != m_response_list.end();)
	{
		if (*it == listener)
		{
			m_response_list.erase(it++);
		}
		else
		{
			it++;
		}
	}
	m_response_list.push_back(listener);
	return 0;
}

int ClientEngine::unregistResponseListener(IResponseLister* listener)
{
	Guard guard(m_Lock);
	if (listener == NULL)
	{
		return -1;
	}

	std::list<IResponseLister*>::iterator it;
	for (it = m_response_list.begin(); it != m_response_list.end();)
	{
		if (*it == listener)
		{
			m_response_list.erase(it++);
		}
		else
		{
			it++;
		}
	}
	return 0;
}

int ClientEngine::doClientEngineResponse(int cmd_id, const char* cmd_buf, uint32_t cmd_buf_len)
{
	std::list<IResponseLister*>::iterator it;
	for (it = m_response_list.begin(); it != m_response_list.end(); it++)
	{
		IResponseLister* listener = *it;
		listener->onGBoxEngineResponse(cmd_id, cmd_buf, cmd_buf_len);
	}
	return 0;
}

void ClientEngine::doClientEngineResponseOnMainThread(std::weak_ptr<ClientEngine> host, int cmd_id, const uint8_t* cmd_buf, uint32_t cmd_buf_len)
{
	std::shared_ptr<ClientEngine> client = host.lock();
	if (client.get() == NULL)
	{
		return;
	}
	client->doClientEngineResponse(cmd_id, (const char*)cmd_buf, cmd_buf_len);
}

int ClientEngine::InitApp(std::shared_ptr<MsgWnd> msgWnd)
{
	msgWnd->SetHandler(std::bind(&self::doClientEngineResponseOnMainThread, shared_from_this(), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	m_msgWnd = msgWnd;
	return 0;
}