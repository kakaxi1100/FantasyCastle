#include "clientinfo.h"

ClientInfo::ClientInfo()
{
	int i = 0;
	int len = sizeof(friends)/sizeof(friends[0]);
	for(; i < len; i++)
	{
		friends[i] = 0;
	}
}

ClientInfo::~ClientInfo()
{
	
}
