#ifndef GLOBAL_H
#define GLOBAL_H

#include "myevent.h"
#include <string>
#include "mylogin.h"

using namespace std;

typedef void(*EVENTFUN)(MyEvent&);

extern string LOGIN_RGE_SUCCESS;
extern string LOGIN_RGE_FAILURE;
extern string SOCKET_CONNECTED;

#endif // GLOBAL_H
