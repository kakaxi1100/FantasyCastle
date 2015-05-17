#include "mysocket.h"
#include <QString>
#include <QHostAddress>
#include <QDebug>

MySocket::MySocket(QObject *parent) :
    QObject(parent)
{
    myTcpSocket = new QTcpSocket(this);
    connect(myTcpSocket, SIGNAL(readyRead()),this, SLOT(socketRecv()));
    connect(myTcpSocket, SIGNAL(connected()), this, SLOT(socketConnected()));
    connect(myTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError()));
}

MySocket::~MySocket()
{
    if(myTcpSocket != NULL)
    {
        delete myTcpSocket;
    }
}

void MySocket::socketConnect(QString ip, int port)
{
    qDebug()<<"socketConnect "<<ip<<"   "<< port<<endl;
    myTcpSocket->abort();//取消已经有的连接
    QHostAddress hostAddr(ip);
    myTcpSocket->connectToHost(hostAddr, port);
}

void MySocket::socketConnected()
{
     qDebug()<<"socketConnected";
}

void MySocket::socketRecv()
{

}

void MySocket::socketSend()
{

}

void MySocket::socketError()
{
    qDebug()<<myTcpSocket->errorString();
}
