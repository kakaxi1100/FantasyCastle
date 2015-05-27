#ifndef WORK_H
#define WORK_H

#include "pub.h"
#include <cstdlib>
#include <iostream>
#include <sys/epoll.h>
#include <string.h>
#include <errno.h>
#include "clientsql.h"
#include "byteArray.h"


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
	
	PUB pub;
	MYSQL mysql;
	ClientSQL sqlClient;
	
		
	unsigned short head;
	unsigned short len;
		
	int recvSocket(int fd);
	int handleMsg(unsigned short id, ByteArray &ba, int fd);
	int verifyUserData(struct LoginRecvMsg &loginRecv, int fd);
	
	int getUserPassWordByID(int id);
};

#endif
