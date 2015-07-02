#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include "myaddfriend.h"
#include "myfuncset.h"
#include "mytoolbox.h"
#include <QGroupBox>
#include <QVBoxLayout>
#include <QPushButton>
#include "global.h"
#include "myeventdispatcher.h"

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = 0);
    ~MyWidget();

    void destroyObjs();
private slots:
    void testFunc();
private:
    MyToolBox *mytoolbox;
    QGroupBox* friendGroup;
    QVBoxLayout* friendVBox;
    QGroupBox* blackListGroup;
    QVBoxLayout* blackListVBox;

    MyFuncSet* myFunSet;

    QPushButton* testBtn;

//    static int clientID;
public:
    static struct ClientInfo myInfo;//用户自己的信息

    void addFriendItem(ClientInfo &c);
    void addBlckListItem();

    QMap<unsigned int, struct ClientInfo*> clientMap;

    void addClient(struct ClientInfo& c);//添加用户信息
};

#endif // MYWIDGET_H
