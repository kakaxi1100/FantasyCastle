#include "myevent.h"

MyEvent::MyEvent(string type)
{
    _type = type;
   // cout << "MyEvent()" << endl;
}

MyEvent::~MyEvent()
{
  //  cout << "~MyEvent()" << endl;
}

std::string MyEvent::getType()
{
    return _type;
}
