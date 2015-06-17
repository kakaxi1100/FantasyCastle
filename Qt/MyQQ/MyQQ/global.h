#ifndef GLOBAL_H
#define GLOBAL_H

#include "myevent.h"
#include <string>
#include "mylogin.h"

using namespace std;

typedef void(*EVENTFUN)(MyEvent&);

extern const string LOGIN_RGE_SUCCESS;
extern const string LOGIN_RGE_FAILURE;

#endif // GLOBAL_H
