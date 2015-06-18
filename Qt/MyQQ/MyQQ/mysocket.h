#ifndef MYSOCKET_H
#define MYSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QString>
#include <QByteArray>
#include "myeventdispatcher.h"


struct LoginSend
{
   quint16 protocolID;//--100
   unsigned int userID;
   char password[100];
};

struct LoginRecv
{
    uchar loginType;
};

struct RegSend
{
    quint16 protocolID;//--200
    unsigned int userID;
    char password[100];
};

struct RegRecv
{
    uchar regType;
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
};


#endif // MYSOCKET_H
