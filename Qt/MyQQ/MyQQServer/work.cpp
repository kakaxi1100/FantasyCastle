#include "work.h"


using namespace std;
Work::Work(int port)
{
	//获得服务端socket描述符 
	socketfd = socket_create(port);
	if(socketfd == -1)//socket创建失败程序退出 
	{
		exit(-1); 
	}
	setnonblocking(socketfd); //设置为非阻塞 
	
	if(sqlClient.initMySQL(&mysql) == -1)//如果初始化mysql失败则退出程序 
	{
		exit(EXIT_FAILURE);
	} 
	
	if(sqlClient.connectMySQL(&mysql, "10.88.52.79", "liju", "123456", "MYQQDB") !=0 )//链接数据库不成功就退出  
    {  
       exit(EXIT_FAILURE); 
    }
}

Work::~Work()
{
	
}

int Work::userLogout(int clientSd)
{
	return 0;
}

void Work::run()
{
	//3、声明一个 epll_event 结构，用来放入 epoll 池中，每次轮询都会从池中加入有变化的 描述符
	struct epoll_event ev, events[CLINETCOUNT];
	
	//4、创建epoll的描述符 数量和池的数量一样大, 表示对多能放多少文件描述符   
    int epfd = epoll_create(CLINETCOUNT);  
      
    //5、把服务端 fd 加到epoll池中   
    ev.data.fd = socketfd;  
    ev.events = EPOLLIN | EPOLLERR | EPOLLHUP ;//设置事件; 
	epoll_ctl(epfd, EPOLL_CTL_ADD, socketfd, &ev);//把服务端的socket加到epoll池中来
	
	int client_skfd = -1;
	//6、开始轮询   
    while(1)  
    { 
    	cout<<"epoll wait..."<<endl;
		//返回有事件的描述符的总数量   
        int fd_num = epoll_wait(epfd, events, CLINETCOUNT, -1);//-1 表示一直等待直到有事件到来
		//错误返回-1   
        if(fd_num == -1)  
        {  
        	cout<<strerror(errno)<<endl;  
            break;  
        }     
        
        int i;  
        for( i = 0; i < fd_num; i++)  //循环处理每一个来事件的socket 
        {
        	 //假如是服务端的描述符则执行accept， 并且将客户端的 描述符 添加到池中   
            if(events[i].data.fd == socketfd)  
            {  
                client_skfd = acceptSocket(socketfd);  
                if(client_skfd >= 0)  
                {  
                    ev.data.fd = client_skfd;  
                    ev.events = EPOLLIN | EPOLLERR | EPOLLHUP;  
                    epoll_ctl(epfd, EPOLL_CTL_ADD, client_skfd, &ev);   
                    setnonblocking(client_skfd); //设置为非阻塞 
					continue; 
                }  
            }  
              
            //如果来的是输入事件，则执行socket_recv   
            if(events[i].events & EPOLLIN)  
            {  
                client_skfd = events[i].data.fd;
                if(recvSocket(client_skfd) < 0)  
                {  
                	userLogout(client_skfd);
                    close(client_skfd);  
                }  
            }  
            //如果是错误事件，则执行 close   
            if(events[i].events & EPOLLERR)  
            {  
            	client_skfd = events[i].data.fd;  
            	userLogout(client_skfd);
                close(client_skfd);  
            }  
            //如果是挂起事件， 则执行close   
            if(events[i].events & EPOLLHUP)  
            {  
            	client_skfd = events[i].data.fd;  
            	userLogout(client_skfd);
                close(client_skfd);  
            }  
        }
	} 
	//7、循环结束关闭epoll ，epoll 描述符用完后需要用close关闭   
    close(epfd); 
    close(socketfd);
}
