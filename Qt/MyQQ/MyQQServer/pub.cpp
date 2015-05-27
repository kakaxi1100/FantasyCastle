#include "pub.h"


using namespace std;

unsigned short head = 0;

unsigned short len = 0;

unsigned char buf[4] = {0};//存消息头和消息长度 

bool parseOver = false;

void setDeamon()
{
	//1、创建孤儿进程
	pid_t pid, sid;
	
	pid = fork();//创建一个新的子进程 
	
	if(pid < 0)
	{
		cout<<"创建进程失败: " << strerror(errno) << endl; 
		exit(EXIT_FAILURE);
	}
	
	if(pid > 0)//处理父进程 
	{
		exit(EXIT_SUCCESS);//父进程直接退出 
	}
	//2、处理子进程 
	sid = setsid();
	if(sid < 0)
	{
		cout<<"setid 失败: " << strerror(errno) << endl; 
		exit(EXIT_FAILURE);
	}
	/*chdir("/");//改变工作目录，避免造成其它目录无法卸载  
    umask(0);//更改操作 
    //关闭不必要的文件描述符  
    close(STDIN_FILENO); 
    close(STDOUT_FILENO); 
    close(STDERR_FILENO);*/   
}

//先创建服务端的socket   
int socket_create(int port)  
{  
    //1,创建SOCKET   
    int sockfd  = socket(AF_INET, SOCK_STREAM, 0);  
    if(sockfd == -1)  
    {  
    	cout<<"socket create failed !" << strerror(errno) << endl; 
        return -1;  
    }  
      
    //2, 断开再连接无需等待，具体查看博客 操作记录 8   
    int opt = 1;    
    if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)    
    {    
    	cout<<"setsockopt failed !" << strerror(errno) << endl;
        return -1;    
    }   
      
    //3, 绑定端口和IP  
    struct sockaddr_in  addr;    
    addr.sin_family = AF_INET;    
    addr.sin_port = htons(port);    
    addr.sin_addr.s_addr = htonl(INADDR_ANY);       
        
    if(bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) == -1)    
    {    
    	cout<<"socket bind failed !" << strerror(errno) << endl;   
        return -1;    
    }     
      
    //4, 开始侦听  
    if(listen(sockfd, 100) == -1)  
    {  
    	cout<<"socket listen failed !" << strerror(errno) << endl;   
        return -1;  
    }  
      
    return sockfd;   
}

//创建非阻塞  
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
 
 //侦听信号函数模板 
int signalTemplet(int signo, void(*func)(int))//固定格式   
{  
    struct sigaction act, oldact;  
    act.sa_handler = func;  
    sigemptyset(&act.sa_mask);  
    act.sa_flags = 0;  
    return sigaction(signo, &act, &oldact);  
} 

//捕捉信号函数模板 
void catchSignal(int type)  
{  
	//捕获它们不让这些信号造成程序退出 
    switch(type)  
    {  
        case SIGINT:  
            break;
		case SIGPIPE:
			break;  
    }  
} 

//接收来自客户端的ID 
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

