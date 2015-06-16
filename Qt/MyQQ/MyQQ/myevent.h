#ifndef MYEVENT_H
#define MYEVENT_H

#include <iostream>
#include <string>
using namespace std;
class MyEvent
{
public:
    MyEvent(string type);
    ~MyEvent();
    string getType();
protected:
private:
    string _type;
};

#endif // MYEVENT_H
