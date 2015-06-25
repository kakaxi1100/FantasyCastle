#ifndef GLOBAL_H
#define GLOBAL_H

#include "myevent.h"
#include <string>
#include <QString>

using namespace std;

typedef void(*EVENTFUN)(MyEvent&);

struct ClientInfo
{
    int id;
    unsigned int userID;
    QString userName;
    int userImage;
    signed char userState;
};

extern string LOGIN_RGE_SUCCESS;
extern string LOGIN_RGE_FAILURE;
extern string SOCKET_CONNECTED;
extern string FRIEND_LIST;
extern string ADD_FRIEND;


#endif // GLOBAL_H
