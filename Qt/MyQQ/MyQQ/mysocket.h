#ifndef MYSOCKET_H
#define MYSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QString>
#include <QByteArray>
#include <QMap>

struct ClientInfo
{
    qint32 id;
    QString userName;
    QString password;
};

struct LoginSend
{
    qint32 protocolID;
    QString userName;
    QString password;
};

class MySocket : QObject
{
    Q_OBJECT
public:
    MySocket(QObject *parent = 0);
    ~MySocket();
public:
    void socketConnect(QString userName, QString password, QString ip, int port);
private slots:
    void socketConnected();
    void socketRecv();
    void socketSend();
    void socketError();
private:
    void addClient(QString userName, QString password);

    void loginSendMsg();

    QTcpSocket* myTcpSocket;
    QByteArray outblock;//输出缓冲区

    struct LoginSend loginSend;

    QMap<int, struct ClientInfo*> clientMap;


    static int clientID;
};


#endif // MYSOCKET_H
