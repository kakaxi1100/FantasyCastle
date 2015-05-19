#ifndef PUB_H
#define PUB_H

void setDeamon();

int socket_create(int port);

void setnonblocking(int fd);

int signalTemplet(int signo, void(*func)(int));

void catchSignal(int type);

int acceptSocket(int fd); 

int recvSocket(int fd);

struct LoginRecvMsg
{
	char* userName;
	char* password;	
};
#endif
