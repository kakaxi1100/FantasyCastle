#ifndef GLOBALDATA_H
#define GLOBALDATA_H

//--100
struct LoginRecvMsg
{
	unsigned int userID;
	char password[100];	
};

//--101
struct LoginSendMsg
{
	unsigned short len;
	unsigned short protocolID;
	
	unsigned char loginType;//0-success,1-user or password invalid
	
	char clientInfo[100];//���ؿͻ�����Ϣ 
};

//--200
struct RegRecvMsg
{
	unsigned int userID;
	char password[100];	
};

//--201
struct RegSendMsg
{
	unsigned short len;
	unsigned short protocolID;
	
	unsigned char regType;//0-success,1-failure
	
	char clientInfo[100];//���ؿͻ�����Ϣ 
};

//--300
struct FriendListRecvMsg
{
	unsigned int userID;
};


//--301
struct FriendListSendMsg
{
	unsigned short len;
	unsigned short protocolID;
	
	char list[2048];
};

//--500
struct SendMessageRecvMsg
{
	unsigned int senderUserID;//������id
    unsigned int receiverUserID;//������id
    char messageInfo[2048];//���͵���Ϣ 
};


//--501
struct SendmessageSendMsg
{
	unsigned short len;
	unsigned short protocolID;
	
	unsigned int senderUserID;//������id
	unsigned int receiverUserID;//������id
    char messageInfo[2048];//���͵���Ϣ 
};
#endif
