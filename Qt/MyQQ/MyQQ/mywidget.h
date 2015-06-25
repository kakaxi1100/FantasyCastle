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

    static int clientID;
public:

    void addFriendItem(ClientInfo &c);
    void addBlckListItem();

    QMap<int, struct ClientInfo*> clientMap;

    void addClient(quint32 userID);//添加用户信息
    void addClient(struct ClientInfo& c);
    void addClient(quint32 userID, QString userName, qint32 userImage, qint8 userState);
};

#endif // MYWIDGET_H