//多客户端拼包和粘包不知道怎么处理。以后解决。 
int recvSocket(int fd)
{
	ByteArray ba;
	int ret = 0;
	
	int recvSize = -1; 
	unsigned int totalRecv = 0;
	
	do
	{
		recvSize = recv(fd, ba.buf, sizeof(ba.buf), 0);
		cout << "recvSize:: "<<recvSize<<endl;
		if(recvSize > 0)
		{	
			totalRecv += recvSize;
		}
		ba.setBytesAvailable(totalRecv);
		ba.setBufLen(totalRecv);
		
	}while(recvSize > 0);
	//假如消息是从头开始接收的
	//假如不足四个字节 则不知道怎么处理，所以先要缓存起来 
	cout<< "total::  "<<ba.getBufLen()<<endl;
	if(ba.getBufLen() > 4)//取得消息头和消息长度 
	{
		len = ba.readUnsignedShort();//取得长度 
		cout<<"len:: "<<len<<endl;
		head = ba.readUnsignedShort();//取得协议号
		cout<<"head:: "<<head<<endl;
		
		if( ba.getBufLen() >= len )//包含了至少一条完整的消息 
		{		
			cout<<"position is: "<<ba.getPosition() << " available is: "<<ba.getBytesAvailable() << endl;
			handleMsg(head, ba, fd);
		}
 
	}
			
	if(recvSize == -1)    
    {   
    	if(errno == EINTR)//还要继续再读 
		{
    		cout<<"ERRNO IS EINTR"<<endl;
    		ret = 0;
		}
		else if(errno == EAGAIN)
		{
			cout<<"ERRNO IS EINTR"<<endl;
			ret = 0;	
		}
		else
		{
			cout<<"socket listen failed ! " << strerror(errno) << endl;
       		ret = - 1; 
		}
    }    
    else if(recvSize == 0)//正常退出
    {   
		cout<<"socket closed failed ! " << strerror(errno) << endl;   
        ret = -1;      
    }   

	return ret;
}

int handleMsg(unsigned short id, ByteArray &ba, int fd)
{
	switch(id)
	{
		case 100:
			cout<< "Protocol id: "<< id << endl;
			struct LoginRecvMsg loginRecv; 
			memset(&loginRecv, 0, sizeof(loginRecv));
			memcpy(&loginRecv, &ba.buf[ba.getPosition()], sizeof(loginRecv));
			cout<<loginRecv.userName<<endl;
			cout<<loginRecv.password<<endl;
			cout<<"position is: "<<ba.getPosition() << " available is: "<<ba.getBytesAvailable() << endl;
			verifyUserData(loginRecv, fd);
//			cout<< ba.readUTFBytes(100) << endl;
//			cout<< ba.readUTFBytes(100) << endl;
			break;
		default:
			cout<<"Unkonwn Protocol " << id << endl; 
			break;
	}
	
	return 0;
}

int verifyUserData(struct LoginRecvMsg &loginRecv, int fd)
{
	char buf[100] = "hello Ares! Your password is 123465!";
	int sendSize = 0;
	cout<<loginRecv.userName<<" "<<strcmp(loginRecv.userName, "Ares")<<endl;
	if(!strcmp(loginRecv.userName, "Ares") && !strcmp(loginRecv.password, "123456"))
	{
		sendSize = send(fd, buf, sizeof(buf), 0);
		cout << "sendSize:: "<<sendSize<<endl;
	}
	return 0;	
}
/*//接收消息    
int recvSocket(int fd)    
{      
    struct LoginRecvMsg loginRecv;   
    int ret = 0;   
    memset(&loginRecv, 0, sizeof(loginRecv));      
//    int retrecv = recv(fd, &loginRecv, sizeof(loginRecv), 0);
	int a; 
    int retrecv = recv(fd, &a, sizeof(a), 0); 
    int count = 0;
	while(retrecv > 0)
	{
		retrecv = recv(fd, &a, sizeof(a), 0); 
		count++;
		cout<<"a is:: "<<a<<endl;
		cout<<retrecv<<" "<<count<<endl;
//		memset(buf, 0, sizeof(buf)); 
	}
	cout<<"recv length:: " << retrecv <<endl;
	 
    if(retrecv == -1)    
    {   
    	cout<<"socket listen failed ! " << strerror(errno) << endl;
        ret = - 1;      
    }    
    else if(retrecv == 0)//正常退出     
    {   
		cout<<"socket closed failed ! " << strerror(errno) << endl;   
        ret = -1;      
    }    
    else    
    {    
//    	cout<<a<<endl;
//    	cout<<loginRecv.protoclID<<" "<<loginRecv.userName<<" "<<loginRecv.password<< endl;
    }     
    return ret;       
} */
