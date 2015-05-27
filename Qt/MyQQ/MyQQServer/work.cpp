#include "work.h"


using namespace std;
Work::Work(int port)
{
	//��÷����socket������ 
	socketfd = socket_create(port);
	if(socketfd == -1)//socket����ʧ�ܳ����˳� 
	{
		exit(-1); 
	}
	setnonblocking(socketfd); //����Ϊ������ 
	
	if(sqlClient.initMySQL(&mysql) == -1)//�����ʼ��mysqlʧ�����˳����� 
	{
		exit(EXIT_FAILURE);
	} 
	
	if(sqlClient.connectMySQL(&mysql, "10.88.52.79", "liju", "123456", "MYQQDB") !=0 )//�������ݿⲻ�ɹ����˳�  
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
	//3������һ�� epll_event �ṹ���������� epoll ���У�ÿ����ѯ����ӳ��м����б仯�� ������
	struct epoll_event ev, events[CLINETCOUNT];
	
	//4������epoll�������� �����ͳص�����һ����, ��ʾ�Զ��ܷŶ����ļ�������   
    int epfd = epoll_create(CLINETCOUNT);  
      
    //5���ѷ���� fd �ӵ�epoll����   
    ev.data.fd = socketfd;  
    ev.events = EPOLLIN | EPOLLERR | EPOLLHUP ;//�����¼�; 
	epoll_ctl(epfd, EPOLL_CTL_ADD, socketfd, &ev);//�ѷ���˵�socket�ӵ�epoll������
	
	int client_skfd = -1;
	//6����ʼ��ѯ   
    while(1)  
    { 
    	cout<<"epoll wait..."<<endl;
		//�������¼�����������������   
        int fd_num = epoll_wait(epfd, events, CLINETCOUNT, -1);//-1 ��ʾһֱ�ȴ�ֱ�����¼�����
		//���󷵻�-1   
        if(fd_num == -1)  
        {  
        	cout<<strerror(errno)<<endl;  
            break;  
        }     
        
        int i;  
        for( i = 0; i < fd_num; i++)  //ѭ������ÿһ�����¼���socket 
        {
        	 //�����Ƿ���˵���������ִ��accept�� ���ҽ��ͻ��˵� ������ ��ӵ�����   
            if(events[i].data.fd == socketfd)  
            {  
                client_skfd = acceptSocket(socketfd);  
                if(client_skfd >= 0)  
                {  
                    ev.data.fd = client_skfd;  
                    ev.events = EPOLLIN | EPOLLERR | EPOLLHUP;  
                    epoll_ctl(epfd, EPOLL_CTL_ADD, client_skfd, &ev);   
                    setnonblocking(client_skfd); //����Ϊ������ 
					continue; 
                }  
            }  
              
            //��������������¼�����ִ��socket_recv   
            if(events[i].events & EPOLLIN)  
            {  
                client_skfd = events[i].data.fd;
                if(recvSocket(client_skfd) < 0)  
                {  
                	userLogout(client_skfd);
                    close(client_skfd);  
                }  
            }  
            //����Ǵ����¼�����ִ�� close   
            if(events[i].events & EPOLLERR)  
            {  
            	client_skfd = events[i].data.fd;  
            	userLogout(client_skfd);
                close(client_skfd);  
            }  
            //����ǹ����¼��� ��ִ��close   
            if(events[i].events & EPOLLHUP)  
            {  
            	client_skfd = events[i].data.fd;  
            	userLogout(client_skfd);
                close(client_skfd);  
            }  
        }
	} 
	//7��ѭ�������ر�epoll ��epoll �������������Ҫ��close�ر�   
    close(epfd); 
    close(socketfd);
}
