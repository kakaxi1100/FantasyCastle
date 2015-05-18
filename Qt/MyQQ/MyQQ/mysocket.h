#ifndef MYSOCKET_H
#define MYSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QString>

class MySocket : QObject
{
    Q_OBJECT
public:
    MySocket(QObject *parent = 0);
    ~MySocket();
public:
    void socketConnect(QString ip, int port);
private slots:
    void socketConnected();
    void socketRecv();
    void socketSend();
    void socketError();
private:
    QTcpSocket* myTcpSocket;
};

#endif // MYSOCKET_H
