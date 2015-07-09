#ifndef MYEVENTDISPATCHER_H
#define MYEVENTDISPATCHER_H

#include <unordered_map>
#include <string>
#include "myevent.h"
#include <iostream>
#include "myeventitem.h"
#include <memory>

using namespace std;

template<typename T>
class EventDispatcher
{
    typedef void(T::*EventFun)(MyEvent&);
public:
    static void addEventListener(string type, shared_ptr<T> t, EventFun f);
    static void dispatchEvent(shared_ptr<MyEvent> sp);
    static void removeEventListener(string type);
    static bool hasEventListener(string type);
private:
    static unordered_map<string, shared_ptr<EventItem<T>>> events;
};

template<typename T>
unordered_map<string, shared_ptr<EventItem<T>>> EventDispatcher<T>::events;

template<typename T>
void EventDispatcher<T>::addEventListener(string type, shared_ptr<T> t, EventFun f)
{
    if (!hasEventListener(type))
    {
        shared_ptr<EventItem<T>> spItem = make_shared<EventItem<T>>();
        spItem->t = t;
        spItem->f = f;
        events[type] = spItem;
    }
    else{
       // cout << "事件 " << type << " 已经定义" << endl;
    }
}

template<typename T>
void EventDispatcher<T>::dispatchEvent(shared_ptr<MyEvent> sp)
{
    string temp = sp->getType();
    if (hasEventListener(temp))
    {
        shared_ptr<EventItem<T>> spItem = events[temp];
        shared_ptr<T> spT = spItem->t;
        void(T::*spF)(MyEvent&) = spItem->f;
        (*spT.*spF)(*sp);
    }
    else{
        //cout << "event " << temp << " no define." << endl;
    }
}

template<typename T>
void EventDispatcher<T>::removeEventListener(string type)
{
    if (hasEventListener(type))
    {
        events.erase(type);
    }
    else{
       // cout << "event " << type << " no define." << endl;
    }
}

template<typename T>
bool EventDispatcher<T>::hasEventListener(string type)
{
    if (events[type] != nullptr)
    {
        return true;
    }
    return false;
}

#endif // MYEVENTDISPATCHER_H
