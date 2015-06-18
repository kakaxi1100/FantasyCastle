#include "work.h"


using namespace std;
Work::Work(int port)
{
	//��÷����socket������ 
	socketfd = pub.socket_create(port);
	if(socketfd == -1)//socket����ʧ�ܳ����˳� 
	{
		exit(-1); 
	}
	pub.setnonblocking(socketfd); //����Ϊ������ 
	
	if(sqlClient.initMySQL(&mysql) == -1)//�����ʼ��mysqlʧ�����˳����� 
	{
		exit(EXIT_FAILURE);
	} 
	
//	if(sqlClient.connectMySQL(&mysql, "192.168.1.254", "liju", "123456", "MYQQDB") !=0 )//�������ݿⲻ�ɹ����˳�  
//    {  
//       exit(EXIT_FAILURE); 
//    }
    
    if(sqlClient.connectMySQL(&mysql, "10.88.52.79", "liju", "123456", "MYQQDB") !=0 )//�������ݿⲻ�ɹ����˳�  
    {  
       exit(EXIT_FAILURE); 
    }
    
    //����sql��� �����ַ��� 
	char sql[50] = {0};
	sprintf(sql,"set names utf8");
	cout<<"sql sentence: " <<sql<<endl;
	sqlClient.sendAndResponseMySQL(&mysql, sql);
}

Work::~Work()
{
	
}

//��ͻ���ƴ����ճ����֪����ô�����Ժ����� 
int Work::recvSocket(int fd)
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
	//������Ϣ�Ǵ�ͷ��ʼ���յ�
	//���粻���ĸ��ֽ� ��֪����ô����������Ҫ�������� 
	cout<< "total::  "<<ba.getBufLen()<<endl;
	if(ba.getBufLen() > 4)//ȡ����Ϣͷ����Ϣ���� 
	{
		len = ba.readUnsignedShort();//ȡ�ó��� 
		cout<<"len:: "<<len<<endl;
		head = ba.readUnsignedShort();//ȡ��Э���
		cout<<"head:: "<<head<<endl;
		
		if( ba.getBufLen() >= len )//����������һ����������Ϣ 
		{		
			cout<<"position is: "<<ba.getPosition() << " available is: "<<ba.getBytesAvailable() << endl;
			handleMsg(head, ba, fd);
		}
 
	}
			
	if(recvSize < 0)    
    {   
    	if(errno == EINTR)//��Ҫ�����ٶ� 
		{
    		cout<<"ERRNO IS EINTR"<<endl;
    		ret = 1;
		}
		else if(errno == EAGAIN)
		{
			cout<<"ERRNO IS EINTR"<<endl;
			ret = 1;	
		}
		else
		{
			cout<<"socket listen failed ! " << strerror(errno) << endl;
       		ret = - 1; 
		}
    }    
    else if(recvSize == 0)//�����˳�
    {   
		cout<<"socket closed failed ! " << strerror(errno) << endl;   
        ret = 0;
		      
    }
	else
	{
    	ret =  1;
	}   

	return ret;
}

int Work::handleMsg(unsigned short id, ByteArray &ba, int fd)
{
	switch(id)
	{
		case 100:
			cout<< "Protocol id: "<< id << endl;
			
			struct LoginRecvMsg loginRecv; 
			memset(&loginRecv, 0, sizeof(loginRecv));
			memcpy(&loginRecv, &ba.buf[ba.getPosition()], sizeof(loginRecv));
			
			cout<<"UserInfo: "<<loginRecv.userID<<"  "<<loginRecv.password<<endl;
			
			ba.plusPosition(sizeof(loginRecv));
			cout<<"position is: "<<ba.getPosition() << " available is: "<<ba.getBytesAvailable() << endl;
			
			verifyUserData(loginRecv, fd);
//			cout<< ba.readUTFBytes(100) << endl;
//			cout<< ba.readUTFBytes(100) << endl;
			break;
		case 200:
			cout<< "Protocol id: "<< id << endl;
			struct RegRecvMsg RegRecv; 
			memset(&RegRecv, 0, sizeof(RegRecv));
			memcpy(&RegRecv, &ba.buf[ba.getPosition()], sizeof(RegRecv));
			
			cout<<"UserInfo: "<<RegRecv.userID<<"  "<<RegRecv.password<<endl;
			
			ba.plusPosition(sizeof(RegRecv));
			cout<<"position is: "<<ba.getPosition() << " available is: "<<ba.getBytesAvailable() << endl;
			
			verifyRegEvent(RegRecv, fd);
			break;
		default:
			cout<<"Unkonwn Protocol " << id << endl; 
			break;
	}
	
	return 0;
}

