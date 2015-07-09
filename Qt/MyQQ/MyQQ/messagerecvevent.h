#ifndef MESSAGERECVEVENT_H
#define MESSAGERECVEVENT_H

#include <string>
#include <myevent.h>

class MessageRecvEvent : public MyEvent
{
public:
    MessageRecvEvent(string type);

    unsigned int senderUserID;
    unsigned int receiverUserID;
    string messge;
};

#endif // MESSAGERECVEVENT_H
