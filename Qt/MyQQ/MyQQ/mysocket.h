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

class MySocket : QObject
{
    Q_OBJECT
public:
    MySocket(QObject *parent = 0);
    ~MySocket();
public:
    void socketConnect(uint userID, QString password, QString ip, int port);
private slots:
    void socketConnected();
    void socketRecv();
    void socketSend();
    void socketError();
private:
    void addClient(uint userID, QString password);

    void loginSendMsg();

    QTcpSocket* myTcpSocket;

    QMap<int, struct ClientInfo*> clientMap;

    static int clientID;
};


#endif // MYSOCKET_H
