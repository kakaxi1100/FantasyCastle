#include "work.h"
#include <sstream>
#include <stdexcept>

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
    
    if(sqlClient.connectMySQL(&mysql, "10.88.52.88", "liju", "123456", "MYQQDB") !=0 )//�������ݿⲻ�ɹ����˳�  
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

bool Work::isPlayerOnLine(unsigned int id)
{
//----3.��ȷ���� �����֣�һ����find һ����count----------------
 	if(clients.find(id) == clients.end())
 	{
 		return false;
	}
	return true;
//	if(clients.count(id) == 1)
//	{
//		return true;
//	}
//	return false;
//----2. �쳣������ԣ����ǲ���ѧ--------	
//	try{
//		clients.at(id);
//		return true;
//	}catch(out_of_range err)
//	{
//		return false;
//	}
//----1. ���������� id �����ڻ����һ�� id�����Բ��������ַ���-------------------	
//	if(clients[id] != NULL)
//	{
//		return true;
//	}
//	return false;
}

//�û��ǳ� 
int Work::userLogout(int clientSd)
{
	for(auto p : clients)
	{
		if( p.second->socketID  == clientSd)
		{
			cout<<"Erase Client: "<<p.first<<" Socket ID: "<< p.second->socketID <<endl;
			//��Ҫ֪ͨ�û��Ѿ��ǳ�������֪��������Ѿ��ǳ� 
			clients.erase(p.first);
		}
	}
	return 0;
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
	if(ba.getBufLen() >= 4)//ȡ����Ϣͷ����Ϣ���� ����4��ʱ���ǿ���Ϣ 
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
	cout<< "Protocol id: "<< id << endl;
	switch(id)
	{
		case 100://--login
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
		case 200://--register
			struct RegRecvMsg RegRecv; 
			memset(&RegRecv, 0, sizeof(RegRecv));
			memcpy(&RegRecv, &ba.buf[ba.getPosition()], sizeof(RegRecv));
			
			cout<<"UserInfo: "<<RegRecv.userID<<"  "<<RegRecv.password<<endl;
			
			ba.plusPosition(sizeof(RegRecv));
			cout<<"position is: "<<ba.getPosition() << " available is: "<<ba.getBytesAvailable() << endl;
			
			verifyRegEvent(RegRecv, fd);
			break;
		case 300://--friend list
			struct FriendListRecvMsg friendListRecv;
			memset(&friendListRecv, 0, sizeof(friendListRecv));
			memcpy(&friendListRecv, &ba.buf[ba.getPosition()], sizeof(friendListRecv));
			cout<<"UserID: "<<friendListRecv.userID<<endl;
			ba.plusPosition(sizeof(FriendListRecvMsg));
			cout<<"position is: "<<ba.getPosition() << " available is: "<<ba.getBytesAvailable() << endl;
			
			sendFriendList(friendListRecv,fd);
				
			break;
		case 500://---message
			struct SendMessageRecvMsg recvMsg;
			memset(&recvMsg, 0, sizeof(recvMsg));
			memcpy(&recvMsg, &ba.buf[ba.getPosition()], ba.getBytesAvailable());
			cout<<"Send User ID: "<<recvMsg.senderUserID << " Recive User ID: "<<recvMsg.receiverUserID << " Message Info: "<<recvMsg.messageInfo<<endl;
			ba.plusPosition(ba.getBytesAvailable());
			cout<<"position is: "<<ba.getPosition() << " available is: "<<ba.getBytesAvailable() << endl;
			
			handleRecvMsgInfo(recvMsg, fd);
			break;	
		default:
			cout<<"Unkonwn Protocol " << id << endl; 
			break;
	}
	
	return 0;
}

int Work::handleRecvMsgInfo(struct SendMessageRecvMsg &msgRecv, int fd)
{
	struct SendmessageSendMsg sendMsg;
	memset(&sendMsg, 0, sizeof(sendMsg));
	sendMsg.protocolID = 501;
	if(!isPlayerOnLine(msgRecv.receiverUserID) || !isPlayerOnLine(msgRecv.senderUserID))
	{
		cout<<"The Receiver Or Sender is offline ! "<<" r: "<<msgRecv.receiverUserID<<" s: "<<msgRecv.senderUserID<<endl;
		return -1;
	}
	sendMsg.senderUserID = msgRecv.senderUserID;
	sendMsg.receiverUserID = msgRecv.receiverUserID;
	strcpy(sendMsg.messageInfo, msgRecv.messageInfo);
	sendMsg.len = sizeof(sendMsg.senderUserID)+sizeof(sendMsg.receiverUserID)+strlen(sendMsg.messageInfo);
	//1�������Լ� 
	int sendSize = send(fd, &sendMsg, sizeof(sendMsg.len)+sizeof(sendMsg.protocolID)+sendMsg.len, 0);
	cout<<"send myself::" << "sendSize: "<<sendSize<<endl;
	//2�������Է�
	int recvFD = clients[msgRecv.receiverUserID]->socketID;
	int sendSize2 = send(recvFD, &sendMsg, sizeof(sendMsg.len)+sizeof(sendMsg.protocolID)+sendMsg.len, 0);
	cout<<"send Other::" << "sendSize2: "<<sendSize2<<endl;
	return 0;
}

