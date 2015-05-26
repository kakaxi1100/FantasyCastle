#ifndef PUB_H
#define PUB_H

#include "byteArray.h"
#include <iostream>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h> 
#include <arpa/inet.h>    
#include <netinet/in.h> 
#include <signal.h>
#include <stdio.h>


void setDeamon();

int socket_create(int port);

void setnonblocking(int fd);

int signalTemplet(int signo, void(*func)(int));

void catchSignal(int type);

int acceptSocket(int fd); 

int recvSocket(int fd);

int handleMsg(unsigned short id, ByteArray &ba, int fd);

struct LoginRecvMsg
{
	char userName[100];
	char password[100];	
};

int verifyUserData(struct LoginRecvMsg &loginRecv, int fd);

#endif
