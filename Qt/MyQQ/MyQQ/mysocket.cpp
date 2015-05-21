#include "mysocket.h"
#include <QString>
#include <QHostAddress>
#include <QDataStream>
#include <QIODevice>
#include <QDebug>
#include <QtEndian>
#include <iostream>

using namespace std;

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

struct Test
{
    int a;
    char buf[100];
};

void MySocket::loginSendMsg()
{
/*    QByteArray outblock;//输出缓冲区
    struct LoginSend loginSend;
    memset(&loginSend, 0, sizeof(loginSend));
    loginSend.protocolID = 100;

    //注意必须转化一个 处理一个，不能都转化完后再处理，否则，所有的 数据都会是一个值
    //比如：
    //const char *userName = QString("Ares").toStdString().data();
    //const char *password = QString("123456")..toStdString().data();
    //cout<< userName <<"  " <<password << endl;
    //这时 userName = password = 123456；
    //必须这样处理
    //const char *userName = QString("Ares").toStdString().data();
    //cout<< userName;
    //const char *password = QString("123456")..toStdString().data();
    //cout<<"  " <<password << endl;
    //这时输出正确的值 : Ares 123456

    const char *userName = clientMap[0]->userName.toStdString().data();
    strncpy(loginSend.userName,userName, strlen(userName));
    const char *password = clientMap[0]->password.toStdString().data();
    strncpy(loginSend.password,password, strlen(password));
    cout << loginSend.userName<< "  " << loginSend.password<< endl;
    QDataStream sendout(&outblock, QIODevice::WriteOnly);
    sendout.setByteOrder(QDataStream::BigEndian);
//    sendout.setVersion(QDataStream::Qt_5_2);
//    sendout<< loginSend.userName << loginSend.password;
    sendout.writeBytes(loginSend.userName, sizeof(loginSend.userName));
    sendout.writeBytes(loginSend.password, sizeof(loginSend.password));

    qDebug()<<loginSend.userName<<"  "<<loginSend.password<<"  "<<sizeof(loginSend.userName) + sizeof(loginSend.password)<<endl;
    myTcpSocket->write(outblock, sizeof(loginSend.userName) + sizeof(loginSend.password));
    //outblock.resize(0);
*/
//----------------------for test----------------------------------
    QByteArray outblock;
    QDataStream sendout(&outblock, QIODevice::WriteOnly);
    sendout.setByteOrder(QDataStream::LittleEndian);
    if(sendout.byteOrder() == sendout.BigEndian)
    {
        qDebug()<<"BigEndian";
    }else{
        qDebug()<<"LittleEndian";
    }
 /*
//  注意char的类型的长度（sizeof）要提成int在后端才能正确收到
//  后端的类型也是int
//    int a = 123456;//转换成服务器的字节序
//    sendout<< a;
//    char b = 'x';
//    sendout<<b;
//    char c = 'y';
//    sendout<<c;
//    char d = 'z';
//    sendout<<d;
    const char * h = "okokokkok";
//    sendout << h; 这个服务端收到会错误，不知道输入成什么类型了
//    sendout.writeBytes(h, strlen(h)); 这个服务端收到会错误，内部经过处理了，用的无符号32位整型
//    outblock.append(h, strlen(h));
    sendout.writeRawData(h, strlen(h));//这个服务端收到不会报错
   qint64 q =  myTcpSocket->write(outblock, strlen(h));
*/
   struct Test t;
   t.a = 10;
   memset(t.buf, 0, sizeof(t.buf));
   const char* b = "bb";
   qDebug()<<"strlen(b)  "<<strlen(b);
   strncpy(t.buf, b, strlen(b));
   qDebug()<<"t.buf  "<<strlen(t.buf);
   sendout<<t.a;
   sendout.writeRawData(t.buf, strlen(t.buf));
   qint64 q =  myTcpSocket->write(outblock, sizeof(t.a) + strlen(t.buf));
   qDebug()<<q;
//----------------------------------------------------------------
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

    clientInfo->id = clientID;
    clientInfo->userName = userName;
    clientInfo->password = password;

    clientMap[clientInfo->id] = clientInfo;

    clientID++;
}