int Work::verifyRegEvent(struct RegRecvMsg &regRecv, int fd)
{
	//����sql���
	char sql[100] = {0};
	sprintf(sql, "select ID from userinfo where ID=%d", regRecv.userID);
	int result = sqlClient.sendAndResponseMySQL(&mysql, sql); 
	
	struct RegSendMsg regSendMsg;
	memset(&regSendMsg, 0, sizeof(regSendMsg));
	
	regSendMsg.len = sizeof(regSendMsg);
	regSendMsg.protocolID = 201;
	
	if(result > 0)//����������û�����ע��  Ӱ�����������Ϊ1 
	{
		regSendMsg.regType = 1;//ʧ�� 
		cout<<"User register Failure!"<<endl;
	}
	else if(result == 0)//�������������û����ǲ�ѯ����ֳɹ������ע�� 
	{
		regSendMsg.regType = 0;//�ɹ�
		//�����ݿ��в���ֵ 
		memset(sql, 0, sizeof(sql));
		sprintf(sql,"insert userinfo (ID,PW) values (%d, %s)", regRecv.userID, regRecv.password);
		result = sqlClient.sendAndResponseMySQL(&mysql, sql);
		if(result == -2)//��ѯ��ȷ���ҷ��صĽ��ΪNULL 
		{
			cout<<"User register Success!"<<endl;
		}else{
			cout<<"insert User Info. Error!"<<endl;
		}
	}
	else
	{
		cout<<"verifyRegEvent sql error!!"<<endl;
	}
	
	int sendSize = send(fd, &regSendMsg, sizeof(regSendMsg), 0);
	cout << "sendSize: "<<sendSize<<endl;
	
	return 0;
}

int Work::verifyUserData(struct LoginRecvMsg &loginRecv, int fd)
{
	//����sql��� 
	char sql[100] = {0};
	sprintf(sql,"select ID from userinfo where ID=%d", loginRecv.userID);
	int result = sqlClient.sendAndResponseMySQL(&mysql, sql);
	
	struct LoginSendMsg loginSendMsg;
	memset(&loginSendMsg, 0, sizeof(loginSendMsg));
	
	loginSendMsg.len = sizeof(loginSendMsg);
	loginSendMsg.protocolID = 101;
	
	if(result > 0)//���������û� ������ѯ�������Ϊ1�� �򿴿�����Բ��� 
	{	
		memset(sql, 0, sizeof(sql));
		
		sprintf(sql,"select PW from userinfo where PW=%s", loginRecv.password);
		result = sqlClient.sendAndResponseMySQL(&mysql, sql);
		
		if(result > 0)//������ȷ 
		{
			loginSendMsg.loginType = 0;
			cout<<"User Login !!"<<endl;
		}
		else//������� 
		{
			loginSendMsg.loginType = 2;
			cout<<"User Password is Invalid !!"<<endl;	
		} 
	}
	else if(result == 0)
	{
		loginSendMsg.loginType = 1;
		cout<<"User ID is Invalid !!"<<endl;
	}
	else
	{
		cout<<"verifyUserData sql error!!"<<endl;
	}
	
	int sendSize = send(fd, &loginSendMsg, sizeof(loginSendMsg), 0);
	cout << "sendSize: "<<sendSize<<endl;
	
/*	char buf[100] = "hello Ares! Your password is 123465!";
	int sendSize = 0;
	cout<<loginRecv.userName<<" "<<strcmp(loginRecv.userID, "Ares")<<endl;
	if(!strcmp(loginRecv.userName, "Ares") && !strcmp(loginRecv.password, "123456"))
	{
		sendSize = send(fd, buf, sizeof(buf), 0);
		cout << "sendSize:: "<<sendSize<<endl;
	}*/
	return 0;	
}

int getUserPassWordByID(int id)
{
	return 0;
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
                client_skfd = pub.acceptSocket(socketfd);  
                if(client_skfd >= 0)  
                {  
                    ev.data.fd = client_skfd;  
                    ev.events = EPOLLIN | EPOLLERR | EPOLLHUP;  
                    epoll_ctl(epfd, EPOLL_CTL_ADD, client_skfd, &ev);   
                    pub.setnonblocking(client_skfd); //����Ϊ������ 
					continue; 
                }  
            }  
              
            //��������������¼�����ִ��socket_recv   
            if(events[i].events & EPOLLIN)  
            {  
                client_skfd = events[i].data.fd;
                if(recvSocket(client_skfd) <= 0)  
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
