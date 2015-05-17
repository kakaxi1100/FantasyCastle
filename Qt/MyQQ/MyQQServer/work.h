#ifndef WORK_H
#define WORK_H

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
