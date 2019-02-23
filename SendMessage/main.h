#pragma once
#include "IResponseLister.h"
class MainDisPatcher :IResponseLister
{
public:
	MainDisPatcher();
	~MainDisPatcher();
	int onGBoxEngineResponse(int cmd_id, const char* str, uint32_t str_len);
};

