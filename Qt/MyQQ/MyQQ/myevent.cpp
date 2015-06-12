#include "myevent.h"

MyEvent::MyEvent(string type)
{
    setType(type);

    cout << "MyEvent()" << endl;
}

MyEvent::~MyEvent()
{
    cout << "~MyEvent()" << endl;
}

string& MyEvent::getType()
{
    return _type;
}

void MyEvent::setType(string value)
{
    _type = value;
}
