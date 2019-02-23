#pragma once
#include "main.h"
#include "message_engine.h"
MainDisPatcher::MainDisPatcher()
{
	ClientEngine::GetInstance()->registResponseListener(this);
}

MainDisPatcher::~MainDisPatcher()
{
	ClientEngine::GetInstance()->unregistResponseListener(this);
}

int MainDisPatcher::onGBoxEngineResponse(int cmd_id, const char* str, uint32_t str_len)
{
	printf("%s\n", str);
	return 0;
}