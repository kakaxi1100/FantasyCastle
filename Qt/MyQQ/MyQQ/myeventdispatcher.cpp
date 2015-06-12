#include "myeventdispatcher.h"

MyEventDispatcher::MyEventDispatcher()
{

}

MyEventDispatcher::~MyEventDispatcher()
{

}

unordered_map<string, EVENTFUN> MyEventDispatcher::myEvents;

void MyEventDispatcher::addEventListener(string type, EVENTFUN f)
{
    if (!hasEventListener(type))
    {
        myEvents[type] = f;
    }
    else
    {
        cout << "exist event type :: " << type << endl;
    }
}

void MyEventDispatcher::dispatchEvent(MyEvent &e)
{
    string &type = e.getType();
    if (hasEventListener(type))
    {
        myEvents[type](e);
    }
    else
    {
        cout << "can not find event type :: " << type << endl;
    }
}

void MyEventDispatcher::dispatchEvent(shared_ptr<MyEvent> e)
{
    string &type = e->getType();
    if (hasEventListener(type))
    {
        myEvents[type](*e);
    }
    else
    {
        cout << "can not find event type :: " << type << endl;
    }
}

bool MyEventDispatcher::hasEventListener(string type)
{
    return myEvents[type] != nullptr;
}

void MyEventDispatcher::removeEventListener(string type)
{
    myEvents.erase(type);
}
