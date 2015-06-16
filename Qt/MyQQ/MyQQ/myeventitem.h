#ifndef MYEVENTITEM_H
#define MYEVENTITEM_H

#include "myevent.h"
#include <memory>

template <typename T>
class EventItem
{
public:
    EventItem()
    {
        cout << "EventItem()" << endl;
    }

    ~EventItem()
    {
        cout << "~EventItem()" << endl;
    }

    void (T::*f)(MyEvent&);
    shared_ptr<T> t;
};

#endif // MYEVENTITEM_H
