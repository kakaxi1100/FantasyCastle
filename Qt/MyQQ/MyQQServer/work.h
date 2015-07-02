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
#include "globalData.h"
#include <unordered_map>
#include <memory>

#define CLINETCOUNT 100


class Work
{
public:
	Work(int port);
	~Work();
	
	void run();
	int userLogout(int clientSd);
	
	unordered_map<unsigned int, shared_ptr<ClientInfo>> clients;
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
	int verifyRegEvent(struct RegRecvMsg &regRecv, int fd);
	int sendFriendList(struct FriendListRecvMsg &firendListRecv, int fd);
};

#endif
