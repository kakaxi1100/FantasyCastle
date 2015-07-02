#ifndef LOGINREGEVENT_H
#define LOGINREGEVENT_H

#include <string>
#include <myevent.h>

class LoginRegEvent : public MyEvent
{
public:
    LoginRegEvent(string type);
    string list;
};

#endif // LOGINREGEVENT_H
