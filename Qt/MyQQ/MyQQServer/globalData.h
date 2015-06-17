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
	
	unsigned char loginType;//0-success,1-user invalid, 2-password invalid.
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
};

#endif
