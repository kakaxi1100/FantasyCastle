#include "pub.h"
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

using namespace std;

void setDeamon()
{
	//1�������¶�����
	pid_t pid, sid;
	
	pid = fork();//����һ���µ��ӽ��� 
	
	if(pid < 0)
	{
		cout<<"��������ʧ��: " << strerror(errno) << endl; 
		exit(EXIT_FAILURE);
	}
	
	if(pid > 0)//�������� 
	{
		exit(EXIT_SUCCESS);//������ֱ���˳� 
	}
	//2�������ӽ��� 
	sid = setsid();
	if(sid < 0)
	{
		cout<<"setid ʧ��: " << strerror(errno) << endl; 
		exit(EXIT_FAILURE);
	}
	/*chdir("/");//�ı乤��Ŀ¼�������������Ŀ¼�޷�ж��  
    umask(0);//���Ĳ��� 
    //�رղ���Ҫ���ļ�������  
    close(STDIN_FILENO); 
    close(STDOUT_FILENO); 
    close(STDERR_FILENO);*/   
}

//�ȴ�������˵�socket   
int socket_create(int port)  
{  
    //1,����SOCKET   
    int sockfd  = socket(AF_INET, SOCK_STREAM, 0);  
    if(sockfd == -1)  
    {  
    	cout<<"socket create failed !" << strerror(errno) << endl; 
        return -1;  
    }  
      
    //2, �Ͽ�����������ȴ�������鿴���� ������¼ 8   
    int opt = 1;    
    if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)    
    {    
    	cout<<"setsockopt failed !" << strerror(errno) << endl;
        return -1;    
    }   
      
    //3, �󶨶˿ں�IP  
    struct sockaddr_in  addr;    
    addr.sin_family = AF_INET;    
    addr.sin_port = htons(port);    
    addr.sin_addr.s_addr = htonl(INADDR_ANY);       
        
    if(bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) == -1)    
    {    
    	cout<<"socket bind failed !" << strerror(errno) << endl;   
        return -1;    
    }     
      
    //4, ��ʼ����  
    if(listen(sockfd, 100) == -1)  
    {  
    	cout<<"socket listen failed !" << strerror(errno) << endl;   
        return -1;  
    }  
      
    return sockfd;   
}

//����������  
 void setnonblocking(int fd)  
 {  
    int opts = fcntl(fd, F_GETFL);  
    if(opts < 0)  
    {  
    	cout<<"fcntl failed !" << strerror(errno) << endl;   
    }  
      
    opts = opts | O_NONBLOCK;  
    if(fcntl(fd, F_SETFL, opts) < 0)  
    {  
    	cout<<"fcntl failed !" << strerror(errno) << endl; 
    }  
 } 
 
 //�����źź���ģ�� 
int signalTemplet(int signo, void(*func)(int))//�̶���ʽ   
{  
    struct sigaction act, oldact;  
    act.sa_handler = func;  
    sigemptyset(&act.sa_mask);  
    act.sa_flags = 0;  
    return sigaction(signo, &act, &oldact);  
} 

//��׽�źź���ģ�� 
void catchSignal(int type)  
{  
    switch(type)  
    {  
        case SIGINT:  
            break;
		case SIGPIPE:
			break;  
    }  
} 

//�������Կͻ��˵�ID 
int acceptSocket(int fd)  
{  
    struct sockaddr_in client_addr;    
    socklen_t client_socklen = sizeof(client_addr);
	memset(&client_addr, 0 , sizeof(client_addr));    
    int client_sockfd = accept(fd, (struct sockaddr*)&client_addr, &client_socklen);    
    if(client_sockfd == -1)    
    {   
    	cout<<"socket accept failed ! "<< strerror(errno) <<endl;
    }else{
    	cout << "client IP :" << inet_ntoa(client_addr.sin_addr) << endl;
	}  
    return client_sockfd;    
}

//������Ϣ    
int recvSocket(int fd)    
{      
    return 0;    
} 
