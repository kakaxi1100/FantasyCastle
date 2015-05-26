#ifndef WORK_H
#define WORK_H

#include "pub.h"
#include <cstdlib>
#include <iostream>
#include <sys/epoll.h>
#include <string.h>
#include <errno.h>

#define CLINETCOUNT 100

class Work
{
public:
	Work(int port);
	~Work();
	
	void run();
	int userLogout(int clientSd);
private:
	int socketfd;
};

#endif