int Work::sendFriendList(struct FriendListRecvMsg &firendListRecv, int fd)
{
		//����sql���
	char sql[100] = {0};
	sprintf(sql, "select friendlist from userinfo where ID=%d and friendlist is not NULL", firendListRecv.userID);
	string result = sqlClient.getMySQLResult(&mysql, sql); 
	
	struct FriendListSendMsg friendlistSendMsg;
	memset(&friendlistSendMsg, 0, sizeof(friendlistSendMsg));

	friendlistSendMsg.protocolID = 301;
	
	if(result == "")//û�н�� ���߽������ 
	{
		cout<<"friendlist: NULL" << endl;
	}else{
		string finalStr = "";
		//Ҫ����������ֵ 
		vector<unordered_map<string, string>> testVec = pub.parseString(result);
		for (auto m : testVec)//m = map
		{
			for (auto p : m)//p = pair
			{
				cout << p.first << " = " << p.second << endl;
				auto s = p.second;
				string::size_type l = 0;
				string::size_type r = 0;
				string temp;
				string state;
				while (true)
				{
					r = s.find_first_of('|', r);
					if (r == string::npos)
					{
						break;
					}
					temp = s.substr(l, r - l);
					cout << "item is: " << temp << endl;
					//���Ҷ�ӦID����Ϣ 
					memset(sql, 0, sizeof(sql));
					sprintf(sql,"select ID, NAME, IMAGE from userinfo where ID=%s", temp.c_str());
					result = sqlClient.getMySQLResult(&mysql, sql);
					
					stringstream s1;
					if(isPlayerOnLine(atoi(temp.c_str())))
					{
						s1<<1;
					}else{
						s1<<0;
					}
					state = s1.str();
					result.replace(result.find_last_of('}'), 1, ",STATE:"+state+"}");
					cout<<"reslut is: "<<result<<endl;
					finalStr += result + ",";
					
					r++;
					l = r;
				}
				temp = s.substr(l);
				cout << "item is: " << temp << endl;
				memset(sql, 0, sizeof(sql));
				sprintf(sql,"select ID, NAME, IMAGE from userinfo where ID=%s", temp.c_str());
				result = sqlClient.getMySQLResult(&mysql, sql);
				
				stringstream s2;
				if(isPlayerOnLine(atoi(temp.c_str())))
				{
					s2<<1;
				}else{
					s2<<0;
				}
				state = s2.str();
				result.replace(result.find_last_of('}'), 1, ",STATE:"+state+"}");
				cout<<"result is: "<<result<<endl;
				finalStr += result;
				//����Ҫ֪ͨ�Է��������ˡ�
				 
			}
		}
		
//		strcpy(friendlistSendMsg.list, finalStr.c_str());

		size_t len = finalStr.copy(friendlistSendMsg.list, finalStr.length(), 0);
		
		friendlistSendMsg.len = finalStr.length();
		cout<<"friendlist: "<<friendlistSendMsg.list << "  len:  "<< len << endl;
	}
	
	int sendSize = send(fd, &friendlistSendMsg, sizeof(friendlistSendMsg.len)+sizeof(friendlistSendMsg.protocolID)+friendlistSendMsg.len, 0);
	cout << "sendSize: "<<sendSize<<endl;
	
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
		sprintf(sql,"insert userinfo (ID,PW,IMAGE) values (%d, %s, %d)", regRecv.userID, regRecv.password, 0);
		result = sqlClient.sendAndResponseMySQL(&mysql, sql);
		if(result == -2)//��ѯ��ȷ���ҷ��صĽ��ΪNULL 
		{
			cout<<"User register Success!"<<endl;
			//�����û���Ϣ 
			shared_ptr<ClientInfo> c = make_shared<ClientInfo>();
			c->userID = regRecv.userID;
			c->userName = "NULL";
			c->userImage = 0;
			c->userState = 1;
			c->socketID = fd; 
			cout<<"Self Info : UserName: "<<c->userName << " UserState : "<<c->userState<<" UserFD: "<<c->socketID<<endl;
			clients[c->userID] = c; 
			
			sprintf(regSendMsg.clientInfo, "{ID=%d,NAME=%s,IMAGE=%d,STATE=%d}", c->userID,c->userName.c_str(),c->userImage,c->userState);
		}else{
			cout<<"insert User Info. Error!"<<endl;
		}
	}
	else
	{
		cout<<"verifyRegEvent sql error!!"<<endl;
	}
	
	regSendMsg.len = sizeof(regSendMsg.regType)+strlen(regSendMsg.clientInfo);
	int sendSize = send(fd, &regSendMsg, sizeof(regSendMsg.len)+sizeof(regSendMsg.protocolID)+regSendMsg.len, 0);
	cout << "sendSize: "<<sendSize<<endl;
	
	return 0;
}

