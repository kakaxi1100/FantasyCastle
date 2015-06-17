#ifndef MYSOCKET_H
#define MYSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QString>
#include <QByteArray>
#include <QMap>
#include "myeventdispatcher.h"

struct ClientInfo
{
    qint32 id;
    uint userID;
    QString userName;
    QString password;
};

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
    void setConnectType(int type);

    void socketConnect(uint userID, QString password, QString ip, int port);

private slots:
    void socketConnected();
    void socketDisconnected();
    void socketRecv();
    void socketError();
private:
    static MySocket* instance;//单例

    bool _isConnected;//判断是否已经建立链接
    int _connectType;
    void addClient(uint userID, QString password);//添加用户信息

    void loginSendMsg();//发送登录消息
    void regSendMsg();//发送注册消息

    QTcpSocket* myTcpSocket;

    QMap<int, struct ClientInfo*> clientMap;

    static int clientID;
};


#endif // MYSOCKET_H
