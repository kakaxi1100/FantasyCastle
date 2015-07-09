#ifndef CLIENTINFO_H
#define CLIENTINFO_H
#include <string>

using namespace std;

class ClientInfo
{
public:
	
	ClientInfo();
	~ClientInfo();
	
	unsigned int userID;
    string userName;
    int userImage;
    signed char userState;
	unsigned int friends[250];
	int socketID;//socket ÃèÊö·û 
};
#endif
