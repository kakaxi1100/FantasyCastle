#ifndef MYEVENTDISPATCHER_H
#define MYEVENTDISPATCHER_H

#include <unordered_map>
#include "global.h"
#include "myevent.h"
#include <memory>

using namespace std;

class MyEventDispatcher
{
public:
    MyEventDispatcher();
    ~MyEventDispatcher();

    static void addEventListener(string type, EVENTFUN f);
    static void dispatchEvent(MyEvent& e);
    static void dispatchEvent(shared_ptr<MyEvent> e);
    static bool hasEventListener(string type);
    static void removeEventListener(string type);
private:
    static unordered_map<string, EVENTFUN> myEvents;
};

#endif // MYEVENTDISPATCHER_H
