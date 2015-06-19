#ifndef MYSOCKET_H
#define MYSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QString>
#include <QByteArray>
#include "myeventdispatcher.h"

//----login------
struct LoginSend
{
   quint16 protocolID;//--100
   unsigned int userID;
   char password[100];
};

struct LoginRecv//--101
{
    uchar loginType;
};

//----register-----
struct RegSend
{
    quint16 protocolID;//--200
    unsigned int userID;
    char password[100];
};

struct RegRecv//--201
{
    uchar regType;
};

//----freindlist-----
struct FriendListSend
{
    quint16 protocolID;//--300
    quint32 userID;
};

struct FriendListRcv//--301
{
    char list[2048];
};

class MySocket : QObject
{
    Q_OBJECT
public:
    MySocket(QObject *parent = 0);
    ~MySocket();
public:
    static MySocket* getInstance();
    bool isConnected();

    void socketConnect(QString ip, int port);

private slots:
    void socketConnected();
    void socketDisconnected();
    void socketRecv();
    void socketError();
private:
    static MySocket* instance;//单例
    bool _isConnected;//判断是否已经建立链接
    QTcpSocket* myTcpSocket;
public:
    void loginSendMsg(qint32 fUserID, QString fPassword);//发送登录消息
    void regSendMsg(qint32 fUserID, QString fPassword);//发送注册消息
    void friendListSendMsg(qint32 fUserID);//发送好友列表消息
};


#endif // MYSOCKET_H
