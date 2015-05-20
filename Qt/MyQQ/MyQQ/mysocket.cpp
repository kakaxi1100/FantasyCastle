#include "mysocket.h"
#include <QString>
#include <QHostAddress>
#include <QDataStream>
#include <QIODevice>
#include <QDebug>

int MySocket::clientID = 0;

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

    QMap<qint32, struct ClientInfo*>::const_iterator it = clientMap.cbegin();
    while(it != clientMap.cend())
    {
        delete it.value();
        ++it;
    }
}

void MySocket::socketConnect(QString userName, QString password, QString ip, int port)
{
    qDebug()<<"socketConnect "<<userName<<"   "<<password<<"   "<<ip<<"   "<< port<<endl;
    myTcpSocket->abort();//取消已经有的连接
    QHostAddress hostAddr(ip);
    myTcpSocket->connectToHost(hostAddr, port);

    addClient(userName, password);
}

void MySocket::socketConnected()
{
     qDebug()<<"socketConnected";
     loginSendMsg();
}

void MySocket::loginSendMsg()
{
    memset(&loginSend, 0, sizeof(loginSend));
    loginSend.protocolID = 100;
    const char *userName = clientMap[0]->userName.toStdString().c_str();
    const char *password = clientMap[0]->password.toStdString().c_str();

    strncpy(loginSend.userName, "userName", strlen("userName"));
    strncpy(loginSend.password, "password", strlen("password"));

    QDataStream sendout(&outblock, QIODevice::WriteOnly);
    sendout.setVersion(QDataStream::Qt_5_2);
    sendout<< loginSend.userName << loginSend.password;
    myTcpSocket->write(outblock);
    //outblock.resize(0);
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

void MySocket::addClient(QString userName, QString password)
{
    struct ClientInfo* clientInfo = new ClientInfo();

    clientInfo->userName = userName;
    clientInfo->password = password;

    clientMap[clientInfo->id] = clientInfo;

    clientID++;
}

