#ifndef MYEVENT_H
#define MYEVENT_H

#include <string>
#include <iostream>

using namespace std;

class MyEvent
{
public:
    MyEvent(string type);
    ~MyEvent();

    string &getType();
    void setType(string value);
private:
    string _type;
};

#endif // MYEVENT_H
