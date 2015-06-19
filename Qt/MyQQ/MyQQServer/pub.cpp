#include "pub.h"

PUB::PUB()
{

}

PUB::~PUB()
{
	
}

void PUB::setDeamon()
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
int PUB::socket_create(int port)  
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
 void PUB::setnonblocking(int fd)  
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
	//�������ǲ�����Щ�ź���ɳ����˳� 
    switch(type)  
    {  
        case SIGINT:  
            break;
		case SIGPIPE:
			break;  
    }  
} 

//�������Կͻ��˵�ID 
int PUB::acceptSocket(int fd)  
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

int PUB::parseJason(string obj)
{
	if(obj.at(0) != '{' || obj.at(obj.length()-1) != '}')
	{
		cout<<"Jason format error! " << obj << endl;
		return -1;
	}
	
	return 0;
}

/*//������Ϣ    
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
    else if(retrecv == 0)//�����˳�     
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
