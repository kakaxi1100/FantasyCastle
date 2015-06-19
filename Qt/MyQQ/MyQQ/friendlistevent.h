#ifndef FRIENDLISTEVENT_H
#define FRIENDLISTEVENT_H

#include <string>
#include <myevent.h>

using namespace std;

class FriendListEvent : public MyEvent
{
public:
    FriendListEvent(string type);

    string list;
};

#endif // FRIENDLISTEVENT_H
