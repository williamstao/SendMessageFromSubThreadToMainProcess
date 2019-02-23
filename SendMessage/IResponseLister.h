#pragma once
#include <stdint.h>
class IResponseLister
{
public:
	virtual int onGBoxEngineResponse(int cmd_id, const char* str, uint32_t str_len) = 0; 
};
