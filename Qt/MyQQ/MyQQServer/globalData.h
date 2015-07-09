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
	
	char clientInfo[100];//返回客户端信息 
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
	
	char clientInfo[100];//返回客户端信息 
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
	unsigned int senderUserID;//发送者id
    unsigned int receiverUserID;//接收者id
    char messageInfo[2048];//发送的信息 
};


//--501
struct SendmessageSendMsg
{
	unsigned short len;
	unsigned short protocolID;
	
	unsigned int senderUserID;//发送者id
	unsigned int receiverUserID;//接收者id
    char messageInfo[2048];//发送的信息 
};
#endif
