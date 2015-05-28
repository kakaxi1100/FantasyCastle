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
using namespace std;

int signalTemplet(int signo, void(*func)(int));
	
void catchSignal(int type);

class PUB
{
public:
	
	PUB();
	~PUB();
	
	void setDeamon();

	int socket_create(int port);
	
	void setnonblocking(int fd);

	int acceptSocket(int fd); 

private:
};


#endif