int Work::verifyUserData(struct LoginRecvMsg &loginRecv, int fd)
{
	//����sql��� 
	char sql[100] = {0};
	sprintf(sql,"select * from userinfo where  ID=%d and PW='%s'", loginRecv.userID, loginRecv.password);
	int result = sqlClient.sendAndResponseMySQL(&mysql, sql);
	
	struct LoginSendMsg loginSendMsg;
	memset(&loginSendMsg, 0, sizeof(loginSendMsg));
	
	loginSendMsg.protocolID = 101;
	string final = "";
	if(result > 0)//���������û� ������ѯ�������Ϊ1��
	{	
		loginSendMsg.loginType = 0;
		//�����û���Ϣ
		memset(sql, 0, sizeof(sql));
		sprintf(sql,"select ID,NAME,IMAGE from userinfo where ID=%d", loginRecv.userID);
		final = sqlClient.getMySQLResult(&mysql, sql);
		final.copy(loginSendMsg.clientInfo, final.length(), 0);		
		cout<<"User Login !! "<<loginSendMsg.clientInfo<<endl;
		//�������û�
		vector<unordered_map<string, string>> testVec = pub.parseString(final);
		shared_ptr<ClientInfo> c = make_shared<ClientInfo>();
		for (auto m : testVec)//m = map
		{
			for (auto p : m)//p = pair
			{
				if(p.first == "ID")
				{
					c->userID = atoi(p.second.c_str());
				}else if(p.first == "NAME")
				{
					c->userName = p.second;	
				}else if(p.first == "IMAGE")
				{
					c->userImage = atoi(p.second.c_str());
				}
			}
		}
		c->userState = 1;
		c->socketID = fd;
		cout<<"Self Info : UserName: "<<c->userName << " UserState : "<<c->userState<<" UserFD: "<<c->socketID<<endl;
		clients[c->userID] = c; 
	}
	else if(result == 0) //û���ҵ�����û�����Ӱ����0�� 
	{
		loginSendMsg.loginType = 1;
		cout<<"User ID or Password is Invalid !!"<<endl;
	}
	else
	{
		cout<<"verifyUserData sql error!!"<<endl;
	}
	
	loginSendMsg.len = sizeof(loginSendMsg.loginType)+final.length();
	int sendSize = send(fd, &loginSendMsg, sizeof(loginSendMsg.len)+sizeof(loginSendMsg.protocolID)+loginSendMsg.len, 0);
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
    	cout<<"epoll wait..."<<endl<<endl<<endl;
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
                	epoll_ctl(epfd, EPOLL_CTL_DEL, client_skfd, &ev);  
                    close(client_skfd);  
                }  
            }  
            //����Ǵ����¼�����ִ�� close   
            if(events[i].events & EPOLLERR)  
            {  
            	client_skfd = events[i].data.fd;  
            	userLogout(client_skfd);
            	epoll_ctl(epfd, EPOLL_CTL_DEL, client_skfd, &ev);
                close(client_skfd);  
            }  
            //����ǹ����¼��� ��ִ��close   
            if(events[i].events & EPOLLHUP)  
            {  
            	client_skfd = events[i].data.fd;  
            	userLogout(client_skfd);
            	epoll_ctl(epfd, EPOLL_CTL_DEL, client_skfd, &ev);
                close(client_skfd);  
            }  
        }
	} 
	//7��ѭ�������ر�epoll ��epoll �������������Ҫ��close�ر�   
    close(epfd); 
    close(socketfd);
}
